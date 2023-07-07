LimaDetector class
====================

**LimaDetector** is the generic class and it provides a unique interface to control any supported camera. 

One can find below the properties, commands, and attributes and their descriptions.

At the 1st start of the device server, all the properties are created with the default values.

To run a LimaDetector device you will need at least to configure the **DetectorType** property.

This property is used by the LimaDetector device to communicate with the associated camera plugin. 

Please refer a specific camera device chapter for further information.

Properties
----------

===============================     ========================    ==================      ===============================================
Property name                       Default value               Type                    Description
===============================     ========================    ==================      ===============================================
DetectorType                        SimulatorCCD                String                  Define the type of the Detector. 

                                                                                        Availables types :

                                                                                        - AndorCCD                                                                                                                                                                                
                                                                                        - BaslerCCD
                                                                                        - Dhyana
                                                                                        - Eiger                                                                                             
                                                                                        - Hamamatsu                                                                                         
                                                                                        - ImXpad      
                                                                                        - Lambda
                                                                                        - MarCCD                                                                                            
                                                                                        - Maxipix                                                                                           
                                                                                        - Merlin                                                                                            
                                                                                        - Pco                                                                                               
                                                                                        - PerkinElmer                                                                                       
                                                                                        - PilatusPixelDetector                                                                              
                                                                                        - PrincetonCCD                                                                                                                                                                        
                                                                                        - SimulatorCCD    
                                                                                        - SlsEiger
                                                                                        - SlsJungfrau
                                                                                        - Ufxc
                                                                                        - UviewCCD                                                                                          
                                                                                        - XpadPixelDetector

AutoSaveResetRoi                    false                       Boolean                 Memorize the "full frame" automatically at the call of "ResetRoi"                                    

AutoStartVideo                      false                       Boolean                 Allows calling automatically the "Start" command when:                                            

                                                                                        The device starts                                                                                 
                                                                                        
                                                                                        After calling the "Init" command                                                                  

DebugFormats                        DateTime                    Array of String         Define Lima traces formats.  
                                    Module
                                    Type                                               
                                                                                        Availables values : (a combination of these) 
                                                                                        
                                                                                        - DateTime                                                                                          
                                                                                        - Thread                                                                                            
                                                                                        - Module                                                                                            
                                                                                        - Obj                                                               
                                                                                        - Funct
                                                                                        - FileLine

DebugLevels                         Fatal                       Array of String         Define Lima traces levels.    
                                    Error
                                    Warning                                             
                                                                                        Availables values : (a combination of these)
                                                                                        
                                                                                        - Fatal                                                                                             
                                                                                        - Error                                                                                             
                                                                                        - Warning                                                                                           
                                                                                        - Trace                                                                                             
                                                                                        - Funct                                                                                             
                                                                                        - Param                                                                                             
                                                                                        - Return                                                                                            
                                                                                        - Always                                                                                            

DebugModules                        Hardware                    Array of String         Define Lima traces modules. 
                                    Control
                                    Common                                              
                                    Camera
                                                                                        
                                                                                        Availables values : (a combination of these)
                                                                                        
                                                                                        - None                                                                                              
                                                                                        - Hardware                                                                                          
                                                                                        - Control                                                                                           
                                                                                        - Common                                                                                            
                                                                                        - Camera                                                                                            

DetectorDescription                 This is my Simulator        String                  Detector user-defined text to identify the engine.                                                   

DetectorPixelDepth                  16                          String                  Define the pixel depth of the detector.

                                                                                        Availables values :
                                                                                        
                                                                                        - 2
                                                                                        - 8                                                                                                 
                                                                                        - 12                                                                                                
                                                                                        - 14
                                                                                        - 16                                                                                                
                                                                                        - 16S                                                                                               
                                                                                        - 24                                                                                                
                                                                                        - 24S                                                                                               
                                                                                        - 32                                                                                                
                                                                                        - 32S                                                                                               

DetectorVideoMode                   NONE                        String                  Define the format of video stream. 

                                                                                        Availables types :
                                          
                                                                                        - NONE                                                                                              
                                                                                        - Y8                                                                                                
                                                                                        - Y16                                                                                               
                                                                                        - Y32                                                                                               
                                                                                        - Y64                                                                                               
                                                                                        - RGB555                                                                                            
                                                                                        - RGB565
                                                                                        - RGB24
                                                                                        - RGB32
                                                                                        - BGR24
                                                                                        - BGR32
                                                                                        - BAYER_RG8
                                                                                        - BAYER_RG16
                                                                                        - I420
                                                                                        - YUV411
                                                                                        - YUV422
                                                                                        - YUV444

ExpertBufferMaxMemoryPercent        70                          UShort                  Define the Percent of available system memory reserved to Lima buffer control :

ExpertNbPoolThread                  4                           UShort                  Defines the number of threads dedicated to process images in the PricessLib

ExpertUsePrepareCmd                 false                       Boolean                 If true, a call of 'Prepare' command is necessary before each 'Snap' or 'Start' command.

