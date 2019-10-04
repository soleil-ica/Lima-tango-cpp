SlsEiger Tango device
========================

This is the reference documentation of the Sls Eiger Tango device.


Properties
----------
=============================== =============== =============== ===================================================================
Property name                   Mandatory       Default value   Description
=============================== =============== =============== ===================================================================
ConfigFileName 	                Yes             N/A             Configuration files used during the camera instanciation.
ExpertReadoutTime               Yes             0.00004 (40µs)  Readout time in seconds of the camera.
ExpertReceiverFifoDepth         Yes             8000            Number of frames in the receiver memory.
ExpertFramePacketNumber8        Yes             32              Number of packet for each received frame part in bit depth 8 bits.
ExpertFramePacketNumber16       Yes             64              Number of packet for each received frame part in bit depth 16 bits.
ExpertFramePacketNumber32       Yes             128             Number of packet for each received frame part in bit depth 32 bits.
ExpertLiveModeMinFramePeriodSec Yes             1.0             Minimum period in seconds between frames for the live mode.
=============================== =============== =============== ===================================================================


Attributes
----------

============================= ========== ========== =================================================================================================================
Attribute name                Read/Write Type       Description
============================= ========== ========== =================================================================================================================
clockDivider                  R/W        DevString  Change the readout clock. Available clock dividers :

                                                    - FULL_SPEED (equivalent to the 0 sls value)
                                             
                                                    - HALF_SPEED (equivalent to the 1 sls value)
                                             
                                                    - QUARTER_SPEED (equivalent to the 2 sls value)
                                             
                                                    - SUPER_SLOW_SPEED (currently not used)
                                             
                                             
parallelMode                  R/W        DevString  Change the parallel mode. Available modes :

                                                    - NON_PARALLEL
                                             
                                                    - PARALLEL
                                             
                                                    - SAFE
                                             
                                             
overflowMode                  R/W        DevBoolean When activated, shows saturated for overflow in subframes in 32 bits mode.
subFrameExposureTime          R/W        DevDouble  Set sub frame exposure time for 32 bits mode.
gainMode                      R/W        DevString  Change the gain mode. Available modes :

                                                    - STANDARD
                                             
                                                    - LOW (currently not used)
                                             
                                                    - MEDIUM (currently not used)
                                             
                                                    - HIGH (currently not used)
                                             
                                                    - VERY_HIGH (currently not used)
                                             
                                             
thresholdEnergy               R/W        DevLong    Set/Get threshold energy for modules in eV.
countRateCorrectionActivation R/W        DevBoolean Set/Get count rate correction activation value.
countRateCorrection           R          DevLong    Get count rate correction in ns.
                                                    When the count rate correction is disabled, the value will be 0.
configFileName                R          DevString  Configuration files used during the camera instanciation.
detectorFirmwareVersion       R          DevString  Get detector firmware version.
detectorSoftwareVersion       R          DevString  Get detector software version.
tempFpga1                     R          DevLong    Get temperature of hardware element (fpga) for first module in millidegree Celsius.
tempFpga2                     R          DevLong    Get temperature of hardware element (fpga) for second module in millidegree Celsius.
tempFpgaext1                  R          DevLong    Get temperature of hardware element (close to the fpga) for first module in millidegree Celsius.
tempFpgaext2                  R          DevLong    Get temperature of hardware element (close to the fpga) for second module in millidegree Celsius.
temp10ge1                     R          DevLong    Get temperature of hardware element (close to the 10GE) for first module in millidegree Celsius.
temp10ge2                     R          DevLong    Get temperature of hardware element (close to the 10GE) for second module in millidegree Celsius.
tempDcdc1                     R          DevLong    Get temperature of hardware element (close to the dc dc converter) for first module in millidegree Celsius.
tempDcdc2                     R          DevLong    Get temperature of hardware element (close to the dc dc converter) for second module in millidegree Celsius.
tempSodl1                     R          DevLong    Get temperature of hardware element (close to the left so-dimm memory) for first module in millidegree Celsius.
tempSodl2                     R          DevLong    Get temperature of hardware element (close to the left so-dimm memory) for second module in millidegree Celsius.
tempSodr1                     R          DevLong    Get temperature of hardware element (close to the right so-dimm memory) for first module in millidegree Celsius.
tempSodr2                     R          DevLong    Get temperature of hardware element (close to the right so-dimm memory) for second module in millidegree Celsius.
tempFpgafl1                   R          DevLong    Get temperature of hardware element (left front end board fpga) for first module in millidegree Celsius.
tempFpgafl2                   R          DevLong    Get temperature of hardware element (left front end board fpga) for second module in millidegree Celsius.
tempFpgafr1                   R          DevLong    Get temperature of hardware element (right front end board fpga) for first module in millidegree Celsius.
tempFpgafr2                   R          DevLong    Get temperature of hardware element (right front end board fpga) for second module in millidegree Celsius.
============================= ========== ========== =================================================================================================================


Commands
--------
======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    DevVoid         DevVoid                 Do not use
State                   DevVoid         DevLong                 Return the device state
Status                  DevVoid         DevString               Return the device state as a string
SetCmd                  DevString       DevString               Allow to execute a line command (set type)
GetCmd                  DevString       DevString               Allow to execute a line command (get type)
======================= =============== ======================= ===========================================

