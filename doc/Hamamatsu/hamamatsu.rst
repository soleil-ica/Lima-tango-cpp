Hamamatsu C++ Tango device
==========================

This is the reference documentation of the Hamamatsu Tango device.


Properties
----------
========================= =============== =============== =========================================================================
Property name             Mandatory       Default value   Description
========================= =============== =============== =========================================================================
DetectorNum               Yes             N/A             id of the camera.
BlankOfSyncreadoutTrigger Yes             N/A             Allows you to select the blank of synreadout. Availables values:

                                                          - STANDARD
                                                          
                                                          - MINIMUM
========================= =============== =============== =========================================================================


Attributes
----------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
readoutSpeed            R/W        DevString  Readout speed . Possible values are:
                                              
                                              - NORMAL
                                              
                                              - SLOW
                                              
lostFrames              R          DevLong    Number of frames lost during the current or last acquisition.
fps                     R          DevDouble  The last computed frame per second (the value is computed every 100 frames only).
wViewEnabled            R/W        DevBoolean Activation state of the W-VIEW mode.
topViewExposureTime     R/W        DevDouble  Exposure time for first W-VIEW.
bottomViewExposureTime  R/W        DevDouble  Exposure time for second W-VIEW.
Temperature             R          DevDouble  Temperature of the image sensor in Celcius.
======================= ========== ========== ==============================================================================================


Commands
--------
=======================	=============== =======================	===========================================
Command name            Arg. in         Arg. out                Description
=======================	=============== =======================	===========================================
Init                    DevVoid         DevVoid                 Do not use.
State                   DevVoid         DevLong                 Return the device state.
Status                  DevVoid         DevString               Return the device state as a string.
=======================	=============== =======================	===========================================

