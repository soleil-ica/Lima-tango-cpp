.. _lima-tango-aviex:

AviexCCD Tango C++ device
==========================

This is the reference documentation of the AviexCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Aviex camera plugin`_ section.


Properties
----------

============================ ================ ================ =====================================
Property name                Default value    Type             Description
============================ ================ ================ =====================================
DetectorID                   MUST_BE_DEFINED  String           Detector name
MxDatabaseFileFullName       MUST_BE_DEFINED  String           The path & the Name of the Mx database file.
============================ ================ ================ =====================================


Attributes
----------

============================= ================ ================ =====================================
Attribute name                Read/Write       Type             Description
============================= ================ ================ =====================================
mxLibraryVersion              R                String           Returns a complete version string for MX library.
internalAcquisitionMode       R/W              String           Available Internal Acquisition Modes are:

                                                                - ONESHOT
                                                                - CONTINUOUS
                                                                - MULTIFRAME
                                                                - GEOMETRICAL
                                                                - MEASURE_DARK
                                                                - MEASURE_FLOOD_FIELD
initialDelayTime              R/W              Double           Initial Delay Time (ms)
readoutDelayTime              R/W              Double           Readout Delay Time (ms)
exposureMultiplier            R/W              Double           
gapMultiplier                 R/W              Double           
maskCorrection                R/W              Boolean          
biasCorrection                R/W              Boolean          
darkCorrection                R/W              Boolean          
floodCorrection               R/W              Boolean          
geomCorrection                R/W              Boolean          
highSpeed                     R/W              Boolean          
============================= ================ ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
SetParam                StringArray     Void                    Set Parameter (Input: name, value)
GetParam                String          String                  Get parameter
======================= =============== ======================= ===========================================

.. _Aviex camera plugin: https://lima1.readthedocs.io/en/latest/camera/aviex/doc/index.html
