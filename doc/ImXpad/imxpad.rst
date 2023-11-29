.. _lima-tango-imxpad:

ImXpad C++ Tango device
=======================

This is the reference documentation of the ImXpad Tango device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `ImXpad camera plugin`_ section.


Properties
----------

================= ================= =============== =========================================================================
Property name     Default value     Type            Description
================= ================= =============== =========================================================================
HostName          127.0.0.1         String          Host name /Adress IP of the XPAD SERVER
Port              3456              Long            Host port of the XPAD SERVER
CalibrationPath   MUST_BE_DEFINED   String          Path where calibration files are stored
ModuleMask        0                 String          Define the modules Mask.

                                                    Each bit of this Mask fix if a specific module is enabled or disabled.

                                                    Value must be in Hexadecimal format.
================= ================= =============== =========================================================================


Attributes
----------
========================= =========== ======================= ======================================================================
Attribute name            Read/Write      Type                    Description
========================= =========== ======================= ======================================================================
serverVersion             R           String                  ImXpad Socket Server Version.
geometricalCorrectionFlag R/W         Boolean                 Enable/Disable Geometrical correction
flatFieldCorrectionFlag   R/W         Boolean                 Enable/Disable Flatfield correction
acquisitionMode           R/W         String                  Define the acquisition mode of the detector :

                                                              - STANDARD
                                                              - COMPUTER_BURST
                                                              - DETECTOR_BURST
                                                              - SINGLE_BUNCH_16
                                                              - SINGLE_BUNCH_32
                                                              - STACKING_16
                                                              - STACKING_32
nbStackingImages          W           ULong                   Define the number of images to acquire in the acquisition mode :

                                                              - STACKING_16
                                                              - STACKING/32
outputSignal              R/W         String                  Define the activate output signal of the detector :

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
calibrationFileName       R           String                  Define the loaded calibration file name
calibrationPath           R           String                  Define where calibration files are stored
calibrationMode           W           String                  Define the calibration mode :

                                                              - OTN
                                                              - OTN_PULSE
                                                              - BEAM
calibrationConfigMode     W           String                  Define the calibration configuration mode :

                                                              - SLOW
                                                              - MEDIUM
                                                              - FAST
calibrationExposureTime   W           ULong                   Define the calbration exposure time
calibrationBeamITHL       W           ULong                   Define the limit of the threshold scan during calibration
========================= =========== ======================= ======================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    It's recommanded to use the command Init of the Generic Device LimaDetector
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
StartCalibration        Void            Void                    Start the calibration of detector
SaveCalibrationFile     String          Void                    Save the calibration already done through the StartCalibartion in a file
LoadCalibrationFile     String          Void                    Load a calibration file 
CreateWhiteImage        String          Void                    Create the White image
ChooseWhiteImage        String          Void                    Select the white image
GetWhiteImagesList      Void            StringArray             Display the list of available White images
DeleteWhiteImage        String          Void                    Delete the white image
Abort                   Void            Void                    Abort current process ...
ITHLIncrease            Void            Void                    Increment of one unit of the global ITHL register
ITHLDecrease            Void            Void                    Decrement of one unit in the global ITHL register
======================= =============== ======================= ===========================================

.. _ImXpad camera plugin: https://lima1.readthedocs.io/en/latest/camera/imxpad/doc/index.html
