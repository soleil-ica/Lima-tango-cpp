Uview C++ Tango device
======================
This is the reference documentation of the UviewCCD Tango C++ device.

Attributes
----------
Only four attributes for this device : 
  - Four differents intensities versus time values, depending on four specifics user ROIs
  - ROIs needs to be set in the Uview specific program
=================     ================  ================ ==========================================
Attribute name	      Read/Write        Type             Description
=================     ================  ================ ==========================================
ivsTRoi1              Read              DEV_FLOAT        Intensity versus time on first ROI window
ivsTRoi2              Read              DEV_FLOAT        Intensity versus time on second ROI window
ivsTRoi3              Read              DEV_FLOAT        Intensity versus time on third ROI window
ivsTRoi4              Read              DEV_FLOAT        Intensity versus time on fourth ROI window
=================     ================  ================ ==========================================

Commands
--------
=================     ================  ================ ==========================================
Attribute name	      Arg. in           Arg. out         Description
=================     ================  ================ ==========================================
Init                  DevVoid           DevVoid          Do not use
State                 DevVoid           DevLong          Return the device state
Status                DevVoid           DevString        Return the device state as a string
SetAverageImages      DevLong           DevVoid          0 no average, 1 sliding average, 2-99 :  nb image to average         
=================     ================  ================ ==========================================

--------