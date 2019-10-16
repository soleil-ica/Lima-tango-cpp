.. _lima-tango-andorccd:

AndorCCD Tango C++ device
=========================

This is the reference documentation of the AndorCCD Tango C++ device.

You can also find some useful information about prerequisite/installation/configuration/compilation in the `Andor camera plugin`_ section.


Properties
----------

=========================== ==================================== ======================================================================================================
Property name               Default value                        Description
=========================== ==================================== ======================================================================================================
DetectorNum                 -1                                   Detector Number.
CoolingStatusAtStartUp      OFF                                  Define which Cooling status (ON/OFF) must be selected when start the device.
=========================== ==================================== ======================================================================================================


Attributes
----------

=========================== ============= ============================== ===============================================================================================
Attribute name              Read/Write    Type                           Description
=========================== ============= ============================== ===============================================================================================
enabledCooler               R/W           Boolean                        Controls the cooler.
currentCoolingStatus        R             String                         Current status of the cooling system.
temperatureTarget           R/W           Long                           Controls the temperature target point.
temperature                 R             Long                           Current temperature.
adcMode                     R/W           ULong                          Define the ADC frequency. Available values are :

                                                                         - 0: 5 Mhz                                                                                          
                                                                         - 1: 3 Mhz                                                                                          
                                                                         - 2: 1 Mhz                                                                                          
                                                                         - 3: 0.05 Mhz                                                                                       
currentRate                 R             String                         Current ADC frequency in Mhz.
=========================== ============= ============================== ===============================================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Andor camera plugin: https://lima1.readthedocs.io/en/latest/camera/andor/doc/index.html
