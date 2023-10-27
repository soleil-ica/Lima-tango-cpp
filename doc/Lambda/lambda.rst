.. _lima-tango-lambda:

LAMBDA Tango C++ device
========================

This is the reference documentation of the XSpectrum LAMBDA Tango C++ device.


Properties
----------

======================= =========================== =============== =========================================================================
Property name           Default value               Type            Description
======================= =========================== =============== =========================================================================
ConfigFile              /opt/xsp/config/system.yml  String          Configuration file used to initialize the detector.
DistortionCorrection    false                       Boolean         Set distortion correction.

                                                                    When distortion correction is enabled :

                                                                        - Large pixels are divided according to predefined denominator.
                                                                        - The values of the pixels are rounded during division.
                                                                        - If pixel value is saturated, the division is not applied.
ChargeSumming			False						Boolean			Indicates wether charge summing mode is used or not.						
======================= =========================== =============== =========================================================================


Attributes
----------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
configFile              R          String     Configuration file used to initialize the detector.
chargeSumming           R          Boolean    Indicates wether charge summing mode is used or not.
lowerThreshold          R/W        Double     Get/Set the lower threshold settings in keV for the Lambda detector. It's a memorized attribute.
upperThreshold          R/W        Double     Get/Set the upper threshold settings in keV for the Lambda detector. It's a memorized attribute.
distortionCorrection    R          Boolean    Get whether interpolation of extra large pixels is enabled.
highVoltage             R          Double     Get the measured high voltage value from a specific detector module. (Older detector firmware might not support this command. In this case, a value of 0.0 is returned). It's a memorized attribute.
humidity                R          Double     Get the measured humidity from a specific detector module. (Older detector firmware might not support this command. In this case, the valueof 0.0 is returned).
libraryVersion          R          String     Get the version of the library as a string in the format "major.minor.patch". Available only for expert user.
temperature             R          Double     Get a vector of measured temperatures from a specific detector module. The number of values and their meaning depends on hardware revision of the detectorreadout board.For new readout boards, three values are returned: the board temperature, theFPGA temperature, and the temperature from the humidity sensor. (Older boardsdo not support this command, and an empty vector is returned).
linearityCorrection     R/W        Boolean    Enable/Disable correction of counts. It's a memorized attribute.
saturationFlag          R/W        Boolean    Enable/Disable flagging of saturated pixels. It's a memorized attribute.
saturationThreshold     R/W        Long       Saturation threshold in counts/sec/pixel. It's a memorized attribute.
======================= ========== ========== ==============================================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================
