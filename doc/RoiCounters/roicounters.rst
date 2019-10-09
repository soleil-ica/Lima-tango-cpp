RoiCounters C++ Tango device
============================

**RoiCounters** is a post process specific device

The Region-of-Interest to Counter operation is very useful to provide online statistics on some image areas.

The operation will calculate for each acquired image the : 

- the average of pixels
- the standard deviation
- the sum of pixels
- the minimum pixel value
- the coordinates (X,Y) of the minimum pixel
- the maximum pixel value
- the coordinates (X,Y) of the maximum pixel

User can configure one or many Region Of Interest (32 Rois at Maximum)

User can also configure the order of this operation in the chain of operations already defined


Properties
----------

============================ ==================== ================= =======================================================================
Property name                Default value        Type              Description
============================ ==================== ================= =======================================================================
NbRoiCounters                2                                      Fix the number of Region Of Interest.
__x                          0                                      (Origin X) for each Region of Interest.

                             0
__y                          0                                      (Origin Y) for each Region of Interest.

                             0
__width                      10                                     (Width) for each Region of Interest.

                             10
__height                     10                                     (Height) for each Region of Interest.

                             10
============================ ==================== ================= =======================================================================


Attributes
----------

=========================== ============= ==================== ==============================================
Attribute name              Read/Write    Type                 Description
=========================== ============= ==================== ==============================================
version                     R             String               Display the Version of the RoiCounters Device.
runLevel                    W             ULong                Fix the execution order of this operation in the processing chain.
frameNumber                 R             ULong                The frame number on wich the 'roi counters' computation were made.
operationsList              R             String               Enumerate all RoiCounters active 'post processing' operations on the image.
=========================== ============= ==================== ==============================================


Dynamic attributes (for each defined Roi)
---------------------------------------------------------------
=========================== ============= =============================== =====================================
Attribute name              Read/Write    Type                            Description
=========================== ============= =============================== =====================================
x                           R/W           ULong                           The x coordinate of the Roi.
y                           R/W           ULong                           The y coordinate of the Roi.
width                       R/W           ULong                           The width of the Roi.
height                      R/W           ULong                           The height of the Roi.
sum                         R             Double                          The sum of pixels in the Roi.
average                     R             Double                          The average of pixels in the Roi.
std                         R             Double                          The std deviation of pixels in the Roi.
minValue                    R             Double                          The min of pixels in the Roi.
minX                        R             Double                          The coordinate X of the min of pixels in the Roi.
minY                        R             Double                          The coordinate Y of the min of pixels in the Roi.
maxValue                    R             Double                          The max of pixels in the Roi.
maxX                        R             Double                          The coordinate X of the max of pixels in the Roi.
maxY                        R             Double                          The coordinate Y of the max of pixels in the Roi.
=========================== ============= =============================== =====================================


Commands
--------

======================= =============== ======================= ===========================================
Command name            Arg. in         Arg. out                Description
======================= =============== ======================= ===========================================
Init                    Void            Void                    Do not use
State                   Void            Long                    Return the device state
Status                  Void            String                  Return the device state as a string
======================= =============== ======================= ===========================================
