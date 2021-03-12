.. _lima-tango-eiger:

Eiger C++ Tango device
======================

This is the reference documentation of the Eiger Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Eiger camera plugin`_ section.


Properties
----------

==========================  ================================= =====================================
Property name               Default value                     Description
==========================  ================================= =====================================
DetectorIP                  127.0.0.1                         Eiger server IP address (ex: 192.168.0.1)
DownloadDataFile            False                             Enable/Disable downloading data files from DCU.
TimestampType               RELATIVE                          Define the timestamp type of each frame. Available values:

                                                              - RELATIVE : The time difference between the moment of reading the frame and  the start acquisition time
                                                              - ABSOLUTE : The time at the moment of reading the frame from detector
CurlDelayMs                 100                               Curl delay in ms. this is used as a sleep delay for waiting the curl responses
NbFramesPerTriggerIsMaster  False                             Enable the NbFramesPerTrigger mode:

                                                              - True: nbFrames = memorized values of NbTriggers * NbFramesPerTrigger (case on PX1 beamline)
                                                              - False: nbFrames = memorized nbFrames (case on Swing, Sixs beamlines)
==========================  ================================= =====================================


Attributes
----------

=========================== ================ ================ =====================================
Attribute name              Read/Write       Type             Description
=========================== ================ ================ =====================================
countrateCorrection         R/W              Boolean          Enables (True) or disables (False) countrate correction. 

                                                              Should always be  enabled.        
flatfieldCorrection         R/W              Boolean          Enables (True) or disables (False) flatfield correction.
pixelMask                   R/W              Boolean          A bit mask that labels and classifies pixels which are either defective, inactive or not exhibit non-standard behavior.

                                                              - 0 gap (pixel with no sensor)
                                                              - 1 dead
                                                              - 2 under responding
                                                              - 3 over responding
                                                              - 4 noisy
                                                              - 5-31 -undefined
virtualPixelCorrection      R/W              Boolean          Enables (True) or disables (False) virtual pixel correction.        
autoSummation               R/W              Boolean          Enables (True) or disables (False) autosummation.        
compression                 R/W              Boolean          Enables (True) or disables (False) compression of detector data written to HDF5 files. 

                                                              Compression is required for full detector performance, disabling compression may lead to data loss at high frame rates. 
dataCollectionDate          R                String           Date and time of data collection.

                                                              Specifically this is the time when the ARM command was issued         
thresholdEnergy             R/W              Double           Threshold energy for X-ray counting.

                                                              Photons with an energy below the threshold are not detected.
photonEnergy                R/W              Double           Energy of incident X-rays.
wavelength                  R/W              Double           Wavelength of incident X-rays.
beamCenterX                 R/W              Double           Beam position on detector.
beamCenterY                 R/W              Double           Beam position on detector.
detectorDistance            R/W              Double           Sample to detector distance.
temperature                 R                Double           Detector temperature.
humidity                    R                Double           Humidity inside the detector module compartment.
chiIncrement                R/W              Double           chi_increment parameter value.
chiStart                    R/W              Double           chi_start parameter value.
kappaIncrement              R/W              Double           kappa_increment parameter value.
kappaStart                  R/W              Double           kappa_start parameter value.
omegaIncrement              R/W              Double           omega_increment parameter value.
omegaStart                  R/W              Double           omega_start parameter value.
phiIncrement                R/W              Double           phi_increment parameter value.
phiStart                    R/W              Double           phi_start parameter value.         
compressionType             R/W              String           Defines the compression algorithm used. 
                                                              Allowed options are :

                                                              - LZ4
                                                              - BSLZ4

                                                              To ensure highest stability at fullframe rates, DECTRIS strongly advises using BSLZ4 compression.
softwareVersion             R                String           Software version used for data acquisition and correction.    
managedMode                 R                String           Display the current managed mode.
                                                              managed mode is based on combination of FileManagedMode & DownloadDataFile properties.

                                                              Available values of Managed Mode are : 

                                                              - STREAMING : Image and header data are transferred via zeromq sockets & Nexus files could be generated into an user defined path

                                                              - FILEWRITER : Image and the metadata are generated into the DCU in HDF5 format & data files are tranferred into an user defined path through the device & data files are deleted from DCU

                                                              - LAZY : Image and the metadata are generated in DCU in HDF5 format 
roiMode                     R/W              String           Enable/Disable the Roi "4M"

                                                              Available values:

                                                              - 4M
                                                              - DISABLED
detectorReadoutTime         R                Double           Readout Time
nbTriggers                  R/W              Long             Define the number of triggers expected by the detector to terminate the acquisition. The detector stays armed until nbTriggers are received.
                                                              Available only for the triggers modes (and if NbFramesPerTriggerIsMaster property is true):
                                                              
                                                              - INTERNAL_SINGLE (ints)
                                                              - EXTERNAL_SINGLE (exts)
nbFramesPerTrigger          R/W              Long             Define the number of frames acquired by the detector for each received trigger.
                                                              Available only for the triggers modes (and if NbFramesPerTriggerIsMaster property is true):

                                                              - INTERNAL_SINGLE (ints)
                                                              - EXTERNAL_SINGLE (exts)
=========================== ================ ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
Abort                   Void            Void                    Not Implemented.
Initialize              Void            Void                    Initializes the detector.
Disarm                  Void            Void                    Disarm the detector.
UpdateTh                Void            Void                    Update values of temperature & humidity from detector (status update )
======================= =============== ======================= ===========================================

.. _Eiger camera plugin: https://lima1.readthedocs.io/en/latest/camera/eiger/doc/index.html
