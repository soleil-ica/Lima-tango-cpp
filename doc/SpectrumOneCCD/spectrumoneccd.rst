.. _lima-tango-spectrumoneccd:

SpectrumOneCCD C++ Tango device
===============================

This is the reference documentation of the SpectrumOneCCD Tango C++ device.


Properties
----------
======================= ======================================= =============== =========================================================================
Property name           Default value                           Type            Description
======================= ======================================= =============== =========================================================================
CameraGpibAddress       0                                       Long            Gpib Address of the controller (from 0 to 30).
GpibControllerPort      1234                                    Long            IP port of the controller.
GpibControllerHost      127.0.0.1                               String          Host name or IP adress of the controller.
TablesPath              /usr/Local/configFiles/SpectrumOne      String          Path of the tables to be loaded in the camera for its initialization.
ExpertConfig            [CCD_config]                            String[]        Advanced config for the camera.
                        port=
                        total_active_x_pixels=
                        total_active_y_pixels=
                        num_serial_pixels_before_active=
                        num_serial_pixels_after_active=
                        num_parallel_rows_before_active=
                        num_parallel_rows_after_active=
                        register_loc_and_direction=
                        min_temperature=
                        max_temperature=
                        min_shutter_time=
                        max_shutter_time=
                        min_gain=
                        max_gain=
                        h_pixel_spacing=
                        v_pixel_spacing=
                        total_parallel_pixels=
                        total_serial_pixels=
InvertX                 false                                   Boolean         Used to invert the X axis of the images.
TablesMode              1401                                    String          Mode of the tables to send to the camera for its initialization.
                                                                                Is contained in the file names of the tables.
                                                                                For example the mode of XXXX1401.TAB is 1401. 
======================= ======================================= =============== =========================================================================


Attributes
----------

======================= =============== =============== ======================================
Attribute name          Read/Write      Type            Description
======================= =============== =============== ======================================
lastTemperature         Read            Double          Last temperature of the CCD.
gain                    Read/Write      Long            CCD gain of the camera.
numFlushes              Read/Write      Long            Set number of flushes on the camera
======================= =============== =============== ======================================


Commands
--------

======================= =============== =============== ===============================================================================================
Attribute name          Arg. in         Arg. out        Description
======================= =============== =============== ===============================================================================================
Init                    Void            Void            Do not use.
State                   Void            State           Return the device state.
Status                  Void            String          Return the device status as string.
GetTemperature          Void            Void            Get the temperature of the CCD sensor.
                                                        The temperature will be updated in the lastTemperature attribute. 
ForceConfig             Void            Void            Force the re-configuration of the camera.
GetGain                 Void            Void            Get the gain of the CCD camera.
                                                        The gain will be updated in the gain attribute.
======================= =============== =============== ===============================================================================================
