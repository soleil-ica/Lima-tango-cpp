Dhyana
-------------

Introduction
============
| This device supports several camera model
| Currently, two kinds of camera are supported: 
| - The Dhyana6060
| - The Dhyana95/Dhyana95 V2


+-----------------------------+-----------------------+
|                    Supported Camera                 |
+=============================+=======================+
| .. image:: Dhyana6060.png   |                       |
|     :height: 200            | Dhyana6060            |
|     :width: 300             |                       |
+-----------------------------+-----------------------+
| .. image:: Dhyana95.png     |                       |
|     :height: 200            | Dhyana95              |
|     :width: 250             |                       |
+-----------------------------+-----------------------+
| .. image:: Dhyana95V2.png   |                       |
|     :height: 200            | Dhyana95V2            |
|     :width: 250             |                       |
+-----------------------------+-----------------------+

Common Properties
``````````````````````

====================================== ========================= ===================  ===========================================
Property name                          Default value             Type                 Description
====================================== ========================= ===================  ===========================================
ConnectionConfig6060                   4                         String               Selection of the number of connections and bandwidth             
ExpertTimerPeriod                      1                         UShort               Timer period (in ms) Useful only for Internal Trigger             
====================================== ========================= ===================  ===========================================


Dhyana6060
-------------

Introduction
============
| The Dhyana 6060/Dhyana 6060BSI is a very large format camera with a
| front-illuminated/back-illuminated high sensitivity image sensor with an image element
| size of 10 μ m x 10 μ m and a resolution of 37.7 MP. The Dhyana 6060 has a full
| resolution frame rate of up to 44fps@12bit, and the Dhyana 6060BSI also achieves
| 26fps@12 bit. It is suitable for demanding scientific imaging applications such as
| research-grade astronomy and x-ray.



Dhyana6060 Commands
````````````````````

======================= =============== ======================= =============================================================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= =============================================================================
Init                    Void            Void                    Do not use (Use Init of the Generic device) 
State                   Void            Long                    Return the device state
Status                  Void            Long                    Return the device status
======================= =============== ======================= =============================================================================


Dhyana6060 Attributes
````````````````````````````

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
tucamVersion                    R                        String             Get Tucam Library Version.
cameraTemperature               R                        Double             Real-time access to display device temperature
sensorTemperature               R                        Double             Get the temperature of the sensor in real time
sensorTemperatureTarget         R/W                      Double             Customizable sensor temperature target value
sensorCoolingType               R/W                      Enum               | Set the sensor cooling type, support fan cooling
                                                                            | and water cooling
sensorCooling                   R/W                      Enum               Set the sensor cooling switch (ON/OFF)
fanSpeed                        R/W                      UShort             | Set the fan speed gear, support 0~100, default 100,
                                                                            | 0 means the fan is off
fanType                         R/W                      Enum               Set the fan control type, support automatic and manual
globalGain                      R/W                      String             | Switch sensor gain mode, support
                                                                            | -HDR_16bit
                                                                            | -HG_12bit
                                                                            | -LG_12bit
                                                                            | -HG_14bit
                                                                            | -HG_HS_12bit
                                                                            | -LG_HS_12bit
                                                                            | -default HDR_16bit
                                                                            | -HS means high speed mode
                                                                            | /!\ currently only 16bit supported
frameRate                       R/W                      Double             | Customizable frame rate, each resolution corresponds to
                                                                            | a different maximum frame rate, but cannot exceed the maximum frame rate
                                                                            | Currently we use the existant one (same as Dhyana95)
trigInEdge                      R/W                      Enum               | Available only for expert user
                                                                            | Set the trigger signal effective edge
trigInExpType                   R/W                      Enum               | Available only for expert user
                                                                            | Set the trigger exposure type, 
                                                                            | TrigTimed that the exposure time set by the software; 
                                                                            | TrigWidth that the exposure time set by the input level width
trigInDelay                     R/W                      Double             | Available only for expert user
                                                                            | Trigger delay, indicates that after receiving a trigger signal,
                                                                            | you can set how long the delay time before the camera to trigger 
                                                                            | the exposure. Can be set 0us ~ 10s, the default 0, precision 1us.
trigInSoftwareSignal            R/W                      Bool               | Available only for expert user
                                                                            | Software trigger mode button, click once, the software will send a command
                                                                            | to the camera, and only one image will be output at a time
trigOutputKind1                 R/W                      Enum               | Available only for expert user
                                                                            | Configure the parameters of the trigger output signal on channel 1
                                                                            | -High
                                                                            | -Low
                                                                            | -ExposureStart
                                                                            | -ReadoutEnd
                                                                            | -GlobalExposure 
trigOutputKind2                 R/W                      Enum               | Available only for expert user
                                                                            | Configure the parameters of the trigger output signal on channel 2
                                                                            | -High
                                                                            | -Low
                                                                            | -ExposureStart
                                                                            | -ReadoutEnd
                                                                            | -GlobalExposure
trigOutputKind3                 R/W                      Enum               | Available only for expert user
                                                                            | Configure the parameters of the trigger output signal on channel 3
                                                                            | -High
                                                                            | -Low
                                                                            | -ExposureStart
                                                                            | -ReadoutEnd
                                                                            | -GlobalExposure
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



Dhyana95
-------------

Introduction
============
| This is the reference documentation of the Dhyana Tango C++ device.
| This camera can manage 3 trigger modes : INTERNAL_SINGLE, EXTERNAL_MULTI, EXTERNAL_GATE
| This camera can manage ROI
| This camera can't manage Binning.



Dhyana95 Commands
````````````````````

======================= =============== ======================= =============================================================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= =============================================================================
Init                    Void            Void                    Do not use (Use Init of the Generic device) 
State                   Void            Long                    Return the device state
Status                  Void            Long                    Return the device status
======================= =============== ======================= =============================================================================


Dhyana95 Attributes
````````````````````````````

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