.. _lima-tango-hamamatsu:

Hamamatsu C++ Tango device
==========================

This is the reference documentation of the Hamamatsu Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Hamamatsu camera plugin`_ section.


Properties
----------
================================== =============== =============== =========================================================================
Property name                      Default value   Type            Description
================================== =============== =============== =========================================================================
DetectorNum                        0               Long            id of the camera.
BlankOfSyncreadoutTrigger          NORMAL          String          Allows you to select the blank of synreadout. Availables values:

                                                                   - STANDARD
                                                                   - MINIMUM
================================== =============== =============== =========================================================================


Static attributes
-----------------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
lostFrames              R          Long       Number of frames lost during the current or last acquisition.
fps                     R          Double     The last computed frame per second (the value is computed every 100 frames only).
wViewEnabled            R/W        Boolean    Activation state of the W-VIEW mode.
topViewExposureTime     R/W        Double     Exposure time for first W-VIEW.
bottomViewExposureTime  R/W        Double     Exposure time for second W-VIEW.
channel1Polarity	R/W	   UShort     Polarity for channel 1 (NEGATIVE = 0, POSITIVE = 1).
channel2Polarity	R/W	   UShort     Polarity for channel 2 (NEGATIVE = 0, POSITIVE = 1).
channel3Polarity	R/W	   UShort     Polarity for channel 3 (NEGATIVE = 0, POSITIVE = 1).
channel1Kind		R/W	   UShort     Kind for channel 1 (LOW = 1, GLOBAL_EXPOSURE  = 2, PROGRAMMABLE = 3, TRIGGER_READY = 4, HIGH = 5).
channel2Kind		R/W	   UShort     Kind for channel 2 (LOW = 1, GLOBAL_EXPOSURE  = 2, PROGRAMMABLE = 3, TRIGGER_READY = 4, HIGH = 5).
channel3Kind		R/W	   UShort     Kind for channel 3 (LOW = 1, GLOBAL_EXPOSURE  = 2, PROGRAMMABLE = 3, TRIGGER_READY = 4, HIGH = 5). 
======================= ========== ========== ==============================================================================================


Dynamic attributes
------------------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
temperature             R          Double     Temperature of the image sensor in Celcius.
coolerMode              R          String     Selected cooler mode (OFF/ON/MAX/NOT_SUPPORTED).
coolerStatus            R          String     Current cooler status. Possible values can be:

                                              - inactive (NOT_SUPPORTED, NONE, OFF)
                                              - in error (ERROR1, ERROR2, ERROR3, ERROR4)
                                              - running (READY, BUSY, ALWAYS, WARNING)
temperatureStatus       R          String     Current temperature status (NOT_SUPPORTED, NORMAL, WARNING, PROTECTION). 
highDynamicRangeEnabled R/W        Boolean    Current high dynamic range activation status (for ORCA Lightning and others detectors).

                                              - False is for Standard Full Well Capacity mode
                                              - True is for High Full Well Capacity mode
readoutSpeed            R/W        String     Readout speed . Possible values are:

                                              - NORMAL
                                              - SLOW
======================= ========== ========== ==============================================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Returns the device state
Status                  Void            String                  Returns the device state as a string
setParamter             String Array    Void                    Set the value of a parameter
getParameter            String          String                  Returns the name and value of a specific parameter
getAllParameter         Void            String                  Returns all parameters and their values
======================= =============== ======================= ===========================================

.. _Hamamatsu camera plugin: https://lima1.readthedocs.io/en/latest/camera/hamamatsu/doc/index.html
