.. _lima-tango-maxipix:

ProsilicaCCD Tango C++ device
=============================

This is the reference documentation of the BaslerCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `Prosilica camera plugin`_ section.


Properties
----------

======================== ==================== ===================== =====================================
Property name            Default value        Type                  Description
======================== ==================== ===================== =====================================
DetectorIP               127.0.0.1            String                Ip Address of the Detector.
======================== ==================== ===================== =====================================


Attributes
----------
No Attribute


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================

.. _Prosilica camera plugin: https://lima1.readthedocs.io/en/latest/camera/prosilica/doc/index.html
