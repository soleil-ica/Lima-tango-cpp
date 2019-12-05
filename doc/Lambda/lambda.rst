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
DistortionCorrection    true            Boolean         Set distortion correction.

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
readoutTime             R          Float      Get readout time used during image acquisition. Depends of the operating mode (12bit/24bit).
distortionCorrection    R          Boolean    Get distortion correction.
                                              When distortion correction is enabled :

                                              - Large pixels are divided according to predefined denominator.
                                              - The values of the pixels are rounded during division.
                                              - If pixel value is saturated, the division is not applied.
energyThreshold1        R/W        Float      Set/get first energy threshold in eV.
operatingMode           R          String     Get operating mode of the detector:

                                              - 24bit mode: TwentyFourBit
                                              - 12bit mode: ContinuousReadWrite
burstMode               R          Boolean    Get the value of burst mode.

                                              - True: 10GE link.
                                              - False: 1GE link.
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