FileIndexPattern                    %06d                        String                  Define the pattern of the index used for image files names.

                                                                                        Nota : %04d mean that file name index will be end with exactly 4 digits filled by '0' if necessary

FileManagedMode                     SOFTWARE                    String                  Define the File managed Mode : (one of these)

                                                                                        - HARDWARE: use the hardware saving system                                                          
                                                                                        - SOFTWARE: use the software saving system

FileMemoryMode                      NO_COPY                     String                  Available only for Nexus format 

                                                                                        Set the SetDataItemMemoryMode()
                                                                                        
                                                                                        Available values :
                                                                                        
                                                                                        - COPY: the nexus lib make its own copy of the image and then works on it
                                                                                        - NO_COPY: the nexus lib use the buffer image allocated by the lima memory manager

FileTimestampEnabled                true                        Boolean                 Available only for Nexus format

                                                                                        enable/disable the creation a dataset for the image timestamp in the file

FileWriteMode                       SYNCHRONOUS                 String                  Available only for Nexus format

                                                                                        Set the SetWriteMode(). 
                                                                                        
                                                                                        Available values : (one of these)      
                                                                                        
                                                                                        - ASYNCHRONOUS                                                                                      
                                                                                        - SYNCHRONOUS                                                                                       

ImageOpMode                         HardAndSoft                 String                  Define ImageOpMode for Roi/Binning/etc... 
                                                                                        
                                                                                        Available values : 
                                                                                        
                                                                                        - HardOnly                                                                                          
                                                                                        - SoftOnly                                                                                          
                                                                                        - HardAndSoft                                                                                       

ImageSource                         VIDEO                       String                  Choose the source of Data given to the image attribute :

                                                                                        - VIDEO : use ctVideo->LastImage() : monitoring mode, not all images are displayed 
                                                                                        
                                                                                        **Nota** : image processing as Flip/Rotation/Mask/etc... are **DISABLED**  in this mode
                                                                                        
                                                                                        - ACQUISITION : use ctControl->ReadImage() : all images are displayed
===============================     ========================    ==================      ===============================================


Attributes
----------

===============================     ========================    ==================      ===============================================
Attribute name                      Read/Write                  Type                    Description                                                                                
===============================     ========================    ==================      ===============================================
detectorDescription                 R                           String                  Detector user-defined text to identify the engine.                                                   
                                                                
detectorType                        R                           String                  type of the Detector                                                                                 
                                                                
detectorModel                       R                           String                  model of the Detector                                                                                
                                                                
detectorWidthMax                    R                           UShort                  Maximum width                                                                                        
                                                                
detectorHeightMax                   R                           UShort                  Maximum height                                                                                       
                                                                
detectorPixelDepth                  R                           UShort                  Pixel resolution in bits (eg: 2, 8 , 12 , 14, 16 ...)                                                       
                                                                
binnedWidthMax                      R                           UShort                  Detector max width taking into account the current Horizontal Binning                                
                                                                
binnedHeightMax                     R                           UShort                  Detector max width taking into account the current Vertical Binning                                  
                                                                
triggerMode                         R/W                         String                  Current Trigger Mode

                                                                                        Available possible values for each camera model, can be consulted through the command GetAttributeAvailableValues("triggerModes")      
                                                                
acquisitionMode                     R/W                         String                  Acquisition modes

                                                                                        Available values:  
                                                                
                                                                                        - SINGLE: standard mode                                                                             
                                                                                        - ACCUMULATION: accumulate frames                                                                   
                                                                
exposureTime                        R/W                         Double                  Exposure time (in ms) 
                                                                
                                                                                        Nota : can be changed during Live view (i.e only when Start command is used )
                                                                
latencyTime                         R/W:                        Double                  Latency time (in ms)                                                                                 
                                                                
frameRate                           R/W                         Double                  Compute the latency thanks to the current exposureTime                                               
                                                                
roiX                                R                           UShort                  Region of Interest . (Origin X)                                                                      
                                                                
roiY                                R                           UShort                  Region of Interest . (Origin Y)                                                                      
                                                                
roiWidth                            R                           UShort                  Region of Interest . (Width)                                                                         
                                                                
roiHeight                           R                           UShort                  Region of Interest . (Height)                                                                        
                                                                
binningH                            R                           UShort                  Horizontal binning                                                                                   
                                                                
binningV                            R                           UShort                  Vertical binning                                                                                     
                                                                
nbFrames                            R/W                         Long                    Number of frames to acquire 
                                                                
                                                                                        Nota : Forced to zero when acquisition is started by Start command
                                                                
currentFrame                        R                           ULong                   Current acquired frame number                                                                        
                                                                
fileGeneration                      W                           Boolean                 Enable/Disable the file saving                                                                       
                                                                
fileFormat                          W                           String                  Set the saving file format 
                                                                
                                                                                        Available values: 
                                                                
                                                                                        - NXS
                                                                                        - EDF
                                                                                        - HDF5
                                                                                        - RAW
                                                                
