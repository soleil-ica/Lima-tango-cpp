.. _lima-tango-maxipix:

PerkinElmer Tango C++ device
=============================

This is the reference documentation of the BaslerCCD Tango C++ device.

you can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `PerkinElmer camera plugin`_ section.

Properties
----------

======================== ==================== ===================== =====================================
Property name	         Default value	      Type                  Description
======================== ==================== ===================== =====================================
DetectorIP               127.0.0.1            String                Ip Address of the Detector.
======================== ==================== ===================== =====================================

Attributes
----------

===========================     ================  ================ =====================================
Attribute name	                Read/Write        Type             Description
===========================     ================  ================ =====================================
frameRate                       R                 Double           Display the current frame rate (nb frames/s)
===========================     ================  ================ =====================================

Commands
--------

=======================	=============== =======================	===========================================
Command name		    Arg. in		    Arg. out		        Description
=======================	=============== =======================	===========================================
Init			        Void 	        Void			        Do not use
State			        Void		    Long			        Return the device state
Status			        Void		    String		            Return the device state as a string
=======================	=============== =======================	===========================================

.. _PerkinElmer camera plugin: https://lima1.readthedocs.io/en/latest/camera/perkinelmer/doc/index.html
