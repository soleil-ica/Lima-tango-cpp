SlsJungfrau Tango device
========================

This is the reference documentation of the Sls Jungfrau Tango device.


Properties
----------
======================= =============== =============== =========================================================================
Property name           Mandatory       Default value   Description
======================= =============== =============== =========================================================================
ConfigFileName 	        Yes             N/A             Configuration files used during the camera instanciation.
ExpertReadoutTime       Yes             N/A             This is the readout time in seconds of the camera.
ExpertReceiverFifoDepth Yes             N/A             This is the number of frames in the receiver memory.
ExpertFramePacketNumber Yes             N/A             This is the number of packet for each received frame part.
======================= =============== =============== =========================================================================


Attributes
----------

======================= ========== ========= ==============================================================================================
Attribute name		Read/Write Type		 Description
======================= ========== ========= ==============================================================================================
clockDivider            R/W        DevString Change the readout clock. Available clock divider :

                                             - FULL_SPEED
                                             
                                             - HALF_SPEED
                                             
                                             - QUARTER_SPEED
                                             
                                             - SUPER_SLOW_SPEED
                                             
                                             
configFileName 	        R          DevString Configuration files used during the camera instanciation.
delayAfterTrigger       R/W        DevDouble set/get delay after trigger in ms.
detectorFirmwareVersion R          DevString Get detector firmware version.
detectorSoftwareVersion R          DevString Get detector software version.
======================= ========== ========= ==============================================================================================


Commands
--------
=======================	=============== =======================	===========================================
Command name            Arg. in         Arg. out                Description
=======================	=============== =======================	===========================================
Init                    DevVoid         DevVoid                 Do not use
State                   DevVoid         DevLong                 Return the device state
Status                  DevVoid         DevString               Return the device state as a string
SetCmd                  DevString       DevString               Allow to execute a line command (set type)
GetCmd                  DevString       DevString               Allow to execute a line command (get type)
ResetCamera             DevVoid         DevVoid                 Execute an hardware reset of the camera. 
=======================	=============== =======================	===========================================

