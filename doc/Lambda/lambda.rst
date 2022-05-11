.. _lima-tango-lambda:

LAMBDA Tango C++ device
========================

This is the reference documentation of the XSpectrum LAMBDA Tango C++ device.


Properties
----------

======================= =============== =============== =========================================================================
Property name           Default value   Type            Description
======================= =============== =============== =========================================================================
ConfigFilesPath         /opt/xsp/config String          Configuration files path used during the camera instanciation.
DistortionCorrection    false           Boolean         Set distortion correction.

                                                        When distortion correction is enabled :

                                                        - Large pixels are divided according to predefined denominator.
                                                        - The values of the pixels are rounded during division.
                                                        - If pixel value is saturated, the division is not applied.
======================= =============== =============== =========================================================================


Attributes
----------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
configFilesPath         R          String     Path of configuration files.
energyThreshold         R/W        Double     Get/Set the threshold settings in keV for the Lambda detector.
distortionCorrection    R          Boolean    Get whether interpolation of extra large pixels is enabled.
highVoltage             R          Double     Get the measured high voltage value from a specific detector module. (Older detector firmware might not support this command. In this case, the attribute is displayed as INVALID).
humidity                R          Double     Get the measured humidity from a specific detector module. (Older detector firmware might not support this command. In this case,  the attribute is displayed as INVALID).
libraryVersion          R          String     Get the version of the library as a string in the format "major.minor.patch".
temperature             R          Double     Get the board temperature from the specific detector module. (Older boards do not support this command, and, in this case,  the attribute is displayed as INVALID).
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
