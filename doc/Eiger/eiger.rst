Eiger C++ Tango device
======================

This is the reference documentation of the Eiger Tango C++ device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Eiger camera plugin`_ section.

Properties
----------

======================== ================================= =====================================
Property name	         Default value	                   Description
======================== ================================= =====================================
DetectorIP               127.0.0.1                         Eiger server IP address (ex: 192.168.0.1)
======================== ================================= =====================================

Attributes
----------

===========================     ================  ================ =====================================
Attribute name	                Read/Write        Type             Description
===========================     ================  ================ =====================================
countrateCorrection             R/W               Boolean          Enables (True) or disables (False)
                                                                   countrate correction. Should always be
                                                                   enabled.        
flatfieldCorrection             R/W               Boolean          Enables (True) or disables (False)
                                                                   flatfield correction.
pixelMask                       R/W               Boolean          A bit mask that labels and classifies
                                                                   pixels which are either defective,
                                                                   inactive or not exhibit non-standard
                                                                   behavior.
                                                                   0 gap (pixel with no sensor)
                                                                   1 dead
                                                                   2 under responding
                                                                   3 over responding
                                                                   4 noisy
                                                                   5-31 -undefined        
virtualPixelCorrection          R/W               Boolean          Enables (True) or disables (False)
                                                                   virtual pixel correction.        
autoSummation                   R/W               Boolean          Enables (True) or disables (False) autosummation.        
compression                     R/W               Boolean          Enables (True) or disables (False) compression
                                                                   of detector data written to
                                                                   HDF5 files. Compression is required
                                                                   for full detector performance, disabling
                                                                   compression may lead to data loss
                                                                   at high frame rates. 
dataCollectionDate              R                 String           Date and time of data collection.
                                                                   Specifically this is the time when the
                                                                   ARM command was issued         
thresholdEnergy                 R/W               Double           Threshold energy for X-ray counting.
                                                                   Photons with an energy below the
                                                                   threshold are not detected.
photonEnergy                    R/W               Double           Energy of incident X-rays.
wavelength                      R/W               Double           Wavelength of incident X-rays.
beamCenterX                     R/W               Double           Beam position on detector.
beamCenterY                     R/W               Double           Beam position on detector.
detectorDistance                R/W               Double           Sample to detector distance.
temperature                     R                 Double           Detector temperature.
humidity                        R                 Double           Humidity inside the detector module
                                                                   compartment.
chiIncrement                    R/W               Double           chi_increment parameter value.
chiStart                        R/W               Double           chi_start parameter value.
kappaIncrement                  R/W               Double           kappa_increment parameter value.
kappaStart                      R/W               Double           kappa_start parameter value.
omegaIncrement                  R/W               Double           omega_increment parameter value.
omegaStart                      R/W               Double           omega_start parameter value.
phiIncrement                    R/W               Double           phi_increment parameter value.
phiStart                        R/W               Double           phi_start parameter value.         
compressionType                 R/W               String           Defines the compression algorithm
                                                                   used. Allowed options are lz4 and bslz4.         
                                                                   To ensure highest stability at full
                                                                   frame rates, DECTRIS strongly
                                                                   advises using bslz4 compression.
softwareVersion                 R                 String           Software version used for data
                                                                   acquisition and correction.           
===========================     ================  ================ =====================================

Commands
--------

=======================	=============== =======================	===========================================
Command name		    Arg. in		    Arg. out		        Description
=======================	=============== =======================	===========================================
Init			        DevVoid 	    DevVoid			        Do not use
State			        DevVoid		    DevLong			        Return the device state
Status			        DevVoid		    DevString		        Return the device state as a string
Abort                   DevVoid         DevVoid                 Not Implemented.
Initialize              DevVoid         DevVoid                 Initializes the detector.
=======================	=============== =======================	===========================================

.. _Eiger camera plugin: http://lima.blissgarden.org/camera/eiger/doc/index.html
