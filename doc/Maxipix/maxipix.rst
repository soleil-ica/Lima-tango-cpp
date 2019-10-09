.. _lima-tango-maxipix:

Maxipix Tango C++ device
==========================

This is the reference documentation of the BaslerCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Maxipix camera plugin`_ section.


Properties
----------

======================== ==================== ===================== =====================================
Property name            Default value        Type                  Description
======================== ==================== ===================== =====================================
EspiaDeviceNumber        -1                   Long                  Espia device number.
ConfigurationPath        TO_BE_DEFINED        String                Define the path of the configuration file.
ConfigurationName        TO_BE_DEFINED        String                Define the name of the configuration file.
UseReconstruction        false                Boolean               Enable/Disable reconstruction.
======================== ==================== ===================== =====================================


Attributes
----------

=========================== ================ ================ =====================================
Attribute name              Read/Write       Type             Description
=========================== ================ ================ =====================================
deviceVersion               R                String           Tango Specific device version.
energyTreshold              R/W              Double           Energy threshold (KeV)
fillMode                    R/W              String           Set the fill mode :

                                                              - RAW
                                                              - DISPATCH
                                                              - ZERO
                                                              - MEAN
gate                        R/W              Boolean          Set the gate to Active or Inactive
gateLevel                   R/W              String           Set gate level :

                                                              - LOW
                                                              - HIGH
readyMode                   R/W              String           Ready mode :

                                                              - EXPOSURE
                                                              - READOUT
readyLevel                  R/W              String           Ready output signal level :

                                                              - LOW
                                                              - HIGH
shutterLevel                R/W              String           Shutter output signal level :

                                                              - LOW
                                                              - HIGH
triggerLevel                R/W              String           Trigger output signal level :

                                                              - LOW
                                                              - HIGH
=========================== ================ ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Maxipix camera plugin: https://lima1.readthedocs.io/en/latest/camera/maxipix/doc/index.html
