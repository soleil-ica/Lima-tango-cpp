Mask class
====================

**Mask** is a post process specific device
The image mask is defined by the user by writing the maskImage attribute.
Each pixel defined to 'zero' in the maskImage will set the pixel of the acquired image to "zero"

Properties
----------

======================== ================================= =====================================
Property name	         Default value	                   Description
======================== ================================= =====================================
======================== ================================= =====================================

Attributes
----------

===========================     ================  ================ ====================================================================
Attribute name                  Read/Write        TypeDescription
===========================     ================  ================ ====================================================================
version                         R                 DevString           Display the Version of the Mask Device
runLevel                        W                 DevULong            Fix the execution order of this operation in the processing chain
operationsList                  R                 DevString           Enumerate all Mask active 'post processing' operations on the image
maskImage                       R/W               DevShort            Define the mask image for the Mask Processing
===========================     ================  ================ ====================================================================

Commands
--------

=======================	=============== =======================	=======================================================================
Command name            Arg. in         Arg. out                Description
=======================	=============== =======================	=======================================================================
Init                    DevVoid         DevVoid                 Do not use
State                   DevVoid         DevLong                 Return the device state
Status                  DevVoid         DevString               Return the device state as a string
=======================	=============== =======================	=======================================================================


