Mask class
====================

**Mask** is a post process specific device
The image mask is defined by the user by writing the maskImage attribute.
Each pixel defined to 'zero' in the maskImage will set the pixel of the acquired image to "zero"

Properties
----------
No Property


Attributes
----------

=========================== ================  ================ ====================================================================
Attribute name              Read/Write        Type             Description
=========================== ================  ================ ====================================================================
version                     R                 String           Display the Version of the Mask Device
runLevel                    W                 ULong            Fix the execution order of this operation in the processing chain
operationsList              R                 String           Enumerate all Mask active 'post processing' operations on the image
maskImage                   R/W               Short            Define the mask image for the Mask Processing
=========================== ================  ================ ====================================================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================
