.. _lima-tango-basler:

BaslerCCD Tango C++ device
==========================

This is the reference documentation of the BaslerCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Basler camera plugin`_ section.


Properties
----------

============================ ================ ================ =====================================
Property name                Default value    Type             Description
============================ ================ ================ =====================================
DetectorIP                   127.0.0.1        String           IP Address of the Detector
DetectorTimeout              11000            Long             During acquisition, this is the time before declaring that is no available image returned by detector. (in ms)
DetectorPacketSize           1500             Long             Define the packet size for the selected steam channel of the Transport Layer. (in bytes)
============================ ================ ================ =====================================


Attributes
----------

============================= ================ ================ =====================================
Attribute name                Read/Write       Type             Description
============================= ================ ================ =====================================
frameRate                     R                Double           Display the current frame rate (nb frames/s)
dataRate                      R                Double           Display the current data rate (MB/s)
temperature                   R                Double           Display the current temperature of the BoardSensor.
gain                          R/W              Double           Define the gain of the detector. [0..1]
autoGain                      R/W              Bool             Let the detector manage the gain automatically.
statisticsFailedBufferCount   R                Long             ???
packetSize                    R                Long             The packet size for the selected steam channel of the Transport Layer. (in bytes)
interPacketDelay              R/W              Long             Define the delay between transmission of each packet for the selected stream channel. (in ticks)
bandwidthAssigned             R                Long             Base bandwidth that will be used by the camera to transmit (image+chunk) data and to handle resends and control transmissions. (in Bytes/s)
maxThroughput                 R                Long             Maximum amount of data that the camera could generate given its current settings and ideal conditions. (in Bytes/s)
currentThroughput             R                Long             Current bandwidth that the camera will use to transmit (image+chunk) data given the curent AOIsettings, ... (in Bytes/s)
============================= ================ ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Basler camera plugin: https://lima1.readthedocs.io/en/latest/camera/basler/doc/index.html