filePrefix                          W                           String                  Prefix name of the saved file (underscore is automatically added at the end)                         
                                                                
fileTargetPath                      W                           String                  Target path for the saved file                                                                       
                                                                
fileNbFrames                        W                           Long                    Number of frame per file

fileExtension                       R                           String                  Actual Extension of the file
                                                                
image                               R                           Available types:        Last acquired image possibly modified by active 'post processing' 
                                                                
                                                                UChar
                                                                UShort
                                                                ULong
                                                                Long
                                                                Float
                                                                
baseImage                           R                           Available types:        Last acquired image without any 'post processing' operations on the image 
                                                                
                                                                UChar
                                                                UShort
                                                                ULong
                                                                Long
                                                                Float
                                                                
operationsList                      R                           String (Spectrum)       Enumerate all (Layout, Mask, RoiCounters) active 'post processing' operations on the image           
                                                                
log                                 R                           Array of String         Logs from Tango and Lima                                                                             
                                                                
info                                R                           Array of String         Informations on version of LimaCore and plugins                                                      
===============================     ========================    ==================      ===============================================


Optionnal attributes (depend on config)
---------------------------------------
===============================     ========================    ==================      ===============================================
Attribute name                      Read/Write                  Type                    Description
===============================     ========================    ==================      ===============================================
shutterMode                         R/W                         String                  Shutter modes. Available values:

                                                                                        - MANUAL: opened and closed manually by OpenShutter and CloseShutter commands
                                                                                        - AUTO_FRAME: the shutter output signal is activated for each frame of a sequence
                                                                                        - AUTO_SEQUENCE: the shutter output signal is activated for the whole sequence
                                                                
shutterState                        R                           String                  State of the Shutter (in case of MANUAL mode)
                                                                
shutterOpenTime                     R/W                         Double                  Delay (ms) between the output shutter trigger and the beginning of the acquisition.
                                                                
                                                                                        if not null the shutter signal is set on before the acquisition is started.

shutterCloseTime                    R/W                         Double                  Delay (ms)  between the shutter trigger and the end of the acquisition.
                                                                
                                                                                        if not null the shutter signal is set on before the end of the acquisition.
                                                                
exposureAccTime                     R/W                         Double                  Accumulation exposure time (ms).
                                                                
currentAccFrame                     R                           ULong                   Current accumulation acquired frame.
===============================     ========================    ==================      ===============================================


Commands
--------
===============================     ========================    ==================      ===============================================
Command name                        Arg. in                     Arg. out                Description
===============================     ========================    ==================      ===============================================
Init                                Void                        Void                    Init the device
                        
State                               Void                        Long                    Return the device state
                        
Status                              Void                        String                  Return the device state as a string
                        
Prepare                             Void                        Void                    Prepare the acquisition 

                                                                                        Apply parameters like bin/roi/exposure/.. & allocate buffers & ... outside the command 'Snap'

                                                                                        Available only if the property ExpertUsePrepareCmd is True


Snap                                Void                        Void                    Starts the acquisition of a number of frames equal to 'nbFrames' attribute value.
                        
Start                               Void                        Void                    Starts a "video/live" acquisition of an infinite number of frames.

                                                                                        In this mode, the loss of some images does not stop the acquisition state and it is not signaled by a FAULT state

                                                                                        It is not allowed to generate files in this mode.
                                    
Stop                                Void                        Void                    Stop current acquisition previously started by Start or Snap command.
                                
SetROI                              VarULongArray:              Void                    Define a Region of Interest .

                                                                                        (OriginX, OriginY, Width, Height)

                                    origin_x                                            Roi and Binning are associated.

                                    origin_y

                                    width 

                                    height
        
SetBinning                          VarULongArray:                Void                  Define a binning Horizontal (x) & Vertical (y) according to current Roi.

                                    bin_x

                                    bin_y
                                    
ResetBinning                        Void                        Void                    Use the binning Horizontal (x = 1) & Vertical (y = 1) according to current Roi.
        
ResetROI                            Void                        Void                    Use the full frame of the detector according to current Binning.

GetAttributeAvailableValues         String:                     VarStringArray:         Return available values of the given String attribute

                                    Attribute name              available values        
                                    
GetAvailableCapabilities            Void                        Void                    Return available capabilities of the camera 

                                                                                        (eg: DetInfo, Bin, Roi ...)
ResetFileIndex                      Void                        Void                    Reset the file index
ReloadROI                           Void                        Void                    This command allows reloading the last ROI previously configured by the SetROI command.
===============================     ========================    ==================      ===============================================


Optionnal commands (depend on config)
-------------------------------------

===============================     ========================    ==================      ===============================================
Command name                        Arg. in                     Arg. out                Description
===============================     ========================    ==================      ===============================================
OpenShutter                         Void                        Void                    Open the shutter 

                                                                                        Nota : Only if shutterMode is MANUAL

CloseShutter                        Void                        Long                    Close the shutter 

                                                                                        Nota : Only if shutterMode is MANUAL
===============================     ========================    ==================      ===============================================

