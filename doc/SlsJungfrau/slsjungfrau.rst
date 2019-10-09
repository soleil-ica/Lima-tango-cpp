.. _lima-tango-slsjungfrau:

SlsJungfrau C++ Tango device
=============================

This is the reference documentation of the SimulatorCDD Tango C++ device.


Properties
----------
======================= =============== =============== =========================================================================
Property name           Default value   Type            Description
======================= =============== =============== =========================================================================
ConfigFileName          N/A             String          Configuration files used during the camera instanciation.
ExpertReadoutTime       N/A             Double          This is the readout time in seconds of the camera.
ExpertReceiverFifoDepth N/A             Long            This is the number of frames in the receiver memory.
ExpertFramePacketNumber N/A             Long            This is the number of packet for each received frame part.
======================= =============== =============== =========================================================================


Attributes
----------

======================= ========== ========= ==============================================================================================
Attribute name          Read/Write Type      Description
======================= ========== ========= ==============================================================================================
clockDivider            R/W        String    Change the readout clock. Available clock divider :

                                             - FULL_SPEED
                                             - HALF_SPEED
                                             - QUARTER_SPEED
                                             - SUPER_SLOW_SPEED
configFileName          R          String    Configuration files used during the camera instanciation.
delayAfterTrigger       R/W        Double    Set/get delay after trigger in ms.
detectorFirmwareVersion R          String    Get detector firmware version.
detectorSoftwareVersion R          String    Get detector software version.
======================= ========== ========= ==============================================================================================


Commands
--------
======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
SetCmd                  String          String                  Allow to execute a line command (set type)
GetCmd                  String          String                  Allow to execute a line command (get type)
ResetCamera             Void            Void                    Execute an hardware reset of the camera. 
======================= =============== ======================= ===========================================
