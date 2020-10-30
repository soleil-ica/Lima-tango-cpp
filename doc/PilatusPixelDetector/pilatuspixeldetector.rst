.. _lima-tango-pilatus:

PilatusPixelDetector Tango C++ device
=====================================

This is the reference documentation of the PilatusPixelDetector Tango C++ device.

You can also find some useful information about the camera models/prerequisite/installation/configuration/compilation in the `PilatusPixelDetector camera plugin`_ section.


Properties
----------

=============================== ======================== ================== ===============================================
Property name                   Default value               Type                    Description
=============================== ======================== ================== ===============================================
DetectorPort                    6666                     Long               Detector port number of Camserver 
DetectorIP                      127.0.0.1                String             Detector IP address of CamServer
DetectorCameraDefFileName       NONE                     String             Detector path of file containing informations about (model, size, pixeldepth, ...).
UseReader                       True                     Boolean            Enable/Disable monitoring of the directory receiving image files in order to read images provided by CamServer & to display image in the attribute image
ReaderTimeout                   10000                    ULong              This is the elapsed time before declaring that is no available image returned by CamServer during the Acquisition. (in ms)
=============================== ======================== ================== ===============================================


Attributes
----------

=============================== ======================== ================== ===============================================
Attribute name                  Read/Write               Type               Description
=============================== ======================== ================== ===============================================
energy                          R/W                      Double             Define a new energy (in eV).
threshold                       R/W                      Long               Define a new threshold (in eV).
gain                            R/W                      String             Define the gain

                                                                            Available Gain values:

                                                                            - LOW
                                                                            - MID
                                                                            - HIGH
                                                                            - UHIGH
imagePath                       R/W                      String             Define the image path of CamSever.

                                                                            If the directory does not exist, it will be created by CamServer if it is possible according to permissions parameters.

                                                                            A path relative to the current path is accepted by camServer.
fileName                        R/W                      String             Image file pattern name.
=============================== ======================== ================== ===============================================


Commands
--------

=============================== ======================== ================== ===============================================
Command name                        Arg. in                     Arg. out                Description
=============================== ======================== ================== ===============================================
Init                            Void                     Void               Do not use
State                           Void                     Long               Return the device state
Status                          Void                     String             Return the device state as a string
SetEnergy                       Double                   Void               Define Energy in eV.
SetThresholdAndGain             LongStringArray          Void               Define Threshold (eV) and Gain (LOW, MID, HIGH, UHIGH).
SetMxSettings                   String                   Void               Set crystallographic parameters reported in the image header.

                                                                            [param_name value] [param_name value] ...

                                                                            List of available param_name :

                                                                            - Wavelength
                                                                            - Energy_range
                                                                            - Detector_distance
                                                                            - Detector_Voffset 
                                                                            - Beam_xy,
                                                                            - Beam_x 
                                                                            - Beam_y
                                                                            - Flux
                                                                            - Filter_transmission
                                                                            - Start_angle
                                                                            - Angle_increment
                                                                            - Detector_2theta
                                                                            - Polarization
                                                                            - Alpha
                                                                            - Kappa
                                                                            - Phi
                                                                            - Phi_increment 
                                                                            - Chi
                                                                            - Chi_increment
                                                                            - Oscillation_axis
                                                                            - N_oscillations
                                                                            - Start_position,
                                                                            - Position_increment
                                                                            - Shutter_time
                                                                            - CBF_template_file
SendAnyCommand                  String                   Void               Allow to send any command to Camserver.

                                                                            See documentation of Pilatus/Camserver for more details of communication protocol .
GetTH                           Void                     DoubleArray        Read temperature (of nb sensors) and humidity (of nb sensors) of the detector
=============================== ======================== ================== ===============================================

.. _PilatusPixelDetector camera plugin: https://lima1.readthedocs.io/en/latest/camera/pilatus/doc/index.html
