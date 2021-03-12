.. _lima-tango-slsjungfrau:

SlsJungfrau C++ Tango device
=============================

This is the reference documentation of the SlsJungfrau Tango C++ device.


Properties
----------
========================== =============== =============== =============================================================================
Property name              Default value   Type            Description
========================== =============== =============== =============================================================================
ConfigFileName             N/A             String          Configuration files used during the camera instanciation.
ExpertReadoutTime          0.00004         Double          Readout time in seconds of the camera.
ExpertReceiverFifoDepth    2500            Long            Number of frames in the receiver memory.
ExpertFramePacketNumber    128             Long            Number of packet for each received frame part.
ExpertGainsCoeffsFileName  N/A             String          Complete path of the gains coefficients file.
ExpertPedestalFileName1    N/A             String          Complete path of a pedestal image (first gain).
ExpertPedestalFileName2    N/A             String          Complete path of a pedestal image (second gain).
ExpertPedestalFileName3    N/A             String          Complete path of a pedestal image (third gain).
ExpertPedestalNbFrames1    5000            Long            Number of frames used to generate a pedestal image (first gain).
ExpertPedestalNbFrames2    1000            Long            Number of frames used to generate a pedestal image (second gain).
ExpertPedestalNbFrames3    1000            Long            Number of frames used to generate a pedestal image (third gain).
========================== =============== =============== =============================================================================


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
gainMode                R/W        String    Change the gain mode. Available modes :

                                             - DYNAMIC (dynamic gain settings)
                                         
                                             - DYNAMICHG0 (dynamic high gain 0)
                                         
                                             - FIXGAIN1 (fix gain 1)
                                         
                                             - FIXGAIN2 (fix gain 2)
                                         
                                             - FORCESWITCHG1 (force switch gain 1)
                                         
                                             - FORCESWITCHG2 (force switch gain 2)
gainCoeffsFileName      R          String    Shows the complete path for the gains'coefficients file.
pedestalFileName1       R          String    Shows the complete path for the pedestal file of the first gain.
pedestalFileName2       R          String    Shows the complete path for the pedestal file of the second gain.
pedestalFileName3       R          String    Shows the complete path for the pedestal file of the third gain.
gainCoeffsState         R          String    Shows the status of the gains coefficients state :

                                             - NONE (not loaded)
                                             - LOADED
calibrationState        R          String    Shows the status of the calibration state :

                                             - NONE (no calibration loaded or generated)
                                             - LOADED (a previous saved calibration was loaded)
                                             - RUNNING_0_3 (a calibration is running and at the moment no pedestal was generated)
                                             - RUNNING_1_3 (a calibration is running and the first pedestal was generated)
                                             - RUNNING_2_3 (a calibration is running and two pedestals were generated)
                                             - GENERATED (a new calibration was done)
gainCoeffs1             R          Double    Shows the coefficients for the first gain.
gainCoeffs2             R          Double    Shows the coefficients for the second gain.
gainCoeffs3             R          Double    Shows the coefficients for the third gain.
pedestal1               R          UShort    Shows the pedestal image for the first gain.
pedestal2               R          UShort    Shows the pedestal image for the second gain.
pedestal3               R          UShort    Shows the pedestal image for the third gain.
======================= ========== ========= ==============================================================================================


Commands
--------
======================= =============== ======================= =========================================================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= =========================================================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
SetCmd                  String          String                  Allow to execute a line command (set type)
GetCmd                  String          String                  Allow to execute a line command (get type)
ResetCamera             Void            Void                    Execute an hardware reset of the camera. 
Calibrate               Void            Void                    Execute a calibration of the camera by creating the three pedestal files.
======================= =============== ======================= =========================================================================
