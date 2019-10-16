.. _lima-tango-simulator:

SimulatorCCD C++ Tango device
=============================

This is the reference documentation of the SimulatorCDD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Simulator camera plugin`_ section.


Properties
----------
No Property


Attributes
----------

============================= ===================== ================= ======================================
Attribute name                Read/Write            Type              Description
============================= ===================== ================= ======================================
growFactor                    R/W                   Double            Grow factor.
fillType                      R/W                   String            Gauss or Diffraction.
xOffset                       R/W                   Double            Set an offset on image when using GAUSS mode.
yOffset                       R/W                   Double            Set an offset on image when using GAUSS mode.
============================= ===================== ================= ======================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Simulator camera plugin: https://lima1.readthedocs.io/en/latest/camera/simulator/doc/index.html
