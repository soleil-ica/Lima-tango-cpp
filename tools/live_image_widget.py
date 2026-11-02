from __future__ import annotations

import argparse
import os
import sys
import time
from typing import Any

import numpy as np
import tango
from taurus import Device
from taurus.external.qt import Qt
from taurus.qt.qtgui.base import TaurusBaseWidget

os.environ["QT_API"] = Qt.QWidget.__module__.split(".", 1)[0].lower()

from plotpy.items import ImageItem, RGBImageItem, RectangleShape
from plotpy.plot import PlotOptions, PlotWidget
from plotpy.tools import (
    ColormapTool,
    ContrastPanelTool,
    RectangleTool,
    RectZoomTool,
    SelectTool,
)
from qtpy import QtWidgets

if QtWidgets.QWidget is not Qt.QWidget:
    raise RuntimeError("Taurus and PlotPy must use the same Qt binding")


def is_image_pending_error(error: tango.DevFailed) -> bool:
    return any(
        getattr(detail, "reason", "") in (
            "API_AttrNotFound", "API_AttrValueNotSet", "API_EmptyDeviceAttribute",
        )
        for detail in error.args
    )


def decode_rgb24(value: Any) -> np.ndarray:
    """Decode Tango's uncompressed RGB24 encoding into an RGB array."""
    decoder = tango.EncodedAttribute()
    image = np.asarray(
        decoder.decode_rgb32(value, extract_as=tango.ExtractAs.Numpy)
    )

    if image.ndim == 3 and image.shape[2] >= 3:
        return np.ascontiguousarray(image[:, :, :3], dtype=np.uint8)
    if image.ndim == 2 and image.dtype == np.uint32:
        rgb = np.empty(image.shape + (3,), dtype=np.uint8)
        rgb[:, :, 0] = image & 0xFF
        rgb[:, :, 1] = (image >> 8) & 0xFF
        rgb[:, :, 2] = (image >> 16) & 0xFF
        return rgb
    raise ValueError(f"Unexpected RGB format: shape={image.shape}, dtype={image.dtype}")


class CameraTask(Qt.QThread):
    result_ready = Qt.pyqtSignal(object)

    def __init__(
        self,
        parent: Qt.QWidget,
        generation: int,
        device_name: str,
        operation: str,
        name: str = "",
        value: Any = None,
        include_modes: bool = False,
    ) -> None:
        super().__init__(parent)
        self.generation = generation
        self.device_name = device_name
        self.operation = operation
        self.name = name
        self.value = value
        self.include_modes = include_modes

    def run(self) -> None:
        attribute_names = (
            "State", "roiX", "roiY", "roiWidth", "roiHeight",
            "exposureTime", "latencyTime", "nbFrames", "triggerMode",
        )
        result: dict[str, Any] = {
            "generation": self.generation,
            "operation": self.operation,
            "name": self.name,
            "error": "",
            "values": {},
            "read_errors": {},
            "modes": None,
            "modes_error": "",
            "modes_deferred": False,
        }
        try:
            with tango.EnsureOmniThread():
                proxy = tango.DeviceProxy(self.device_name)
                proxy.set_timeout_millis(3000)
                if self.isInterruptionRequested():
                    return
                try:
                    if self.operation == "command":
                        if self.value is None:
                            proxy.command_inout(self.name)
                        else:
                            proxy.command_inout(self.name, self.value)
                    elif self.operation == "write":
                        proxy.write_attribute(self.name, self.value)
                except Exception as error:
                    result["error"] = str(error)
                for attribute_name in attribute_names:
                    if self.isInterruptionRequested():
                        break
                    try:
                        value = proxy.read_attribute(attribute_name).value
                        if value is None:
                            raise ValueError("No value returned")
                        result["values"][attribute_name] = value
                    except Exception as error:
                        result["read_errors"][attribute_name] = str(error)
                if self.include_modes and not self.isInterruptionRequested():
                    state = result["values"].get("State")
                    if state is None or getattr(state, "name", str(state)) in (
                        "RUNNING", "INIT", "FAULT",
                    ):
                        result["modes_deferred"] = True
                    else:
                        try:
                            modes = proxy.command_inout("GetAttributeAvailableValues", "triggerMode")
                            result["modes"] = [str(mode) for mode in modes]
                        except tango.DevFailed as error:
                            if any(
                                getattr(detail, "reason", "") == "API_CommandNotAllowed"
                                for detail in error.args
                            ):
                                result["modes_deferred"] = True
                            else:
                                result["modes_error"] = str(error)
                        except Exception as error:
                            result["modes_error"] = str(error)
        except Exception as error:
            result["error"] = str(error)
            for attribute_name in attribute_names:
                if attribute_name not in result["values"]:
                    result["read_errors"][attribute_name] = str(error)
        self.result_ready.emit(result)


