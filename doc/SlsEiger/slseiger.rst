SlsEiger Tango device
========================

This is the reference documentation of the Sls Eiger Tango device.


Properties
----------
=============================== =============== ====== ===================================================================
Property name                   Default value   Type   Description
=============================== =============== ====== ===================================================================
ConfigFileName 	                N/A             String Configuration files used during the camera instanciation.
ExpertReadoutTime               0.00004 (40µs)  Double Readout time in seconds of the camera.
ExpertReceiverFifoDepth         8000            ULong  Number of frames in the receiver memory.
ExpertFramePacketNumber8        32              ULong  Number of packet for each received frame part in bit depth 8 bits.
ExpertFramePacketNumber16       64              ULong  Number of packet for each received frame part in bit depth 16 bits.
ExpertFramePacketNumber32       128             ULong  Number of packet for each received frame part in bit depth 32 bits.
ExpertLiveModeMinFramePeriodSec 1.0             Double Minimum period in seconds between frames for the live mode.
=============================== =============== ====== ===================================================================


Attributes
----------

============================= ========== ======= =================================================================================================================
Attribute name                Read/Write Type       Description
============================= ========== ======= =================================================================================================================
clockDivider                  R/W        String  Change the readout clock. Available clock dividers :

                                                    - FULL_SPEED (equivalent to the 0 sls value)
                                             
                                                    - HALF_SPEED (equivalent to the 1 sls value)
                                             
                                                    - QUARTER_SPEED (equivalent to the 2 sls value)
                                             
                                                    - SUPER_SLOW_SPEED (currently not used)
                                             
                                             
parallelMode                  R/W        String  Change the parallel mode. Available modes :

                                                    - NON_PARALLEL
                                             
                                                    - PARALLEL
                                             
                                                    - SAFE
                                             
                                             
overflowMode                  R/W        Boolean When activated, shows saturated for overflow in subframes in 32 bits mode.
subFrameExposureTime          R/W        Double  Set sub frame exposure time for 32 bits mode.
gainMode                      R/W        String  Change the gain mode. Available modes :

                                                    - STANDARD
                                             
                                                    - LOW (currently not used)
                                             
                                                    - MEDIUM (currently not used)
                                             
                                                    - HIGH (currently not used)
                                             
                                                    - VERY_HIGH (currently not used)
                                             
                                             
thresholdEnergy               R/W        Long    Set/Get threshold energy for modules in eV.
countRateCorrectionActivation R/W        Boolean Set/Get count rate correction activation value.
countRateCorrection           R          Long    Get count rate correction in ns.
                                                    When the count rate correction is disabled, the value will be 0.
gapPixelsActivation           R/W        Boolean Set/Get gap pixels management activation value.
edgePixelsCorrection          R/W        Double  Set/Get correction value for edge pixels (double in size).
cornerPixelsCorrection        R/W        Double  Set/Get correction value for corner pixels (four-times the normal size).
configFileName                R          String  Configuration files used during the camera instanciation.
detectorFirmwareVersion       R          String  Get detector firmware version.
detectorSoftwareVersion       R          String  Get detector software version.
tempFpga1                     R          Long    Get temperature of hardware element (fpga) for first module in millidegree Celsius.
tempFpga2                     R          Long    Get temperature of hardware element (fpga) for second module in millidegree Celsius.
tempFpgaext1                  R          Long    Get temperature of hardware element (close to the fpga) for first module in millidegree Celsius.
tempFpgaext2                  R          Long    Get temperature of hardware element (close to the fpga) for second module in millidegree Celsius.
temp10ge1                     R          Long    Get temperature of hardware element (close to the 10GE) for first module in millidegree Celsius.
temp10ge2                     R          Long    Get temperature of hardware element (close to the 10GE) for second module in millidegree Celsius.
tempDcdc1                     R          Long    Get temperature of hardware element (close to the dc dc converter) for first module in millidegree Celsius.
tempDcdc2                     R          Long    Get temperature of hardware element (close to the dc dc converter) for second module in millidegree Celsius.
tempSodl1                     R          Long    Get temperature of hardware element (close to the left so-dimm memory) for first module in millidegree Celsius.
tempSodl2                     R          Long    Get temperature of hardware element (close to the left so-dimm memory) for second module in millidegree Celsius.
tempSodr1                     R          Long    Get temperature of hardware element (close to the right so-dimm memory) for first module in millidegree Celsius.
tempSodr2                     R          Long    Get temperature of hardware element (close to the right so-dimm memory) for second module in millidegree Celsius.
tempFpgafl1                   R          Long    Get temperature of hardware element (left front end board fpga) for first module in millidegree Celsius.
tempFpgafl2                   R          Long    Get temperature of hardware element (left front end board fpga) for second module in millidegree Celsius.
tempFpgafr1                   R          Long    Get temperature of hardware element (right front end board fpga) for first module in millidegree Celsius.
tempFpgafr2                   R          Long    Get temperature of hardware element (right front end board fpga) for second module in millidegree Celsius.
============================= ========== ======= =================================================================================================================


Commands
--------
======================= ======= ======== ===========================================
Command name            Arg. in Arg. out Description
======================= ======= ======== ===========================================
Init                    Void    Void     Do not use
State                   Void    Long     Return the device state
Status                  Void    String   Return the device state as a string
SetCmd                  String  String   Allow to execute a line command (set type)
GetCmd                  String  String   Allow to execute a line command (get type)
======================= ======= ======== ===========================================

