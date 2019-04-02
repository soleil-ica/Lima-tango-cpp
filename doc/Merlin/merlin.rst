Merlin Tango device
======================

This is the reference documentation of the Merlin Tango device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Merlin camera plugin`_ section.

Properties
----------
================= =============== ================== =========================================================================
Property name	  Default value   Type               Description
================= =============== ================== =========================================================================
HostName          none            String             The name of the Merlin PC
CmdPort           6431            Long               The Merlin command port
DataPort          6432            Long               The Merlin data port
ImageWidth        512             Long               The width of Merlin detector head in pixels
ImageHeight       512             Long               The height of the Merlin detector head in Pixels
Chips             4               Long               The number of detector medipix3 chips
Simulate          false           Boolean            Simulate the Merlin commands.
================= =============== ================== =========================================================================

Attributes
----------
======================= ========== ================ ======================================================================
Attribute name		    Read/Write	    Type			 Description
======================= ========== ================ ======================================================================
acqRunning              R          Boolean          Is acquisition active
chargeSumming           R/W        String           Charge Summming mode 
                                                       
                                                       - ON
                                                       - OFF
                                                       
colourMode              R/W        String           Colour mode
                                                       
                                                       - MONOCHROME
                                                       - COLOUR
                                                       
continuousRW            R/W        String           Continuous Collection
                                                       
                                                       - ON
                                                       - OFF
                                                       
counter                 R/W        String           Counter
                                                       
                                                       - COUNTER0
                                                       - COUNTER1
                                                       - BOTH
                                                       
gain                    R/W        String           Gain Settings
                                                    
                                                       - SHGM
                                                       - HGM
                                                       - LGM
                                                       - SLGM
                                                       
operatingEnergy         R/W        Float            Energy keV  (0 < e < 999.99)             
softwareVersion         R          Float            Software version number
temperature             R          Float            Temperature degrees C
threshold0              R/W        Float            Threshold 0 keV (0 < th < 999.99)
threshold1              R/W        Float            Threshold 1 keV (0 < th < 999.99)
threshold2              R/W        Float            Threshold 2 keV (0 < th < 999.99)
threshold3              R/W        Float            Threshold 3 keV (0 < th < 999.99)
threshold4              R/W        Float            Threshold 4 keV (0 < th < 999.99)
threshold5              R/W        Float            Threshold 5 keV (0 < th < 999.99)
threshold6              R/W        Float            Threshold 6 keV (0 < th < 999.99)
threshold7              R/W        Float            Threshold 7 keV (0 < th < 999.99)
triggerStartType        R/W        Long             Trigger start mode
                                                    
                                                       - INTERNAL
                                                       - RISING_EDGE_TTL
                                                       - FALLING_EDGE_TTL
                                                       - RISING_EDGE_LVDS
                                                       - FALLING_EDGE_LVDS
                                                       - SOFT
triggerStopType         R/W        Long             Trigger stop mode (**INTERNAL/RISING_EDGE_TTL/FALLING_EDGE_TTL/RISING_EDGE_LVDS/FALLING_EDGE_LVDS/SOFT**)
triggerOutTTL           R/W        Long             TTL Trigger stop mode (**TTL/LVDS/TTL_DELAYED/LVDS_DELAYED/FOLLOW_SHUTTER/ONE_PER_ACQ_BURST/SHUTTER_AND_SENSOR_READ/OUTPUT_BUSY**)
triggerOutLVDS          R/W        Long             LVDS Trigger stop mode (**TTL/LVDS/TTL_DELAYED/LVDS_DELAYED/FOLLOW_SHUTTER/ONE_PER_ACQ_BURST/SHUTTER_AND_SENSOR_READ/OUTPUT_BUSY**)
triggerOutTTLInvert     R/W        Long             TTL Trigger invert mode (**NORMAL/INVERTED**)
triggerOutLVDSInvert    R/W        Long             LVDS Trigger invert mode (**NORMAL/INVERTED**)
triggerInTTLDelay       R/W        Long64           TTL Trigger delay in ns (0 < del < 68719476720)
triggerInLVDSDelay      R/W        Long64           LVDS Trigger delay in ns (0 < del < 68719476720)
triggerUseDelay         R/W        Boolean          Use Trigger delay (**ON/OFF**)
======================= ========== ================ ======================================================================

Commands
--------
=======================	================ ======================= ===========================================
Command name		    Arg. in		     Arg. out		         Description
=======================	================ ======================= ===========================================
SoftTrigger             Void             Void			         Perform soft trigger
Abort                   Void             Void                    Abort
=======================	================ ======================= ===========================================

.. _Merlin camera plugin: https://lima1.readthedocs.io/en/latest/camera/merlin/doc/index.html