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
MemorizedTopViewExposureTime       1000            Double          Memorize/Define the Top View exposure time attribute.
MemorizedBottomViewExposureTime    1000            Double          Memorize/Define the Bottom View exposure time attribute.
MemorizedWViewEnabled              false           Boolean         Memorize/Define the W-VIEW mode attribute.
================================== =============== =============== =========================================================================


Attributes
----------

======================= ========== ========== ==============================================================================================
Attribute name          Read/Write Type       Description
======================= ========== ========== ==============================================================================================
readoutSpeed            R/W        String     Readout speed . Possible values are:

                                              - NORMAL
                                              - SLOW
lostFrames              R          Long       Number of frames lost during the current or last acquisition.
fps                     R          Double     The last computed frame per second (the value is computed every 100 frames only).
wViewEnabled            R/W        Boolean    Activation state of the W-VIEW mode.
topViewExposureTime     R/W        Double     Exposure time for first W-VIEW.
bottomViewExposureTime  R/W        Double     Exposure time for second W-VIEW.
Temperature             R          Double     Temperature of the image sensor in Celcius.
======================= ========== ========== ==============================================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Hamamatsu camera plugin: https://lima1.readthedocs.io/en/latest/camera/hamamatsu/doc/index.html
