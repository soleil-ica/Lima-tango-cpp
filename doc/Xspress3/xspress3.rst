.. _lima-tango-xspress3:

Xspress3 Tango C++ device
==========================

This is the reference documentation of the Xspress3 Tango C++ device.

This camera is an unsigned 32 bits pixel depth

This camera can manage 2 trigger modes : INTERNAL_SINGLE, EXTERNAL_GATE

This camera can't manage ROI 

This camera can't manage Binning 

Properties
----------

====================================== ========================= ================== ===============================================
Property name                          Default value             Type               Description
====================================== ========================= ================== ===============================================
BaseIPAdress                           192.168.0.1               String             The base IP Adress of the xspress3
BaseMacAddress                         02.00.00.00.00.00         String             The base MAC address of the xspress3
BasePort                               30123                     Long               The base port of the xspress3
CardIndex                              0                         Long               The card index
DirectoryName                          /home/...                 String             The directory containing calibration files
maxFrames                              16384                     Long               Each card can handle 8192 frames
NbCards                                2                         Long               Number of cards in the system
NbChans                                4                         Long               Each card has 2 channels
NoUDP                                  false                     Boolean            Use or Not UDP connection (always false!)
====================================== ========================= ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
revision                        R                        String             Revision of the firmware
totalCount                      R                        Double             Number of all event triggers = ALLEVENT
totalProcessedCount             R                        Double             Number of processed event = ALLGOOD
icr                             R                        Double             Input Count Rate = AllEvent/Time
ocr                             R                        Double             Output Count Rate = AllGood/Time
deadTime                        R                        Double             Temps mort = 100*(1-AllGood/AllEvent) 
pileup                          R                        Double             Pileup = 100*PileUp/AllGood
realTime                        R                        Double             TotalTicks*12.5/1E9
channel                         R                        ULong              Histogram of datas
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

