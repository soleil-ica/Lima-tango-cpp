.. _lima-tango-dhyana:

Dhyana Tango C++ device
==========================

This is the reference documentation of the Dhyana Tango C++ device.

This camera can manage 3 trigger modes : INTERNAL_SINGLE, EXTERNAL_MULTI, EXTERNAL_GATE

This camera can manage ROI 

This camera can't manage Binning 

Properties
----------

====================================== ========================= ================== ===============================================
Property name                          Default value             Type               Description
====================================== ========================= ================== ===============================================
__ExpertTimerPeriod                    1                         UShort             Timer period (in ms)

                                                                                    Useful only for Internal Trigger
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
tucamVersion                    R                        String             Get Tucam Library Version.
temperature                     R                        Double             Get Temperature of the detector (in Celsius)
temperatureTarget               W                        Double             Set the Temperature target of the detector (in Celsius)
fanSpeed                        R/W                      UShort             Define the fan speed of the detector [0..5]
globalGain                      R/W                      String             Define the gain of the detector [LOW, HIGH, HDR]
=============================== ======================== ================== ===============================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use (Use Init of the Generic device)
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

