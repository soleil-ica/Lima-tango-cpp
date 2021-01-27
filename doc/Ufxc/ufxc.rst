.. _lima-tango-ufxc:

Ufxc Tango C++ device
==========================

This is the reference documentation of the Ufxc Tango C++ device.


Properties
----------

====================================== ========================= ================== ===============================================
Property name                          Default value             Type               Description
====================================== ========================= ================== ===============================================
AutoLoad                               False                     Boolean            Allows to Reload the last used Detector Configuration file at each init of the device.
ConfigIpAddress                        127.0.0.1                 String             Config Ip Address
ConfigPort                             0                         String             Config Port
SFP1IpAddress                          127.0.0.1                 String             SFP1 Ip Address
SFP1Port                               0                         String             SFP1 Port
SFP2IpAddress                          127.0.0.1                 String             SFP2 Ip Address
SFP2Port                               0                         String             SFP2 Port
SFP3IpAddress                          127.0.0.1                 String             SFP3 Ip Address
SFP3Port                               0                         String             SFP3 Port
Timeout                                0                         ULong              Timeout in ms
DetectorConfigFiles                    ALIAS;PATH_AND_FILE_NAME  Array of String    Define the list of Detector Configuration files and their associated alias
GeometricalCorrectionEnabled           true                      Boolean            Enable/Disable the geometrical corrections.
StackFramesSumEnabled                  true                      Boolean            Enable/Disable the sum of the frames stack.
UfxcModel                              U2C                       String             Allows to specify the UFXC model.
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
libVersion                      R                        String             Get the Ufxc Library Version
firmwareVersion                 R                        String             Get the firmware version of the DAQ
currentAlias                    R                        String             Get the current Alias used to load the configuration file
currentConfigFile               R                        String             Get the path+name of the current configuration file
detetorTemperature              R                        ULong              Get the detector temperature in degree Celsius 
thresholdLow                    R/W                      Float              Set threshold Low for the chip A & chip B
thresholdHigh                   R/W                      Float              Set threshold High for the chip A & chip B
thresholdLow1                   R                        Ulong              Get threshold Low for the chip A
thresholdHigh1                  R                        Ulong              Get threshold High for the chip A
thresholdLow2                   R                        Ulong              Get threshold Low for the chip B
thresholdHigh2                  R                        Ulong              Get threshold High for the chip B
triggerAcquisitionFrequency     R/W                      Float              Define the trigger acquisition frequency in the pump & probe mode.

                                                                            pump_probe_nb_frames = (round(exposureTime*triggerAcquisitionFrequency/2))*2
=============================== ======================== ================== ===============================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
LoadConfigFile          String          Void                    Load  the detector configuration file designed by its alias
======================= =============== ======================= ===========================================
