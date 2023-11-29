Dhyana
-------------

Introduction
============
| This device supports several camera models
| Currently, two kinds of camera are supported: 
| - The Dhyana95/Dhyana95 V2
| - The Dhyana4040

+-----------------------------+-----------------------+
|                    Supported Camera                 |
+=============================+=======================+
| .. image:: Dhyana95.png     |                       |
|     :height: 200            | Dhyana95              |
|     :width: 250             |                       |
+-----------------------------+-----------------------+
| .. image:: Dhyana95V2.png   |                       |
|     :height: 200            | Dhyana95V2            |
|     :width: 250             |                       |
+-----------------------------+-----------------------+
| .. image:: Dhyana4040.png   |                       |
|     :height: 200            | Dhyana4040            |
|     :width: 250             |                       |
+-----------------------------+-----------------------+

Dhyana95
-------------

Introduction
============
| This is the documentation of the Lima/Dhyana Tango C++ device.
| This camera can manage 4 triggers modes : INTERNAL_SINGLE, EXTERNAL_MULTI, EXTERNAL_GATE, INTERNAL_MULTI 
| This camera can manage ROI
| This camera can't manage Binning.

Dhyana4040
-------------

Introduction
============
| The Dhyana 4040/Dhyana 4040 BSI delivers big sensor performance with 90% QE.
| With a 52mm diameter sensor made of 9 micron pixels, it operates with 
| low noise at high speed. Providing CCD level performance in terms of 
| background and noise performance, at speeds that enable a wide range of applications.

Common Properties
``````````````````````

====================================== ========================= ===================  ===========================================
Property name                          Default value             Type                 Description
====================================== ========================= ===================  ===========================================
__ExpertTimerPeriod                    1                         UShort               Timer period (in ms) Useful only for Internal Trigger
TemperatureTargetAtInit                15                        Double               Temperature Target at init
====================================== ========================= ===================  ===========================================


Common Attributes
````````````````````````````

=============================== ======================== ================== =================================================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== =================================================================
tucamVersion                    R                        String             Get Tucam Library Version.
sensorTemperature               R                        Double             Get Temperature of the detector (in Celsius)
sensorTemperatureTarget         R/W                      Double             Set the Temperature target of the detector (in Celsius)
fanSpeed                        R/W                      Enum               | Available only for expert user
                                                                            | Define the fan speed of the detector [0..5]                                                                    
globalGain                      R/W                      Enum               Define the gain of the detector [LOW, HIGH, HDR]
frameRate                       R                        Double             Get frame rate value
trigOutputKind1                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode on channel 1 [ExposureStart, Readout, Global]
trigOutputKind2                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode on channel 2 [ExposureStart, Readout, Global]
trigOutputKind3                 R/W                      Enum               | Available only for expert user
                                                                            | Set trigger output mode on channel 3 [ExposureStart, Readout, Global]
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
                                                                            | Set edge option value on channel 1 mode [Rising, Falling]
trigOutputEdge2                 R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value on channel 2 mode [Rising, Falling]
trigOutputEdge3                 R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value on channel 3 mode [Rising, Falling]
=============================== ======================== ================== =================================================================

Dhyana4040 specific Attributes
````````````````````````````````

=============================== ======================== ================== =================================================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== =================================================================
tecMode                         R/W                      Enum               Set the sensor cooling switch [ON, OFF]
=============================== ======================== ================== =================================================================

Common Commands
````````````````````

======================= =============== ======================= =============================================================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= =============================================================================
Init                    Void            Void                    Do not use (Use Init of the Generic device) 
State                   Void            Long                    Returns the device state
Status                  Void            String                  Returns the device status
setParamter             String Array    Void                    Sets the value of a parameter
getParameter            String          String                  Returns the name and value of a specific parameter
getAllParameters        Void            String                  Returns all parameters and their values
======================= =============== ======================= =============================================================================