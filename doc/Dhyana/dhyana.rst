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
ExpertTimerPeriod                      1                         UShort             Timer period (in ms)

                                                                                    Useful only for Internal Trigger
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
tucamVersion                    R                        String             Get Tucam Library Version.
sensorTemperature               R                        Double             Get Temperature of the detector (in Celsius)
sensorTemperatureTarget         R/W                      Double             Set the Temperature target of the detector (in Celsius)
fanSpeed                        R/W                      UShort             Define the fan speed of the detector [0..5]
globalGain                      R/W                      String             Define the gain of the detector [LOW, HIGH, HDR]
frameRate                       R/W                      Double             Get frame rate value
trigOutputKind1                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode (ExposureStart, Readout, Global) on channel 1
trigOutputKind2                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode (ExposureStart, Readout, Global) on channel 2
trigOutputKind3                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode (ExposureStart, Readout, Global) on channel 3
trigOutputWidth1                R/W                      Double             | Available only for expert user
                                                                            | Set width value option on channel 1 mode
trigOutputWidth2                R/W                      Double             | Available only for expert user
                                                                            | Set width value option on channel 2 mode
trigOutputWidth3                R/W                      Double             | Available only for expert user
                                                                            | Set width value option on channel 3 mode
trigOutputDelay1                R/W                      Double             | Available only for expert user
                                                                            | Set delay value option on channel 1 mode
trigOutputDelay2                R/W                      Double             | Available only for expert user
                                                                            | Set delay value option on channel 2 mode
trigOutputDelay3                R/W                      Double             | Available only for expert user
                                                                            | Set delay value option on channel 3 mode
trigOutputEdge1                 R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value (Rising, Failing) on channel 1 mode
trigOutputEdge2                 R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value (Rising, Failing) on channel 2 mode
trigOutputEdge3                 R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value (Rising, Failing) on channel 3 mode
=============================== ======================== ================== ===============================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use (Use Init of the Generic device)
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
setParamter             String Array    Void                    Set the value of a parameter
getParameter            String          String                  Return the name and value of a specific parameter
getAllParameter         Void            String                  Return all parameters and there value
======================= =============== ======================= ===========================================

