.. _lima-tango-perkinelmer:

PerkinElmer Tango C++ device
=============================

This is the reference documentation of the BaslerCCD Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `PerkinElmer camera plugin`_ section.


Properties
----------
No Property


Attributes
----------

=========================== ================ ================ =====================================
Attribute name              Read/Write       Type             Description
=========================== ================ ================ =====================================
correctionMode              R/W              String           Correction mode. Possible values:

                                                              - NO
                                                              - OFFSET ONLY
                                                              - OFFSET AND GAIN
keepFirstImage              R/W              Boolean          Flag stating if 1st image is kept
gain                        R/W              Long             Gain value, from 0 to 63
=========================== ================ ================ =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
StartAcqOffsetImage     DoubleArray     Void                    Set offset
StartAcqGainImage       DoubleArray     Void                    Set gain
======================= =============== ======================= ===========================================

.. _PerkinElmer camera plugin: https://lima1.readthedocs.io/en/latest/camera/perkinelmer/doc/index.html
