.. _lima-tango-marccd:

MarCCD Tango C++ device
==========================

This is the reference documentation of the MarCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `MarCCD camera plugin`_ section.


Properties
----------

=============================== ======================== ================== ===============================================
Property name                   Default value            Type               Description
=============================== ======================== ================== ===============================================
DetectorIP                      N/A                      String             Detector IP address
DetectorPort                    N/A                      ULong              Detector port number
DetectorTargetPath              /no/path/defined         String             Detector target images path
ReaderTimeout                   10000                    UShort             Time before declaring that is no available image returned by detector. (in ms)
ReaderNbRetry                   3                        Long               The number of retry before the Reader declares that there are no images in the directory target path.
=============================== ======================== ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
imageName                       R/W                      String             The image file name
imageIndex                      R/W                      UShort             The current image index
waitFileOnDiskTime              R/W                      Double             The waiting time (in ms) of the arrival of the detector file on the disk.

                                                                            Target is defined in the detectorTargetPath attribute.
=============================== ======================== ================== ===============================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
TakeBackground          Void            Void                    Force the MarCCD detector to acquire a background frame
======================= =============== ======================= ===========================================

.. _MarCCD camera plugin: https://lima1.readthedocs.io/en/latest/camera/marccd/doc/index.html
