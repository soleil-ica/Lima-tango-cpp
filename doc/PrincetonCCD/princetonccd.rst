.. _lima-tango-princetonccd:

PrincetonCCD Tango C++ device
=============================

This is the reference documentation of the PrincetonCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `PrincetonCCD camera plugin`_ section.


Properties
----------

=============================== ======================== ================== ===============================================
Property name                   Default value            Type               Description
=============================== ======================== ================== ===============================================
DetectorNum                                              String             Identifier of the camera 

                                                                            (0..nb total cameras declared in the system. It can be retrieved from WinView32)
TemperatureTargetAtInit         DEFAULT                  String             Define which Temperature must be used at init device

                                                                            - DEFAULT : use DefaultTemperatureTarget value
                                                                            - MEMORIZED : use MemorizedTemperatureTarget value
DefaultTemperatureTarget        -110                     Double             Define the Temperature Target of the Cooler at Init device

                                                                            Used only if TemperatureTargetAtInit = DEFAULT. 

                                                                            (Degree Celsius)
MemorizedTemperatureTarget      -110                     Double             Define the Temperature Target of the Cooler at Init device

                                                                            Used only if TemperatureTargetAtInit = MEMORIZED. 

                                                                            (Degree Celsius)
=============================== ======================== ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
internalAcquisitionMode         R/W                      String             Available Internal Acquisition Modes are :

                                                                            - STANDARD
                                                                            - FOCUS
shutterMode                     R/W                      String             Available Shutter Modes are :

                                                                            - OPEN_NEVER
                                                                            - OPEN_PRE_EXPOSURE
                                                                            - OPEN_NO_CHANGE
temperature                     R                        Double             The current temperature 

                                                                            (Degree Celsius)
temperatureTarget               R/W                      Double             Define the target temperature 

                                                                            (Degree Celsius)
gain                            R/W                      Ushort             Define the gain
currentRate                     R                        String             Display the current ADC frequency in Mhz
=============================== ======================== ================== ===============================================


Commands
--------

=============================== ======================== ================== ===============================================
Command name                    Arg. in                  Arg. out           Description
=============================== ======================== ================== ===============================================
Init                            Void                     Void               Do not use
State                           Void                     Long               Return the device state
Status                          Void                     String             Return the device state as a string
SetADCMode                      UShort                   Void               Define the ADC frequency

                                Available values are :

                                - 0 --> 1 MHz
                                - 1 --> 100 KHz
=============================== ======================== ================== ===============================================

.. _PrincetonCCD camera plugin: https://lima1.readthedocs.io/en/latest/camera/roperscientific/doc/index.html
