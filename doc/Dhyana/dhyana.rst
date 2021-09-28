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
fps                             R/W                      Double             Get frame rate value
channel1                        R/W                      Enum               Set trigger output mode (ExposureStart, Readout, Global) on channel 1
channel2                        R/W                      Enum               Set trigger output mode (ExposureStart, Readout, Global) on channel 2
channel3                        R/W                      Enum               Set trigger output mode (ExposureStart, Readout, Global) on channel 3
width1                          R/W                      Double             Set width value option on channel 1 mode
width2                          R/W                      Double             Set width value option on channel 2 mode
width3                          R/W                      Double             Set width value option on channel 3 mode
delay1                          R/W                      Double             Set delay value option on channel 1 mode
delay2                          R/W                      Double             Set delay value option on channel 2 mode
delay3                          R/W                      Double             Set delay value option on channel 3 mode
edge1                           R/W                      Enum               Set edge option value (Rising, Failing) on channel 1 mode
edge2                           R/W                      Enum               Set edge option value (Rising, Failing) on channel 2 mode
edge3                           R/W                      Enum               Set edge option value (Rising, Failing) on channel 3 mode
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

