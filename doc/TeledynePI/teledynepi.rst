.. _lima-tango-Teledynepi:

TeledynePI Tango C++ device
=============================

This is the reference documentation of the TeledynePI Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `TeledynePI camera plugin`_ section.


Properties
----------

=============================== ======================== ================== ===========================================================
Property name                   Default value            Type               Description
=============================== ======================== ================== ===========================================================
TemperatureTargetAtInit         TBD                      Double             Define the Temperature Target of the camera at Init device
=============================== ======================== ================== ===========================================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
temperature                     R                        Double             The current temperature in deg Celsius.
temperatureTarget               R/W                      Double             Define the target temperature in deg Celsius.
                                                                            It's a memorized attribute.
gain                            R/W                      Enum               Define the gain.It's a memorized attribute.
                                                                            Available values:
                                                                            - LOW
                                                                            - MEDIUM
                                                                            - HIGH
                                                                            It's a memorized attribute.
adcRate                         R/W                      Double             Display the current ADC frequency in Mhz.
                                                                            It's a memorized attribute.
=============================== ======================== ================== ===============================================


Commands
--------

=============================== ======================== ================== ===============================================
Command name                    Arg. in                  Arg. out           Description
=============================== ======================== ================== ===============================================
Init                            Void                     Void               Do not use
State                           Void                     Long               Return the device state
Status                          Void                     String             Return the device state as a string
=============================== ======================== ================== ===============================================

.. _TeledynePI camera plugin: TBD
