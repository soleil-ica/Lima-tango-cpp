.. _lima-tango-pco:

Pco C++ Tango device
======================

This is the reference documentation of the Pco Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Pco camera plugin`_ section.


Properties
----------

======================== ================ ================== =====================================
Property name            Default value    Type               Description
======================== ================ ================== =====================================
SerialNumber             0                String             Serial Number of the camera: used to select camera if several connected to the same host; default : 0 (ie select the 1st camera found)
======================== ================ ================== =====================================


Attributes
----------

=========================== ================  ================ =====================================
Attribute name              Read/Write        Type             Description
=========================== ================  ================ =====================================
pixelRate                   R/W               String           Get / Set the Pixel Rate in Hz
doubleImage                 R/W               Boolean          Get / Set the double image mode
currentRecordedFrame        R                 Ulong            Current recorded frame : frames recorded in the Camera RAM
cameraModel                 R                 String           Model of the camera
sensorTemperature           R                 Float            Image sensor temperature in degree celcius
forcedFIFOMode              R/W               Boolean          Get / Set the forced FIFO mode
dllVersion                  R                 String           Version of the SC2_cam.dll

=========================== ================  ================ =====================================


Optionnal attributes (depend on camera model)
-----------------------------------------------

=========================== ================  ================ =====================================
Attribute name              Read/Write        Type             Description
=========================== ================  ================ =====================================
maxNbImage                  R                 Ulong            Get the max number of images available in the Camera RAM: depending on the Roi (Dimax, 4000, 2000, 1600)
cdiMode                     R/W               Boolean          Get / Set the cdi mode (Dimax)
frameRate                   R                 Double           Get the current frame rate (Dimax, Edge) 
coolingSetPoint             R/W               Short            Get / Set the cooling set point in degree celcius (4000, 2000, 1600, Edge)
adcOperation                R/W               String           Get / Set the adc operation: (4000, 2000, 1600)

                                                               - SINGLE
                                                               - DUAL
shutterMode                     R/W               String           Get / Set the shutterMode operation: (Edge)

                                                                   - ROLLING_SHUTTER
                                                                   - GLOBAL_SHUTTER
                                                                   - GLOBAL_RESET 
=========================== ================  ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
GetCamInfo              Void            String                  Get Camera Infos
Talk                    String          String                  Availables values are: 

                                                                - ? (get all available parameters)
                                                                - lasterror
                                                                - camInfo
                                                                - camType
                                                                - clTransferParam 
                                                                - cocRunTime
                                                                - frameRate
                                                                - maxNbImages
                                                                - timestamp
======================= =============== ======================= ===========================================

.. _Pco camera plugin: https://lima1.readthedocs.io/en/latest/camera/pco/doc/index.html
