ImXpad Tango device
=======================

This is the reference documentation of the ImXpad Tango device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the :ref:`ImXPAD camera plugin <camera-imxpad>` section.


Properties
----------

================= =============== =============== =========================================================================
Property name     Mandatory       Default value   Description
================= =============== =============== =========================================================================
HostName          Yes             127.0.0.1       Host name /Adress IP of the XPAD SERVER
Port              Yes             3456            Host port of the XPAD SERVER
CalibrationPath   Yes             MUST_BE_DEFINED Path where calibration files are stored
================= =============== =============== =========================================================================

Attributes
----------
========================= ======= ======================= ======================================================================
Attribute name            RW      Type                    Description
========================= ======= ======================= ======================================================================
geometricalCorrectionFlag rw      DevBoolean              Enable/Disable Geometrical correction
flatFieldCorrectionFlag   rw      DevBoolean              Enable/Disable Flatfield correction
acquisitionMode           rw      DevString               Define the acquisition mode of the detector :

                                                          - STANDARD
                                                          - COMPUTER_BURST
                                                          - DETECTOR_BURST
                                                          - SINGLE_BUNCH_16
                                                          - SINGLE_BUNCH_32
                                                          - STACKING_16
                                                          - STACKING_32
nbStackingImages          w       DevULong                Define the number of images to acquire in the acquisition mode :
                                                          
                                                          - STACKING_16
                                                          - STACKING/32
outputSignal              rw      DevString               Define the activate output signal of the detector :

                                                          - EXPOSURE_BUSY
                                                          - EXPOSURE_READ_DONE
                                                          - SHUTTER_BUSY
                                                          - UPDATE_OVERFLOW_BUSY
                                                          - PIXEL_COUNTER_ENABLED
                                                          - EXTERNAL_GATE
                                                          - DATA_TRANSFER
                                                          - RAM_READY_IMAGE_BUSY
                                                          - XPAD_TO_LOCAL_DDR
                                                          - LOCAL_DDR_TO_PC

calibrationFileName       rw      DevString               Define the calibration file name
calibrationMode           w       DevString               Define the calibration mode :

                                                          - OTN
                                                          - OTN_PULSE
                                                          - BEAM
mode                      w       DevString               Define the calibration configuration mode :

                                                          - SLOW
                                                          - MEDIUM
                                                          - FAST
time                      w       DevULong                Define the calbration exposure time
iTHL                      w       DevULong                Define the limit of the threshold scan during calibration
========================= ======= ======================= ======================================================================

Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    DevVoid         DevVoid                 It's recommanded to use the command Init of the Generic Device LimaDetector
State                   DevVoid         DevLong                 Return the device state
Status                  DevVoid         DevString               Return the device state as a string
StartCalibration        DevVoid         DevVoid                 Start the calibration of detector
SaveCalibrationFile     DevString       DevVoid                 Save the calibration already done through the StartCalibartion in a file
LoadCalibrationFile     DevString       DevVoid                 Load a calibration file 
CreateWhiteImage        DevString       DevVoid                 Create the White image
ChooseWhiteImage        DevString       DevVoid                 Select the white image
GetWhiteImagesList      DevVoid         DevVarStringArray       Display the list of available White images
DeleteWhiteImage        DevString       DevVoid                 Delete the white image
Abort                   DevVoid         DevVoid                 Abort current process ...
ITHLIncrease            DevVoid         DevVoid                 Increment of one unit of the global ITHL register
ITHLDecrease            DevVoid         DevVoid                 Decrement of one unit in the global ITHL register
======================= =============== ======================= ===========================================



