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
GpibBoardAddress        0                                       Long            Index of the NI GPIB board.
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
SimpleCommandTimeout    T3s                                     String          Default timeout for commands:
                                                                                TNONE   Infinite timeout
                                                                                T10us   Timeout of 10 us
                                                                                T30us   Timeout of 30 us
                                                                                T100us  Timeout of 100 us
                                                                                T300us  Timeout of 300 us
                                                                                T1ms    Timeout of 1 ms
                                                                                T3ms    Timeout of 3 ms
                                                                                T10ms   Timeout of 10 ms
                                                                                T30ms   Timeout of 30 ms
                                                                                T100ms  Timeout of 100 ms
                                                                                T300ms  Timeout of 300 ms
                                                                                T1s     Timeout of 1 s
                                                                                T3s     Timeout of 3 s
                                                                                T10s    Timeout of 10 s
                                                                                T30s    Timeout of 30 s
                                                                                T100s   Timeout of 100 s
                                                                                T300s   Timeout of 300 s
                                                                                T1000s  Timeout of 1000 s
DataAcquisitionTimeout  T100s                                   String          Timeout for data reception:
                                                                                TNONE   Infinite timeout
                                                                                T10us   Timeout of 10 us
                                                                                T30us   Timeout of 30 us
                                                                                T100us  Timeout of 100 us
                                                                                T300us  Timeout of 300 us
                                                                                T1ms    Timeout of 1 ms
                                                                                T3ms    Timeout of 3 ms
                                                                                T10ms   Timeout of 10 ms
                                                                                T30ms   Timeout of 30 ms
                                                                                T100ms  Timeout of 100 ms
                                                                                T300ms  Timeout of 300 ms
                                                                                T1s     Timeout of 1 s
                                                                                T3s     Timeout of 3 s
                                                                                T10s    Timeout of 10 s
                                                                                T30s    Timeout of 30 s
                                                                                T100s   Timeout of 100 s
                                                                                T300s   Timeout of 300 s
                                                                                T1000s  Timeout of 1000 s
======================= ======================================= =============== =========================================================================


Attributes
----------

======================= =============== =============== ======================================
Attribute name          Read/Write      Type            Description
======================= =============== =============== ======================================
lastTemperature         Read            Double          Last temperature of the CCD.
gain                    Read/Write      Long            CCD gain of the camera.
numFlushes              Read/Write      Long            Set number of flushes on the camera
openShutter             Read/Write      Boolean         Open/close camera shutter.
                                                        True = Opened
                                                        False = Closed
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
