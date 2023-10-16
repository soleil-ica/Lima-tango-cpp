Dhyana
-------------

Introduction
============
| This device supports camera model
| - Dhyana6060


+-----------------------------+-----------------------+
|                    Supported Camera                 |
+=============================+=======================+
| .. image:: Dhyana6060.png   |                       |
|     :height: 200            | Dhyana6060            |
|     :width: 300             |                       |
+-----------------------------+-----------------------+



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


Properties
``````````````````````

====================================== ========================= ===================  ===========================================
Property name                          Default value             Type                 Description
====================================== ========================= ===================  ===========================================
ConnectionConfig6060                   4                         String               Selection of the number of connections and bandwidth             
ExpertTimerPeriod                      1                         UShort               Timer period (in ms) Useful only for Internal Trigger             
====================================== ========================= ===================  ===========================================

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
trigOutputPort                  R/W                      Enum               | Select the output port (1, 2, 3)
trigOutputKind                  R/W                      Enum               | Available only for expert user
                                                                            | Configure the parameters of the trigger output signal on channel 1
                                                                            | -High
                                                                            | -Low
                                                                            | -ExposureStart
                                                                            | -ReadoutEnd
                                                                            | -GlobalExposure 
trigOutputWidth                 R/W                      Double             | Available only for expert user
                                                                            | Set width value option
trigOutputDelay                 R/W                      Double             | Available only for expert user
                                                                            | Set delay value option
trigOutputEdge                  R/W                      Enum               | Available only for expert user
                                                                            | Set edge option value (Rising, Failing)
=============================== ======================== ================== ===============================================