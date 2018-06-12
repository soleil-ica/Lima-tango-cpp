Merlin Tango device
======================

This is the reference documentation of the Merlin Tango device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the :ref:`Merlin camera plugin <camera-merlin>` section.

Properties
----------

================= =============== =========================================================================
Property name	  Default value   Description
================= =============== =========================================================================
HostName          none            The detector IP address
CmdPort           6431            The tcp command port
DataPort          6432            The tcp data port
ImageWidth        512             The number of detector pixels
ImageHeight       512             The number of detector rasters
Chips             4               The number of detector medipix3 chips
Simulate          false           Command simulation mode
================= =============== =========================================================================

Attributes
----------

======================= ========== ================ ======================================================================
Attribute name		    Read/Write	    Type			 Description
======================= ========== ================ ======================================================================
acqRunning              R          DevBoolean       Is acquisition active
chargeSumming           R/W        DevString        Charge Summming mode (**ON/OFF**)
colourMode              R/W        DevString        Colour mode (**MONOCHROME/COLOUR**)
continuousRW            R/W        DevString        Continuous Collection (**ON/OFF**)
counter                 R/W        DevString        Counter (**COUNTER0/COUNTER1/BOTH**)
depth                   R/W        DevString        Counter depth (**BPP1/BPP6/BPP12/BPP24**)
fileDirectory           R/W        DevString        Directory name if saving on Merlin PC
fileEnable              R/W        DevString        Enable file saving to Merlin PC (**ON/OFF**)
fileName                R/W        DevString        Filename if saving on Merlin PC
gain                    R/W        DevString        Gain Settings (**SHGM/HGM/LGM/SLGM**)
operatingEnergy         R/W        DevFloat         Energy keV  (0 < e < 999.99)             
softwareVersion         R          DevFloat         Software version number
temperature             R          DevFloat         Temperature degrees C
threshold0              R/W        DevFloat         Threshold 0 keV (0 < th < 999.99)
threshold1              R/W        DevFloat         Threshold 1 keV (0 < th < 999.99)
threshold2              R/W        DevFloat         Threshold 2 keV (0 < th < 999.99)
threshold3              R/W        DevFloat         Threshold 3 keV (0 < th < 999.99)
threshold4              R/W        DevFloat         Threshold 4 keV (0 < th < 999.99)
threshold5              R/W        DevFloat         Threshold 5 keV (0 < th < 999.99)
threshold6              R/W        DevFloat         Threshold 6 keV (0 < th < 999.99)
threshold7              R/W        DevFloat         Threshold 7 keV (0 < th < 999.99)
triggerStartType        R/W        DevLong          Trigger start mode (**INTERNAL/RISING_EDGE_TTL/FALLING_EDGE_TTL/RISING_EDGE_LVDS/FALLING_EDGE_LVDS/SOFT**)
triggerStopType         R/W        DevLong          Trigger stop mode (**INTERNAL/RISING_EDGE_TTL/FALLING_EDGE_TTL/RISING_EDGE_LVDS/FALLING_EDGE_LVDS/SOFT**)
triggerOutTTL           R/W        DevLong          TTL Trigger stop mode (**TTL/LVDS/TTL_DELAYED/LVDS_DELAYED/FOLLOW_SHUTTER/ONE_PER_ACQ_BURST/SHUTTER_AND_SENSOR_READ/OUTPUT_BUSY**)
triggerOutLVDS          R/W        DevLong          LVDS Trigger stop mode (**TTL/LVDS/TTL_DELAYED/LVDS_DELAYED/FOLLOW_SHUTTER/ONE_PER_ACQ_BURST/SHUTTER_AND_SENSOR_READ/OUTPUT_BUSY**)
triggerOutTTLInvert     R/W        DevLong          TTL Trigger invert mode (**NORMAL/INVERTED**)
triggerOutLVDSInvert    R/W        DevLong          LVDS Trigger invert mode (**NORMAL/INVERTED**)
triggerInTTLDelay       R/W        DevLong64        TTL Trigger delay ns (0 < del < 68719476720)
triggerInLVDSDelay      R/W        DevLong64        LVDS Trigger delay ns (0 < del < 68719476720)
triggerUseDelay         R/W        DevBoolean       Use Trigger delay (**ON/OFF**)
======================= ========== ================ ======================================================================

Commands
--------

=======================	================ ======================= ===========================================
Command name		    Arg. in		     Arg. out		         Description
=======================	================ ======================= ===========================================
Init			        DevVoid 	     DevVoid                 Do not use
State			        DevVoid		     DevLong                 Return the device state
Status			        DevVoid		     DevString               Return the device state as a string
SoftTrigger             DevVoid          DevVoid			     Perform soft trigger
Abort                   DevVoid          DevVoid                 Abort
=======================	================ ======================= ===========================================
