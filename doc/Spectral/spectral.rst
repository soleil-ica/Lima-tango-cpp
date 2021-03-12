.. _lima-tango-spectral:

Spectral Tango C++ device
==========================

This is the reference documentation of the Spectral Tango C++ device.


Properties
----------

====================================== ========================= ================== ===============================================
Property name                          Default value             Type               Description
====================================== ========================= ================== ===============================================
ExpertConnectionAddress                127.0.0.1                 String             Server name or IP address of the SI Image SGL II software
ExpertConnectionPort                   0                         String             TCP/IP port of the SI Image SGL II software
ExpertImagePacketPixelsNb              512                       Long               Number of pixels sent into a image part TCP/IP packet
ExpertImagePacketDelayMicroSec         300                       Long               Delay between the sending of two image part TCP/IP packets (in micro-seconds)
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
=============================== ======================== ================== ===============================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================
