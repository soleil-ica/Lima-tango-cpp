.. _lima-tango-spectral-instrument:

Spectral Instrument Tango C++ device
==========================

This is the reference documentation of the Spectral Instrument Tango C++ device.


Properties
----------

====================================== ========================= ================== ===============================================
Property name                          Default value             Type               Description
====================================== ========================= ================== ===============================================
ConnectionAddress                      127.0.0.1                 String             Server name or IP address of the SI Image SGL II software
ConnectionPort                         0                         String             TCP/IP port of the SI Image SGL II software
ImagePacketPixelsNb                    512                       Long               Number of pixels sent into a image part TCP/IP packet
ImagePacketDelayMicroSec               300                       Long               Delay between the sending of two image part TCP/IP packets (in micro-seconds)
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
cooling                         R/W                      Boolean            Turns the CCD cooling On/Off
ccdTemperature                  R                        Float              Camera temperature status (°C)
readoutSpeed                    R/W                      Enum               Readout Speed control is a convenient way to set the DSI Sample Time which is the parameter that controls the readout speed (1MHz, 690KHz)
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