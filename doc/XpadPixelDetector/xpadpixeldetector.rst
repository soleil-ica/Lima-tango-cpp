XpadPixelDetector C++ Tango device
==================================

This is the reference documentation of the XpadPixelDetector Tango C++ device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `XpadPixelDetector camera plugin`_ section.

Properties
----------

==========================  ================================= =====================================
Property name	            Default value	                  Description
==========================  ================================= =====================================
XpadModel                   UNKNOWN                           Define the model of the XPAD (architecture). Availables models :
                                                                - **BACKPLANE**
                                                                - **IMXPAD_S70**
                                                                - **IMXPAD_S140**
                                                                - **IMXPAD_S340**
                                                                - **IMXPAD_S540**
CalibrationPath             /no/path/defined                  Path where the calibration files will be saved, and from where the calibrations will be uploaded via an UploadCalibration command
CalibrationAdjustingNumber  1                                 Number of Adjusting iteration for the Calibration
XpixDebug                   false                             Flag used to enable Xpix library debug
MinLatencyTimeMs            5                                 Minimum LatencyTime (aka deadtime) in ms.
==========================  ================================= =====================================

Attributes
----------

===========================     ================  ================ =====================================
Attribute name	                Read/Write        Type             Description
===========================     ================  ================ =====================================
acquisitionType                 W                 DevString        Acquisition Type:
                                                                    - **SYNC** : Synchrone
                                                                    - **ASYNC**: Asynchrone
enableGeometricalCorrection     R/W               DevBoolean       Enable/disable Geometrical Correction (only for S540)
enableDoublePixelCorrection     R/W               DevBoolean       Enable/disable Double Pixel Correction (only for S140)
normalizationFactor             R/W               DevDouble        Normalization Factor of the intensities, used for the double pixel correction algorithm 
busyOut                         W                 DevULong         Selection of the busy out: 
                                                                    - **0-busy**
                                                                    - **1-busy shutter**
                                                                    - **2-read img ena**
                                                                    - **3-ovf updt ena**
                                                                    - **4-exp ceg(0)**
                                                                    - **5-xpad proc busy**
                                                                    - **6-gpout(img transfer)**
                                                                    - **7-dsfifo full**
                                                                    - **8-ext gate**
                                                                    - **9-init ovf update**
init                            W                 DevULong          time before start (in ms)
shutter                         W                 DevULong          shutter time (in ms)
ovf                             W                 DevULong          ovf time (in us)
n                               W                 DevULong          ?    
p                               W                 DevULong          ?    
gp1                             W                 DevULong          ?    
gp2                             W                 DevULong          ?    
gp3                             W                 DevULong          ?    
gp4                             W                 DevULong          ?    
===========================     ================  ================ =====================================

Commands
--------

=======================	=================================== =======================	===========================================
Command name		    Arg. in		                        Arg. out		        Description
=======================	=================================== =======================	===========================================
Init			        DevVoid 	                        DevVoid			        Do not use
State			        DevVoid		                        DevLong			        Return the device state
Status			        DevVoid		                        DevString		        Return the device state as a string
LoadFlatConfig          DevULong                            DevVoid                 Load a Flat value to all pixels:
                                                                                        IN: Flat value to be loaded
LoadAllConfigG          DevVarULongArray                    DevVoid                 Load the config G(lobal) to a module and a chip:
                                                                                        IN: modNum(1..8), chipId(0..6), config_values (11 values)
SaveConfigL             DevVarULongArray                    DevVoid                 ?
                                                                                        IN: modNum(1..8), calibId(0..6), chipId(0..7), curRow (0..119), values (80 values)
SaveConfigG             DevVarULongArray                    DevVoid                 ?
                                                                                        IN: modNum(1..8), calibId(0..6), reg, values (7 values)
LoadConfig              DevVarULongArray                    DevVoid                 ?
                                                                                        IN: modNum(1..8), calibId(0..6)
LoadConfigG             DevVarULongArray                    DevVoid                 Load a value of a wanted config G register.
                                                                                        IN: modNum(1..8), chipId(0..6), register ID, register value
                                                                                        register IDs are: 
                                                                                        
                                                                                        - **CMOS_DSBL_V32 0x01**
                                                                                        - **AMP_TP_V32 0x1F** 
                                                                                        - **ITHH_V32 0x33** 
                                                                                        - **VADJ_V32 0x35** 
                                                                                        - **VREF_V32 0x36** 
                                                                                        - **IMFP_V32 0x3b** 
                                                                                        - **IOTA_V32 0x3c** 
                                                                                        - **IPRE_V32 0x3d** 
                                                                                        - **ITHL_V32 0x3e** 
                                                                                        - **TUNE_V32 0x3f** 
                                                                                        - **IBUFFER_V32 0x40**   
                                                                                        
                                                                                        
Reset                   DevVoid                             DevVoid                 Reset the Xpad
CalibrateOTNSlow        DevVoid                             DevVoid                 Start the Over The Noise Slow calibration
CalibrateOTNMedium      DevVoid                             DevVoid                 Start the Over The Noise Medium calibration
CalibrateOTNFast        DevVoid                             DevVoid                 Start the Over The Noise Fast calibration
CalibrateBEAM           DevVarULongArray                    DevVoid                 Start the BEAM calibration
                                                                                        IN: Texp, ithl_max, itune, imfp
CalibrateOTN            DevVarULongArray                    DevVoid                 Start the Over The Noise calibration
                                                                                        IN: itune, imfp
UploadCalibration       DevVoid                             DevVoid                 Upload a calibration from a directory defined in the property CalibrationPath
UploadWaitTimes         DevVarULongArray                    DevVoid                 Upload a trajectory of wait times, instead of having always the same value
                                                                                        IN: the wait times
IncrementITHL           DevVoid                             DevVoid                 Increment the ITHL of 1 unit
DecrementITHL           DevVoid                             DevVoid                 Decrement  the ITHL of 1 unit                                
=======================	=================================== =======================	===========================================

.. _XpadPixelDetector camera plugin: http://lima.blissgarden.org/camera/xpad/doc/index.html
