.. _lima-tango-xpadpixeldetector:

XpadPixelDetector C++ Tango device
==================================

This is the reference documentation of the XpadPixelDetector Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `XpadPixelDetector camera plugin`_ section.


Properties
----------

==========================  ================== ================= =====================================
Property name               Default value      Type              Description
==========================  ================== ================= =====================================
XpadModel                   UNKNOWN            String            Define the model of the XPAD (architecture). Availables models :

                                                                 - BACKPLANE
                                                                 - IMXPAD_S70
                                                                 - IMXPAD_S140
                                                                 - IMXPAD_S340
                                                                 - IMXPAD_S540
CalibrationPath             /no/path/defined   String            Path where the calibration files will be saved, and from where the calibrations will be uploaded via an UploadCalibration command
CalibrationAdjustingNumber  1                  ULong             Number of Adjusting iteration for the Calibration
XpixDebug                   false              Boolean           Flag used to enable Xpix library debug
MinLatencyTimeMs            5                  Double            Minimum LatencyTime (aka deadtime) in ms.
==========================  ================== ================= =====================================


Attributes
----------

===========================     ================  ================ =====================================
Attribute name                  Read/Write        Type             Description
===========================     ================  ================ =====================================
acquisitionType                 W                 String           Acquisition Type:

                                                                   - SYNC : Synchrone
                                                                   - ASYNC: Asynchrone
enableGeometricalCorrection     R/W               Boolean          Enable/disable Geometrical Correction (only for S540)
enableDoublePixelCorrection     R/W               Boolean          Enable/disable Double Pixel Correction (only for S140)
normalizationFactor             R/W               Double           Normalization Factor of the intensities, used for the double pixel correction algorithm 
busyOut                         W                 ULong            Selection of the busy out:

                                                                   - 0-busy
                                                                   - 1-busy shutter
                                                                   - 2-read img ena
                                                                   - 3-ovf updt ena
                                                                   - 4-exp ceg(0)
                                                                   - 5-xpad proc busy
                                                                   - 6-gpout(img transfer)
                                                                   - 7-dsfifo full
                                                                   - 8-ext gate
                                                                   - 9-init ovf update
init                            W                 ULong            time before start (in ms)
shutter                         W                 ULong            shutter time (in ms)
ovf                             W                 ULong            ovf time (in us)
n                               W                 ULong            ?    
p                               W                 ULong            ?    
gp1                             W                 ULong            ?    
gp2                             W                 ULong            ?    
gp3                             W                 ULong            ?    
gp4                             W                 ULong            ?    
===========================     ================  ================ =====================================


Commands
--------

======================= =================================== ======================= ===========================================
Command name            Arg. in                             Arg. out                Description
======================= =================================== ======================= ===========================================
Init                    Void                                Void                    Do not use
State                   Void                                Long                    Return the device state
Status                  Void                                String                  Return the device state as a string
LoadFlatConfig          ULong                               Void                    Load a Flat value to all pixels:

                                                                                    IN: Flat value to be loaded
LoadAllConfigG          VarULongArray                       Void                    Load the config G(lobal) to a module and a chip:

                                                                                    IN: modNum(1..8), chipId(0..6), config_values (11 values)
SaveConfigL             VarULongArray                       Void                    ?

                                                                                    IN: modNum(1..8), calibId(0..6), chipId(0..7), curRow (0..119), values (80 values)
SaveConfigG             VarULongArray                       Void                    ?

                                                                                    IN: modNum(1..8), calibId(0..6), reg, values (7 values)
LoadConfig              VarULongArray                       Void                    ?

                                                                                    IN: modNum(1..8), calibId(0..6)
LoadConfigG             VarULongArray                       Void                    Load a value of a wanted config G register.

                                                                                    IN: modNum(1..8), chipId(0..6), register ID, register value
                                                                                    register IDs are: 

                                                                                    - CMOS_DSBL_V32 0x01
                                                                                    - AMP_TP_V32 0x1F
                                                                                    - ITHH_V32 0x33
                                                                                    - VADJ_V32 0x35
                                                                                    - VREF_V32 0x36
                                                                                    - IMFP_V32 0x3b
                                                                                    - IOTA_V32 0x3c
                                                                                    - IPRE_V32 0x3d
                                                                                    - ITHL_V32 0x3e
                                                                                    - TUNE_V32 0x3f
                                                                                    - IBUFFER_V32 0x40
Reset                   Void                                Void                    Reset the Xpad
CalibrateOTNSlow        Void                                Void                    Start the Over The Noise Slow calibration
CalibrateOTNMedium      Void                                Void                    Start the Over The Noise Medium calibration
CalibrateOTNFast        Void                                Void                    Start the Over The Noise Fast calibration
CalibrateBEAM           VarULongArray                       Void                    Start the BEAM calibration

                                                                                    IN: Texp, ithl_max, itune, imfp
CalibrateOTN            VarULongArray                       Void                    Start the Over The Noise calibration

                                                                                    IN: itune, imfp
UploadCalibration       Void                                Void                    Upload a calibration from a directory defined in the property CalibrationPath
UploadWaitTimes         VarULongArray                       Void                    Upload a trajectory of wait times, instead of having always the same value

                                                                                    IN: the wait times
IncrementITHL           Void                                Void                    Increment the ITHL of 1 unit
DecrementITHL           Void                                Void                    Decrement  the ITHL of 1 unit                                
======================= =================================== ======================= ===========================================

.. _XpadPixelDetector camera plugin: https://lima1.readthedocs.io/en/latest/camera/xpad/doc/index.html
