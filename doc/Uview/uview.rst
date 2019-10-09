.. _lima-tango-uview:

Uview C++ Tango device
======================

This is the reference documentation of the UviewCCD Tango C++ device.


Properties
----------
No Property


Attributes
----------
Only four attributes for this device : 
  - Four differents intensities versus time values, depending on four specifics user ROIs
  - ROIs needs to be set in the Uview specific program

=================     ================  ================ ==========================================
Attribute name        Read/Write        Type             Description
=================     ================  ================ ==========================================
ivsTRoi1              Read              Float            Intensity versus time on first ROI window
ivsTRoi2              Read              Float            Intensity versus time on second ROI window
ivsTRoi3              Read              Float            Intensity versus time on third ROI window
ivsTRoi4              Read              Float            Intensity versus time on fourth ROI window
=================     ================  ================ ==========================================


Commands
--------
=================     ================  ================ ==========================================
Attribute name        Arg. in           Arg. out         Description
=================     ================  ================ ==========================================
Init                  Void              Void             Do not use
State                 Void              Long             Return the device state
Status                Void              String           Return the device state as a string
SetAverageImages      Long              Void             0 no average, 1 sliding average, 2-99 :  nb image to average         
=================     ================  ================ ==========================================
