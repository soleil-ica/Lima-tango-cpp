.. _lima-tango-merlin:

Merlin C++ Tango device
========================

This is the reference documentation of the Merlin Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Merlin camera plugin`_ section.


Properties
----------

================= =============== ================== =========================================================================
Property name     Default value   Type               Description
================= =============== ================== =========================================================================
HostName          no_name         String             The name of the Merlin PC
CmdPort           6431            Long               The Merlin command port
DataPort          6432            Long               The Merlin data port
ImageWidth        512             Long               The width of Merlin detector head in pixels
ImageHeight       512             Long               The height of the Merlin detector head in Pixels
Chips             4               Long               The number of detector medipix3 chips
Simulate          false           Boolean            Simulate the Merlin commands.
================= =============== ================== =========================================================================


Attributes
----------

======================= =========== ================ ======================================================================
Attribute name          Read/Write  Type             Description
======================= =========== ================ ======================================================================
chargeSumming           R/W         Boolean          Charge Summming mode:

                                                     - True: ON
                                                     - False: OFF 
colourMode              R/W         Long             Colour mode:

                                                     - 0: MONOCHROME
                                                     - 1: COLOUR
continuousRW            R/W         Boolean          Continuous Collection:

                                                     - True: ON
                                                     - False: OFF
counter                 R/W         Long             Counter: 

                                                     - 0: COUNTER0
                                                     - 1: COUNTER1
                                                     - 2: BOTH (image will be double size)
gain                    R/W         Long             Gain Settings:

                                                     - 0: SHGM
                                                     - 1: HGM
                                                     - 2: LGM
                                                     - 3: SLGM
operatingEnergy         R/W         Float            Energy keV  (0 < e < 999.99)             
softwareVersion         R           Float            Software version number
temperature             R           Float            Temperature degrees C
threshold0              R/W         Float            Threshold 0 keV (0 < th < 999.99)
threshold1              R/W         Float            Threshold 1 keV (0 < th < 999.99)
threshold2              R/W         Float            Threshold 2 keV (0 < th < 999.99)
threshold3              R/W         Float            Threshold 3 keV (0 < th < 999.99)
threshold4              R/W         Float            Threshold 4 keV (0 < th < 999.99)
threshold5              R/W         Float            Threshold 5 keV (0 < th < 999.99)
threshold6              R/W         Float            Threshold 6 keV (0 < th < 999.99)
threshold7              R/W         Float            Threshold 7 keV (0 < th < 999.99)
framesPerTrigger        R/W         Long             Number of frame per trigger
triggerStartType        R/W         Long             Trigger start type:

                                                     - 0: INTERNAL
                                                     - 1: RISING_EDGE_TTL
                                                     - 2: FALLING_EDGE_TTL
                                                     - 3: RISING_EDGE_LVDS
                                                     - 4: FALLING_EDGE_LVDS
                                                     - 5: SOFT
triggerStopType         R/W         Long             Trigger stop type:

                                                     - 0: INTERNAL
                                                     - 1: RISING_EDGE_TTL
                                                     - 2: FALLING_EDGE_TTL
                                                     - 3: RISING_EDGE_LVDS
                                                     - 4: FALLING_EDGE_LVDS
                                                     - 5: SOFT
triggerOutTTL           R/W         Long             TTL Trigger out type:

                                                     - 0: TTL
                                                     - 1: LVDS
                                                     - 2: TTL_DELAYED
                                                     - 3: LVDS_DELAYED
                                                     - 4: FOLLOW_SHUTTER
                                                     - 5: ONE_PER_ACQ_BURST
                                                     - 6: SHUTTER_AND_SENSOR_READ
                                                     - 7: OUTPUT_BUSY
triggerOutLVDS          R/W         Long             LVDS Trigger out type:

                                                     - 0: TTL
                                                     - 1: LVDS
                                                     - 2: TTL_DELAYED
                                                     - 3: LVDS_DELAYED
                                                     - 4: FOLLOW_SHUTTER
                                                     - 5: ONE_PER_ACQ_BURST
                                                     - 6: SHUTTER_AND_SENSOR_READ
                                                     - 7: OUTPUT_BUSY
triggerOutTTLInvert     R/W         Long             TTL Trigger out invert type

                                                     - 0: NORMAL
                                                     - 1: INVERTED
triggerOutLVDSInvert    R/W         Long             LVDS Trigger out invert type

                                                     - 0: NORMAL
                                                     - 1: INVERTED
triggerInTTLDelay       R/W         Long64           TTL Trigger delay in ns (0 < del < 68719476720)
triggerInLVDSDelay      R/W         Long64           LVDS Trigger delay in ns (0 < del < 68719476720)
triggerUseDelay         R/W         Boolean          Use Trigger delay

                                                     - True:  ON
                                                     - False: OFF
======================= =========== ================ ======================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
SoftTrigger             Void            Void                    Perform soft trigger
Abort                   Void            Void                    Abort
======================= =============== ======================= ===========================================

.. _Merlin camera plugin: https://lima1.readthedocs.io/en/latest/camera/merlin/doc/index.html
