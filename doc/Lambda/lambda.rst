LAMBDA Tango device
========================

This is the reference documentation of the XSpectrum LAMBDA Tango device.


Properties
----------
======================= =============== =============== =========================================================================
Property name           Mandatory       Default value   Description
======================= =============== =============== =========================================================================
ConfigFilesPath         Yes             /opt/xsp/config Configuration files path used during the camera instanciation.
DistortionCorrection    Yes             True            Set distortion correction.
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
configFilesPath         R          DevString  Path of configuration files.
readoutTime             R          DevFloat   Get readout time used during image acquisition. Depends of the operating mode (12bit/24bit).
distortionCorrection    R          DevBoolean Get distortion correction.
                                              When distortion correction is enabled :

                                              - Large pixels are divided according to predefined denominator.
                                              
                                              - The values of the pixels are rounded during division.
                                              
                                              - If pixel value is saturated, the division is not applied.
                                              
energyThreshold1        R/W        DevFloat   Set/get first energy threshold in eV.
operatingMode           R          DevString  Get operating mode of the detector:

                                              - 24bit mode: TwentyFourBit

                                              - 12bit mode: ContinuousReadWrite

burstMode               R          DevBoolean Get the value of burst mode.

                                              - True: 10GE link.

                                              - False: 1GE link.
======================= ========== ========== ==============================================================================================


Commands
--------
=======================	=============== =======================	===========================================
Command name            Arg. in         Arg. out                Description
=======================	=============== =======================	===========================================
Init                    DevVoid         DevVoid                 Do not use
State                   DevVoid         DevLong                 Return the device state
Status                  DevVoid         DevString               Return the device state as a string
=======================	=============== =======================	===========================================

