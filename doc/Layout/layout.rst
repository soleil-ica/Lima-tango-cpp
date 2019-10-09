Layout class
====================

**Layout** is a post process specific device

User can configure one or many arithmetics operations (+ , - , * , / , >> , << ) & transformations (FLIP, Rotation) on the image 

User can also configure an order of each operation in the operations chain


Properties
----------
No Property


Attributes
----------

=========================== ============= ==================== =======================================================================
Attribute name              Read/Write    Type                 Description
=========================== ============= ==================== =======================================================================
version                     R             String               Display the Version of the Layout Device.
operationType               R/W           String               Available operation types :

                                                               - \+
                                                               - \-
                                                               - \*
                                                               - /
                                                               - >>
                                                               - <<
                                                               - ROTATION
                                                               - FLIP
operationValue              R/W           String               Arithmetic operationType : any arithmetic value can be used.

                                                               FLIP operationType : only X, Y, XY value can be used.

                                                               ROTATION operationType : only 90, 180, 270 value can be used.
operationsList              R             String               Enumerate all Layout active 'post processing' operations on the image.
=========================== ============= ==================== =======================================================================


Commands
--------

========================== ========= ================= ================================================================================
Command name               Arg. in   Arg. out          Description
========================== ========= ================= ================================================================================
Init                       Void      Void              Do not use.
State                      Void      Long              Return the device state.
Status                     Void      String            Return the device state as a string.
AddOperation               Long      Void              Add Lima external operation in order to transform the image.

                                                       User must first define the operationType, operationValue.

                                                       argin will define the level of operation.
RemoveOperation            Long      Void              Remove a Lima external operation previously defined at the level argin.
========================== ========= ================= ================================================================================