class LiveImageWidget(Qt.QWidget, TaurusBaseWidget):
    image_ready = Qt.pyqtSignal(object)
    connection_changed = Qt.pyqtSignal(bool, str)

    def __init__(self, parent: Qt.QWidget | None = None) -> None:
        Qt.QWidget.__init__(self, parent)
        TaurusBaseWidget.__init__(self, self.__class__.__name__, parent=parent)
        self._device = None
        self._attribute = None
        self._proxy = None
        self._attribute_name = ""
        self._encoded_image = False
        self._last_frame_time: float | None = None
        self._image_item: ImageItem | RGBImageItem | None = None
        self._image_shape: tuple[int, int] | None = None
        self._roi: RectangleShape | None = None
        self.roi_bounds: tuple[int, int, int, int] | None = None
        self._camera_task: CameraTask | None = None
        self._camera_generation = 0
        self._camera_device_name = ""
        self._camera_initialized: set[str] = set()
        self._trigger_modes_loaded = False
        self._camera_refresh_pending = False
        self._camera_pending_action: tuple[str, str, Any] | None = None
        self._camera_state = "Disconnected"
        self._image_status_pending = False
        self._closing = False
        self._build_ui()
        self.image_ready.connect(self._show_image)
        self.connection_changed.connect(self._show_connection_state)
        self._camera_timer = Qt.QTimer(self)
        self._camera_timer.setInterval(2000)
        self._camera_timer.timeout.connect(self._refresh_camera_controls)

    def _build_ui(self) -> None:
        self.setWindowTitle("Lima Live Image")
        self.resize(1200, 760)

        self.device_edit = Qt.QLineEdit()
        self.device_edit.setPlaceholderText("sys/lima/basler")
        self.attribute_combo = Qt.QComboBox()
        self.attribute_combo.addItems(["image", "baseImage"])
        self.attribute_combo.currentTextChanged.connect(self._switch_image_attribute)

        self.connect_button = Qt.QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_model)

        toolbar = Qt.QHBoxLayout()
        toolbar.addWidget(Qt.QLabel("Device"))
        toolbar.addWidget(self.device_edit, 1)
        toolbar.addWidget(Qt.QLabel("Attribute"))
        toolbar.addWidget(self.attribute_combo)
        toolbar.addWidget(self.connect_button)

        self.plot_widget = PlotWidget(
            self,
            toolbar=True,
            options=PlotOptions(
                type="image",
                xlabel="X",
                ylabel="Y",
                xunit="px",
                yunit="px",
                yreverse=True,
                lock_aspect_ratio=True,
            ),
            auto_tools=False,
        )
        self.plot_widget.setMinimumSize(320, 240)
        self._plot = self.plot_widget.get_plot()
        manager = self.plot_widget.get_manager()
        select_tool = manager.add_tool(SelectTool)
        manager.set_default_tool(select_tool)
        manager.add_tool(RectZoomTool)
        plot_toolbar = self.plot_widget.get_toolbar()
        self.fit_button = Qt.QToolButton()
        self.fit_button.setIcon(self.style().standardIcon(Qt.QStyle.SP_TitleBarMaxButton))
        self.fit_button.setToolTip("Fit the image to the window")
        self.fit_button.clicked.connect(self._fit_image)
        plot_toolbar.addWidget(self.fit_button)
        self._roi_tool = manager.add_tool(
            RectangleTool,
            title="ROI",
            tip="Select a rectangular ROI",
            handle_final_shape_cb=self._set_roi,
            switch_to_default_tool=True,
        )
        self.clear_roi_button = Qt.QToolButton()
        self.clear_roi_button.setIcon(self.style().standardIcon(Qt.QStyle.SP_DialogResetButton))
        self.clear_roi_button.setToolTip("Clear ROI")
        self.clear_roi_button.setEnabled(False)
        self.clear_roi_button.clicked.connect(self._clear_roi)
        plot_toolbar.addWidget(self.clear_roi_button)
        manager.add_tool(ContrastPanelTool)
        manager.add_tool(ColormapTool)
        manager.update_tools_status()
        manager.activate_default_tool()
        self._roi_tool.action.setEnabled(False)
        self._plot.SIG_ITEM_MOVED.connect(self._roi_changed)
        self._plot.SIG_ITEM_HANDLE_MOVED.connect(self._roi_changed)
        self._plot.SIG_ITEM_RESIZED.connect(self._roi_changed)
        self._plot.SIG_ITEM_PARAMETERS_CHANGED.connect(self._roi_changed)
        self._plot.SIG_ITEM_REMOVED.connect(self._item_removed)

        self.roi_label = Qt.QLabel("Selected ROI: none")
        self.roi_label.setWordWrap(True)
        self.roi_label.setTextInteractionFlags(Qt.Qt.TextSelectableByMouse)
        self.roi_label.setToolTip(
            "Pixel coordinates relative to the displayed image; origin at the top left. "
            "x1 and y1 are exclusive bounds."
        )

        self.status_label = Qt.QLabel("No image")
        self.status_label.setStyleSheet("padding: 5px 2px; color: #8b1e1e;")
        self.global_status = Qt.QPlainTextEdit()
        self.global_status.setReadOnly(True)
        self.global_status.setLineWrapMode(Qt.QPlainTextEdit.NoWrap)
        self.global_status.setSizePolicy(Qt.QSizePolicy.Expanding, Qt.QSizePolicy.Fixed)
        self.global_status.setFixedHeight(96)
        self.global_status.setPlainText("Disconnected")

        detector_panel = Qt.QWidget()
        detector_layout = Qt.QVBoxLayout(detector_panel)
        detector_layout.setContentsMargins(6, 4, 6, 4)
        detector_layout.setSpacing(4)
        self.device_state_label = Qt.QLabel()
        self.device_state_label.setTextFormat(Qt.Qt.PlainText)
        self.device_state_label.setTextInteractionFlags(Qt.Qt.TextSelectableByMouse)
        self._show_device_state("Disconnected")
        state_layout = Qt.QHBoxLayout()
        state_layout.addWidget(Qt.QLabel("State"))
        state_layout.addWidget(self.device_state_label, 1)
        detector_layout.addLayout(state_layout)
        detector_form = Qt.QFormLayout()
        detector_form.setRowWrapPolicy(Qt.QFormLayout.WrapLongRows)
        detector_form.setHorizontalSpacing(12)
        detector_form.setVerticalSpacing(3)
        self.detector_labels: dict[str, Qt.QLabel] = {}
        for attribute_name in (
            "detectorDescription",
            "detectorType",
            "detectorModel",
            "detectorWidthMax",
            "detectorHeightMax",
            "detectorPixelDepth",
        ):
            label = Qt.QLabel("--")
            label.setTextFormat(Qt.Qt.PlainText)
            label.setWordWrap(True)
            label.setTextInteractionFlags(Qt.Qt.TextSelectableByMouse)
            self.detector_labels[attribute_name] = label
            detector_form.addRow(attribute_name, label)
        detector_layout.addLayout(detector_form)
        self.refresh_detector_button = Qt.QToolButton()
        self.refresh_detector_button.setIcon(
            self.style().standardIcon(Qt.QStyle.SP_BrowserReload)
        )
        self.refresh_detector_button.setToolTip("Refresh detector information")
        self.refresh_detector_button.setEnabled(False)
        self.refresh_detector_button.clicked.connect(self._refresh_detector_info)

        detector_layout.addWidget(Qt.QLabel("Detector ROI (px)"))
        roi_form = Qt.QFormLayout()
        roi_form.setRowWrapPolicy(Qt.QFormLayout.WrapLongRows)
        roi_form.setHorizontalSpacing(12)
        roi_form.setVerticalSpacing(3)
        self.detector_roi_labels: dict[str, Qt.QLabel] = {}
        for attribute_name in ("roiX", "roiY", "roiWidth", "roiHeight"):
            label = Qt.QLabel("--")
            label.setTextFormat(Qt.Qt.PlainText)
            label.setTextInteractionFlags(Qt.Qt.TextSelectableByMouse)
            self.detector_roi_labels[attribute_name] = label
            roi_form.addRow(attribute_name, label)
        detector_layout.addLayout(roi_form)
        detector_layout.addWidget(self.refresh_detector_button, 0, Qt.Qt.AlignRight)

        separator = Qt.QFrame()
        separator.setFrameShape(Qt.QFrame.HLine)
        detector_layout.addWidget(separator)
        detector_layout.addWidget(Qt.QLabel("Camera Controls"))
        commands_layout = Qt.QHBoxLayout()
        self.command_buttons: dict[str, Qt.QPushButton] = {}
        for command_name, icon in (
            ("Start", Qt.QStyle.SP_MediaPlay),
            ("Stop", Qt.QStyle.SP_MediaStop),
            ("Snap", Qt.QStyle.SP_MediaSkipForward),
        ):
            button = Qt.QPushButton(command_name)
            button.setIcon(self.style().standardIcon(icon))
            button.setToolTip(f"Execute {command_name} on the connected device")
            button.clicked.connect(
                lambda checked=False, name=command_name: self._request_camera("command", name)
            )
            commands_layout.addWidget(button)
            self.command_buttons[command_name] = button
        detector_layout.addLayout(commands_layout)
        self.set_roi_button = Qt.QPushButton("Set ROI")
        self.set_roi_button.setIcon(self.style().standardIcon(Qt.QStyle.SP_DialogApplyButton))
        self.set_roi_button.setToolTip("Send the selected ROI as x0, y0, width, height")
        self.set_roi_button.clicked.connect(self._set_camera_roi)
        self.reset_roi_button = Qt.QPushButton("Reset ROI")
        self.reset_roi_button.setIcon(self.style().standardIcon(Qt.QStyle.SP_ArrowBack))
        self.reset_roi_button.setToolTip("Reset ROI on the camera (ResetROI)")
        self.reset_roi_button.clicked.connect(
            lambda: self._request_camera("command", "ResetROI")
        )
        roi_commands_layout = Qt.QHBoxLayout()
        roi_commands_layout.addWidget(self.set_roi_button, 1)
        roi_commands_layout.addWidget(self.reset_roi_button, 1)
        detector_layout.addLayout(roi_commands_layout)

        controls_layout = Qt.QFormLayout()
        controls_layout.setRowWrapPolicy(Qt.QFormLayout.DontWrapRows)
        controls_layout.setHorizontalSpacing(12)
        controls_layout.setVerticalSpacing(4)
        self.camera_editors: dict[str, Any] = {}
        self.camera_readbacks: dict[str, Qt.QLabel] = {}
        self.camera_apply_buttons: dict[str, Qt.QToolButton] = {}
        for attribute_name in ("exposureTime", "latencyTime", "nbFrames", "triggerMode"):
            if attribute_name == "triggerMode":
                editor = Qt.QComboBox()
                editor.setMinimumContentsLength(12)
                editor.setSizeAdjustPolicy(Qt.QComboBox.AdjustToMinimumContentsLengthWithIcon)
                self.trigger_mode_combo = editor
            elif attribute_name == "nbFrames":
                editor = Qt.QSpinBox()
                editor.setRange(0, 2147483647)
            else:
                editor = Qt.QDoubleSpinBox()
                editor.setDecimals(6)
                editor.setRange(0.0, 1e12)
                editor.setSingleStep(0.1)
                editor.setSuffix(" ms")
            self.camera_editors[attribute_name] = editor
            apply_button = Qt.QToolButton()
            apply_button.setIcon(self.style().standardIcon(Qt.QStyle.SP_DialogApplyButton))
            apply_button.setToolTip(f"Apply {attribute_name}")
            apply_button.clicked.connect(
                lambda checked=False, name=attribute_name: self._write_camera_attribute(name)
            )
            self.camera_apply_buttons[attribute_name] = apply_button
            readback = Qt.QLabel("Current: --")
            readback.setTextFormat(Qt.Qt.PlainText)
            readback.setWordWrap(True)
            readback.setTextInteractionFlags(Qt.Qt.TextSelectableByMouse)
            self.camera_readbacks[attribute_name] = readback
            entry_layout = Qt.QHBoxLayout()
            entry_layout.addWidget(editor, 1)
            entry_layout.addWidget(apply_button)
            field_layout = Qt.QVBoxLayout()
            field_layout.setSpacing(2)
            field_layout.addLayout(entry_layout)
            field_layout.addWidget(readback)
            controls_layout.addRow(attribute_name, field_layout)
        detector_layout.addLayout(controls_layout)
        detector_layout.addStretch()
        self.trigger_mode_combo.currentIndexChanged.connect(
            lambda index: self._update_camera_controls_enabled()
        )
        self._update_camera_controls_enabled()

        detector_scroll = Qt.QScrollArea()
        detector_scroll.setWidgetResizable(True)
        detector_scroll.setFrameShape(Qt.QFrame.NoFrame)
        detector_scroll.setHorizontalScrollBarPolicy(Qt.Qt.ScrollBarAlwaysOff)
        detector_scroll.setMinimumWidth(
            detector_panel.minimumSizeHint().width()
            + 2 * detector_scroll.frameWidth()
            + self.style().pixelMetric(Qt.QStyle.PM_ScrollBarExtent)
        )
        detector_scroll.setWidget(detector_panel)

        self.content_splitter = Qt.QSplitter(Qt.Qt.Horizontal, self)
        self.content_splitter.setChildrenCollapsible(False)
        self.content_splitter.setHandleWidth(8)
        self.content_splitter.addWidget(self.plot_widget)
        self.content_splitter.addWidget(detector_scroll)
        self.content_splitter.setStretchFactor(0, 1)
        self.content_splitter.setStretchFactor(1, 0)
        self.content_splitter.setSizes([800, 360])
        self.content_splitter.handle(1).setToolTip("Adjust detector panel width")

        self.image_refresh_label = Qt.QLabel("Image: not subscribed")
        self.image_polling_spin = Qt.QSpinBox()
        self.image_polling_spin.setRange(50, 60000)
        self.image_polling_spin.setSingleStep(100)
        self.image_polling_spin.setSuffix(" ms")
        self.image_polling_spin.setValue(1000)
        self.image_polling_spin.setToolTip(
            "Taurus client-side polling period when Tango image events are unavailable"
        )
        self.image_polling_spin.valueChanged.connect(self._set_image_polling_period)
        image_refresh_layout = Qt.QHBoxLayout()
        image_refresh_layout.addWidget(self.image_refresh_label)
        image_refresh_layout.addStretch()
        image_refresh_layout.addWidget(Qt.QLabel("Image polling"))
        image_refresh_layout.addWidget(self.image_polling_spin)

        layout = Qt.QVBoxLayout(self)
        layout.addLayout(toolbar)
        layout.addWidget(self.plot_widget.get_toolbar())
        layout.addWidget(self.content_splitter, 1)
        layout.addWidget(self.roi_label)
        layout.addLayout(image_refresh_layout)
        layout.addWidget(self.global_status)
        layout.addWidget(self.status_label)

    def setModel(self, model: str | None) -> None:
        if not model:
            return
        self.device_edit.setText(model.strip())
        self.connect_model()

    @Qt.pyqtSlot(str)
    def _switch_image_attribute(self, attribute_name: str) -> None:
        if self._device is not None:
            self.connect_model()

    @Qt.pyqtSlot()
    def connect_model(self) -> None:
        self._disconnect_model()
        self._clear_roi()
        if self._image_item is not None:
            self._plot.del_item(self._image_item)
        self._image_item = None
        self._image_shape = None
        self._last_frame_time = None
        self.status_label.setText("No image")
        self._roi_tool.action.setEnabled(False)
        self._plot.replot()
        device_name = self.device_edit.text().strip()
        attribute_name = self.attribute_combo.currentText()
        if not device_name:
            self._show_connection_state(False, "Device is required")
            return

        try:
            self._device = Device(device_name)
            self._proxy = tango.DeviceProxy(device_name)
            self._proxy.ping()
            self._attribute_name = attribute_name
            self._camera_device_name = device_name
            self._subscribe_image()
            self.refresh_detector_button.setEnabled(True)
            self._refresh_detector_info()
            self._camera_timer.start()
            self._update_camera_controls_enabled()
            self.connect_button.setText("Reconnect")
            self._show_connection_state(
                True, f"Connected to {device_name} - waiting for an image ({attribute_name})"
            )
        except Exception as error:
            self._disconnect_model()
            self._show_connection_state(False, str(error))

    def _subscribe_image(self) -> None:
        if self._proxy is None or self._attribute is not None:
            return
        try:
            config = self._proxy.get_attribute_config(self._attribute_name)
        except tango.DevFailed as error:
            if is_image_pending_error(error):
                self._show_connection_state(
                    True, f"Connected - waiting for an image ({self._attribute_name})"
                )
                return
            raise
        attribute = self._device.getAttribute(self._attribute_name)
        self._encoded_image = config.data_type == tango.DevEncoded
        self._attribute = attribute
        try:
            attribute.changePollingPeriod(self.image_polling_spin.value())
            attribute.addListener(self)
        except Exception:
            try:
                attribute.removeListener(self)
            except Exception:
                pass
            self._attribute = None
            raise
        self._update_image_refresh_mode()

    @Qt.pyqtSlot(int)
    def _set_image_polling_period(self, period: int) -> None:
        if self._attribute is not None:
            try:
                self._attribute.changePollingPeriod(period)
            except Exception as error:
                self._show_connection_state(False, f"Unable to change image polling: {error}")
        self._update_image_refresh_mode()

    def _update_image_refresh_mode(self) -> None:
        if self._attribute is None:
            text = "Image: not subscribed"
        elif self._attribute.isPollingActive():
            text = f"Image: polling ({self._attribute.getPollingPeriod()} ms)"
        elif self._attribute.isUsingEvents():
            text = "Image: Tango events"
        else:
            text = "Image: subscribing"
        self.image_refresh_label.setText(text)

    def _disconnect_model(self) -> None:
        self._camera_timer.stop()
        self._camera_generation += 1
        self._camera_refresh_pending = False
        self._camera_pending_action = None
        self._camera_device_name = ""
        self._camera_initialized.clear()
        self._trigger_modes_loaded = False
        if self._camera_task is not None:
            self._camera_task.requestInterruption()
        if self._attribute is not None:
            try:
                self._attribute.removeListener(self)
            except Exception:
                pass
        self._attribute = None
        self._device = None
        self._proxy = None
        self._attribute_name = ""
        self._encoded_image = False
        self._update_image_refresh_mode()
        self._show_device_state("Disconnected")
        self.refresh_detector_button.setEnabled(False)
        for label in self.detector_labels.values():
            label.setText("--")
            label.setToolTip("")
        for label in self.detector_roi_labels.values():
            label.setText("--")
            label.setToolTip("")
        self.trigger_mode_combo.clear()
        for label in self.camera_readbacks.values():
            label.setText("Current: --")
            label.setToolTip("")
        self._show_global_status("Disconnected")
        self._update_camera_controls_enabled()

    @Qt.pyqtSlot()
    def _refresh_detector_info(self) -> None:
        if self._proxy is None:
            return
        for attribute_name, label in self.detector_labels.items():
            try:
                value = self._proxy.read_attribute(attribute_name).value
                if value is None:
                    raise ValueError("No value returned")
            except Exception as error:
                label.setText("Unavailable")
                label.setToolTip(str(error))
            else:
                label.setText(str(value))
                label.setToolTip("")
        self._refresh_camera_controls(include_modes=True)

    def _update_camera_controls_enabled(self) -> None:
        connected = self._proxy is not None
        fault = self._camera_state == "FAULT"
        running = self._camera_state == "RUNNING"
        reading = self._camera_task is not None and self._camera_task.operation == "refresh"
        ready = (
            connected and (self._camera_task is None or reading)
            and self._camera_pending_action is None and not self._closing and not fault
        )
        for name, button in self.command_buttons.items():
            button.setEnabled(ready and not (running and name in ("Start", "Snap")))
        self.reset_roi_button.setEnabled(ready and not running)
        self.clear_roi_button.setEnabled(
            self._roi is not None and not fault and not self._closing
        )
        bounds = self.roi_bounds
        self.set_roi_button.setEnabled(
            ready and bounds is not None and bounds[2] > bounds[0] and bounds[3] > bounds[1]
        )
        for name, editor in self.camera_editors.items():
            available = (
                connected and name in self._camera_initialized and not fault and not self._closing
            )
            if name == "triggerMode":
                available = (
                    available and self._trigger_modes_loaded and self.trigger_mode_combo.count() > 0
                )
            editor.setEnabled(available)
            selected = name != "triggerMode" or self.trigger_mode_combo.currentIndex() >= 0
            self.camera_apply_buttons[name].setEnabled(ready and available and selected)

    def _refresh_camera_controls(self, include_modes: bool = False) -> None:
        if self._proxy is not None and self._attribute is None:
            try:
                self._subscribe_image()
            except Exception as error:
                self._show_connection_state(False, f"Unable to subscribe to image: {error}")
        self._update_image_refresh_mode()
        if self._camera_task is not None:
            self._camera_refresh_pending |= include_modes
            return
        self._request_camera("refresh", include_modes=include_modes)

    def _request_camera(
        self, operation: str, name: str = "", value: Any = None, include_modes: bool = False
    ) -> None:
        if self._proxy is None or self._closing:
            return
        if operation != "refresh" and (
            self._camera_state == "FAULT"
            or (self._camera_state == "RUNNING" and name in ("Start", "Snap", "ResetROI"))
        ):
            self._show_global_status(
                f"{name}: unavailable while camera is {self._camera_state}", True
            )
            return
        include_modes = include_modes or not self._trigger_modes_loaded
        if self._camera_task is not None:
            if (
                self._camera_task.operation == "refresh" and operation != "refresh"
                and self._camera_pending_action is None
            ):
                self._camera_pending_action = (operation, name, value)
                self._camera_refresh_pending |= self._camera_task.include_modes
                self._camera_task.requestInterruption()
                self._show_global_status(f"{name}: pending")
                self._update_camera_controls_enabled()
            return
        task = CameraTask(
            self, self._camera_generation, self._camera_device_name,
            operation, name, value, include_modes,
        )
        self._camera_task = task
        task.result_ready.connect(self._camera_result)
        task.finished.connect(self._camera_task_finished)
        task.finished.connect(task.deleteLater)
        self._update_camera_controls_enabled()
        if operation != "refresh":
            self._show_global_status(f"{name}: pending")
        task.start()

    @Qt.pyqtSlot(object)
    def _camera_result(self, result: dict[str, Any]) -> None:
        if result["generation"] != self._camera_generation or self._closing:
            return
        if result["modes"] is not None:
            selected_mode = (
                self.trigger_mode_combo.currentText() if self._trigger_modes_loaded
                else str(result["values"].get("triggerMode", ""))
            )
            self._trigger_modes_loaded = True
            self.trigger_mode_combo.clear()
            self.trigger_mode_combo.addItems(result["modes"])
            selected_index = self.trigger_mode_combo.findText(selected_mode)
            if selected_index >= 0:
                self.trigger_mode_combo.setCurrentIndex(selected_index)
            elif "triggerMode" in result["values"]:
                self.trigger_mode_combo.setCurrentIndex(
                    self.trigger_mode_combo.findText(str(result["values"]["triggerMode"]))
                )
            self.trigger_mode_combo.setToolTip("")
        elif result["modes_error"]:
            self.trigger_mode_combo.setToolTip(result["modes_error"])
        elif result["modes_deferred"] and not self._trigger_modes_loaded:
            self.trigger_mode_combo.setToolTip(
                "Trigger mode choices will load automatically when the device is idle"
            )
        for name, value in result["values"].items():
            if name == "State":
                self._show_device_state(value)
                continue
            if name in self.detector_roi_labels:
                self.detector_roi_labels[name].setText(str(value))
                self.detector_roi_labels[name].setToolTip("")
                continue
            label = self.camera_readbacks[name]
            suffix = " ms" if name in ("exposureTime", "latencyTime") else ""
            label.setText(f"Current: {value}{suffix}")
            label.setToolTip("")
            if name == "triggerMode" and not self._trigger_modes_loaded:
                self.trigger_mode_combo.clear()
                self.trigger_mode_combo.addItem(str(value))
            if name not in self._camera_initialized:
                if name == "triggerMode":
                    self.trigger_mode_combo.setCurrentIndex(
                        self.trigger_mode_combo.findText(str(value))
                    )
                else:
                    self.camera_editors[name].setValue(value)
                self._camera_initialized.add(name)
        for name, error in result["read_errors"].items():
            if name == "State":
                self._show_device_state("Unavailable", error)
                continue
            if name in self.detector_roi_labels:
                self.detector_roi_labels[name].setText("Unavailable")
                self.detector_roi_labels[name].setToolTip(error)
                continue
            self.camera_readbacks[name].setText("Current: unavailable")
            self.camera_readbacks[name].setToolTip(error)
        if result["error"]:
            self._show_global_status(f"{result['name'] or 'Read'} error: {result['error']}", True)
        elif result["operation"] != "refresh":
            self._show_global_status(f"{result['name']}: completed")
            if result["name"] in ("SetROI", "ResetROI"):
                self._clear_roi()
        if result["operation"] == "refresh" and result["modes_error"]:
            self._show_global_status(f"Trigger modes unavailable: {result['modes_error']}", True)
        self._update_camera_controls_enabled()

    def _show_device_state(self, value: Any, error: str = "") -> None:
        state = getattr(value, "name", str(value))
        self._camera_state = state
        background, color = {
            "ON": ("#00ff00", "#000000"),
            "OFF": ("#ffffff", "#000000"),
            "CLOSE": ("#ffffff", "#000000"),
            "OPEN": ("#00ff00", "#000000"),
            "INSERT": ("#ffffff", "#000000"),
            "EXTRACT": ("#00ff00", "#000000"),
            "MOVING": ("#80a0ff", "#000000"),
            "STANDBY": ("#ffff00", "#000000"),
            "FAULT": ("#ff0000", "#000000"),
            "INIT": ("#cccc7a", "#000000"),
            "RUNNING": ("#007d00", "#ffffff"),
            "ALARM": ("#ff8c00", "#000000"),
            "DISABLE": ("#ff00ff", "#000000"),
            "UNKNOWN": ("#9b9b9b", "#000000"),
            "Unavailable": ("#f9dede", "#8b1e1e"),
        }.get(state, ("#eeeeee", "#444444"))
        self.device_state_label.setText(state)
        self.device_state_label.setToolTip(error)
        self.device_state_label.setStyleSheet(
            f"background-color: {background}; color: {color}; "
            "padding: 4px 8px; border-radius: 3px; font-weight: bold;"
        )

    @Qt.pyqtSlot()
    def _camera_task_finished(self) -> None:
        self._camera_task = None
        self._update_camera_controls_enabled()
        if self._camera_pending_action is not None:
            operation, name, value = self._camera_pending_action
            self._camera_pending_action = None
            self._request_camera(operation, name, value)
        elif self._camera_refresh_pending:
            self._camera_refresh_pending = False
            self._refresh_camera_controls(include_modes=True)

    def _show_global_status(self, message: str, failed: bool = False) -> None:
        self._image_status_pending = False
        self.global_status.setPlainText(message)
        color = "#8b1e1e" if failed else "#176b3a"
        self.global_status.setStyleSheet(f"padding: 5px 2px; color: {color};")

    def _write_camera_attribute(self, name: str) -> None:
        editor = self.camera_editors[name]
        if name == "triggerMode":
            value = editor.currentText()
            if not value:
                return
        else:
            editor.interpretText()
            value = int(editor.value()) if name == "nbFrames" else float(editor.value())
        self._request_camera("write", name, value)

    @Qt.pyqtSlot()
    def _set_camera_roi(self) -> None:
        if self.roi_bounds is None:
            return
        x0, y0, x1, y1 = self.roi_bounds
        values = [x0, y0, x1 - x0, y1 - y0]
        if values[2] <= 0 or values[3] <= 0 or any(value < 0 or value > 4294967295 for value in values):
            self._show_global_status("Invalid ROI for SetROI", True)
            return
        self._request_camera("command", "SetROI", np.asarray(values, dtype=np.uint32))

    def eventReceived(self, source: Any, event_type: Any, event_value: Any) -> None:
        if source is not self._attribute or self._proxy is None:
            return
        try:
            device_attribute = self._proxy.read_attribute(
                self._attribute_name,
                extract_as=(
                    tango.ExtractAs.Nothing if self._encoded_image else tango.ExtractAs.Numpy
                ),
            )
            if device_attribute.dim_x == 0:
                self.connection_changed.emit(True, "Connected - waiting for an image")
                return
            if not self._encoded_image and device_attribute.value is None:
                self.connection_changed.emit(True, "Connected - waiting for an image")
                return
            image = (
                decode_rgb24(device_attribute)
                if self._encoded_image
                else np.asarray(device_attribute.value)
            )
            if image.size == 0:
                self.connection_changed.emit(True, "Connected - waiting for an image")
                return
            if image.ndim not in (2, 3):
                raise ValueError(f"Unexpected image shape: {image.shape}")
            if image.ndim == 3 and (image.shape[2] != 3 or image.dtype != np.uint8):
                raise ValueError(f"Unexpected RGB format: shape={image.shape}, dtype={image.dtype}")
            if image.ndim == 2 and image.dtype.kind not in "uif":
                raise ValueError(f"Unexpected monochrome dtype: {image.dtype}")
            image = np.ascontiguousarray(image)
        except tango.DevFailed as error:
            if is_image_pending_error(error):
                self.connection_changed.emit(True, "Connected - waiting for an image")
            else:
                self.connection_changed.emit(False, f"Unable to read image: {error}")
            return
        except Exception as error:
            self.connection_changed.emit(False, f"Unable to decode image: {error}")
            return
        self.image_ready.emit(image)

    @Qt.pyqtSlot(object)
    def _show_image(self, image: np.ndarray) -> None:
        self._update_image_refresh_mode()
        height, width = image.shape[:2]
        is_rgb = image.ndim == 3
        shape_changed = self._image_shape != (height, width)
        if shape_changed:
            self._clear_roi()
        if self._image_item is None or is_rgb != isinstance(self._image_item, RGBImageItem):
            if self._image_item is not None:
                self._plot.del_item(self._image_item)
            self._image_item = RGBImageItem(image) if is_rgb else ImageItem(image)
            if not is_rgb:
                self._image_item.set_color_map("gray")
                self._image_item.param.keep_lut_range = True
            self._image_item.set_movable(False)
            self._image_item.set_resizable(False)
            self._image_item.set_rotatable(False)
            self._image_item.set_readonly(True)
            self._plot.add_item(self._image_item, z=0, autoscale=False)
            self._plot.set_active_item(self._image_item)
        else:
            if shape_changed:
                self._image_item.set_xdata(0, width)
                self._image_item.set_ydata(0, height)
            self._image_item.set_data(image)
        self._image_shape = (height, width)
        self._plot.enableAxis(self._plot.colormap_axis, not is_rgb)
        self._roi_tool.action.setEnabled(True)
        if shape_changed:
            self._fit_image()
        else:
            self._plot.replot()
        now = time.monotonic()
        fps = 0.0 if self._last_frame_time is None else 1.0 / max(now - self._last_frame_time, 1e-9)
        self._last_frame_time = now
        image_format = "RGB24" if is_rgb else f"Mono {image.dtype}"
        self.status_label.setText(f"{width} x {height} | {image_format} | {fps:.1f} fps")
        self.status_label.setStyleSheet("padding: 5px 2px; color: #176b3a;")
        if self._image_status_pending:
            self._show_global_status("Image stream active")

    @Qt.pyqtSlot(bool, str)
    def _show_connection_state(self, connected: bool, message: str) -> None:
        self._show_global_status(message, not connected)
        self._image_status_pending = True

    @Qt.pyqtSlot()
    def _fit_image(self) -> None:
        if self._image_item is not None:
            self._plot.do_autoscale()

    def _set_roi(self, shape: RectangleShape) -> None:
        self._clear_roi()
        if self._image_item is None:
            self._plot.del_item(shape)
            return
        self._roi = shape
        self._plot.add_autoscale_excludes([shape])
        self._update_roi_label()

    def _roi_changed(self, item: Any, *args: Any) -> None:
        if item is self._roi:
            self._update_roi_label()

    def _item_removed(self, item: Any) -> None:
        if item is self._roi:
            self._roi = None
            self._update_roi_label()
            self.clear_roi_button.setEnabled(False)

    def _update_roi_label(self) -> None:
        self.roi_bounds = None
        self._update_camera_controls_enabled()
        if self._roi is None or self._image_item is None:
            self.roi_label.setText("Selected ROI: none")
            return
        x0, y0, x1, y1 = self._roi.get_rect()
        left, right = sorted((x0, x1))
        top, bottom = sorted((y0, y1))
        bounds = self._image_item.boundingRect()
        if (
            right <= bounds.left() or left >= bounds.right()
            or bottom <= bounds.top() or top >= bounds.bottom()
        ):
            self.roi_label.setText("Selected ROI: outside image")
            return
        self.roi_bounds = self._image_item.get_closest_index_rect(left, top, right, bottom)
        x0, y0, x1, y1 = self.roi_bounds
        self.roi_label.setText(
            f"Selected ROI (px): x0={x0}, y0={y0}, x1={x1}, y1={y1} | "
            f"width={x1 - x0}, height={y1 - y0}"
        )
        self._update_camera_controls_enabled()

    @Qt.pyqtSlot()
    def _clear_roi(self) -> None:
        if self._roi is not None:
            self._plot.del_item(self._roi)
        self._roi = None
        self._update_roi_label()
        self.clear_roi_button.setEnabled(False)
        self._plot.replot()

    def closeEvent(self, event: Qt.QCloseEvent) -> None:
        self._closing = True
        self._disconnect_model()
        if self._camera_task is not None:
            self._camera_task.wait()
        super().closeEvent(event)


def main() -> int:
    parser = argparse.ArgumentParser(description="Taurus/PlotPy viewer for Lima images")
    parser.add_argument("device", nargs="?", help="Tango device, e.g. sys/lima/basler")
    args = parser.parse_args()

    app = Qt.QApplication.instance() or Qt.QApplication(sys.argv)
    widget = LiveImageWidget()
    if args.device:
        widget.setModel(args.device)
    widget.show()
    return app.exec()


if __name__ == "__main__":
    raise SystemExit(main())