static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         UviewCCD.cpp
//
// description :  C++ source for the UviewCCD and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                UviewCCD are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :    Synchrotron SOLEIL 
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name      |  Method name
//	----------------------------------------
//  State             |  dev_state()
//  Status            |  dev_status()
//  SetAverageImages  |  set_average_images()
//
//===================================================================


#include <tango.h>
#include <UviewCCD.h>
#include <UviewCCDClass.h>
#include <PogoHelper.h>

const short ROIid1 = 1;
const short ROIid2 = 2;
const short ROIid3 = 3;
const short ROIid4 = 4;

const long slidingAverageMode = 1;
const long maxNbImagesAverage = 99;
const float IntensityWindowClosed = -1;

namespace UviewCCD_ns
{

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::UviewCCD(string &s)
// 
// description : 	constructor for simulated UviewCCD
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
UviewCCD::UviewCCD(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

UviewCCD::UviewCCD(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

UviewCCD::UviewCCD(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void UviewCCD::delete_device()
{
    //	Delete device allocated objects
    DELETE_SCALAR_ATTRIBUTE(attr_ivsTRoi1_read);
    DELETE_SCALAR_ATTRIBUTE(attr_ivsTRoi2_read);
    DELETE_SCALAR_ATTRIBUTE(attr_ivsTRoi3_read);
    DELETE_SCALAR_ATTRIBUTE(attr_ivsTRoi4_read);

    INFO_STREAM << "Remove the inner-appender." << endl;
    yat4tango::InnerAppender::release(this);
}

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void UviewCCD::init_device()
{
	INFO_STREAM << "UviewCCD::UviewCCD() create device " << device_name << endl;
	
  // Initialise variables to default values
  //--------------------------------------------
  CREATE_SCALAR_ATTRIBUTE(attr_ivsTRoi1_read);
  CREATE_SCALAR_ATTRIBUTE(attr_ivsTRoi2_read);
  CREATE_SCALAR_ATTRIBUTE(attr_ivsTRoi3_read);
  CREATE_SCALAR_ATTRIBUTE(attr_ivsTRoi4_read);

  //-- INITIALIZE VARIABLES--//
  set_state(Tango::INIT);
  m_status_message.str("");
  m_is_device_initialized = false;
  m_ivs_roi_data_1 = yat::IEEE_NAN;
  m_ivs_roi_data_2 = yat::IEEE_NAN;
  m_ivs_roi_data_3 = yat::IEEE_NAN;
  m_ivs_roi_data_4 = yat::IEEE_NAN;

  INFO_STREAM << "Create the inner-appender in order to manage logs." << endl;  
  yat4tango::InnerAppender::initialize(this, 512);

  try
  {
      //- get the main object used to pilot the lima framework
      //in fact LimaDetector is create the singleton control objet
      //so this call, will only return existing object, no need to give it the ip !!
      m_ct = ControlFactory::instance().get_control("Uview");

      //- get interface to specific camera
      m_hw = dynamic_cast<Uview::Interface*>(m_ct->hwInterface());
      if(m_hw==0)
      {
          INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"UviewCCD"<<") !"<< endl;
          m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"UviewCCD"<<") !"<< endl;
          m_is_device_initialized = false;
          set_state(Tango::FAULT);
          set_status(m_status_message.str());
          return;
      }
  
  //- get camera to specific detector
  m_camera = &(m_hw->getCamera());
     
  if(m_camera == 0)
  {
    INFO_STREAM<<"Initialization Failed : Unable to get the camera of plugin !"<<endl;
    m_status_message <<"Initialization Failed : Unable to get the camera object !"<< endl;
    m_is_device_initialized = false;
    set_state(Tango::FAULT);
          set_status(m_status_message.str());
    return;			
  }		

  }
  catch(Exception& e)
  {
      INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
      m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
      m_is_device_initialized = false;
      set_state(Tango::FAULT);
      set_status(m_status_message.str());
      return;
  }
  catch(...)
  {
      INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
      m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
      set_state(Tango::FAULT);
      set_status(m_status_message.str());
      m_is_device_initialized = false;
      return;
  }

  set_state(Tango::STANDBY);
	set_status("Device initialized");
	m_is_device_initialized = true;
}

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void UviewCCD::always_executed_hook()
{
    if (m_is_device_initialized)
    {      
		//to set the running state 
		if (m_camera->m_Acq_running)
			set_state(Tango::RUNNING);
		else
		{
			set_state(Tango::STANDBY);
			set_status("Device is in idle state");
		}
		//To refresh ivs RoI values
		if (m_camera->IsIvSRoiDataReady())
		{
            m_ivs_roi_data_1 = m_camera->checkIvsROIValues(ROIid1);
            m_ivs_roi_data_2 = m_camera->checkIvsROIValues(ROIid2);
            m_ivs_roi_data_3 = m_camera->checkIvsROIValues(ROIid3);
            m_ivs_roi_data_4 = m_camera->checkIvsROIValues(ROIid4);
			//Check if signal intensity versus time window is open
			//Don't need to check on each values
            if(m_ivs_roi_data_1 == IntensityWindowClosed)
				set_status("Intensity window not open");
			else 
			{
				set_status("Acquiring intensity data for actived ROI");
				m_camera->IvSRoiDataImported();
			}
		}
	}
	
}
//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void UviewCCD::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "UviewCCD::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::read_ivsTRoi1
// 
// description : 	Extract real attribute values for ivsTRoi1 acquisition result.
//
//-----------------------------------------------------------------------------
void UviewCCD::read_ivsTRoi1(Tango::Attribute &attr)
{
	DEBUG_STREAM << "UviewCCD::read_ivsTRoi1(Tango::Attribute &attr) entering... "<< endl;
	//To check if ROI is valid (if window is open and if ROI is specified)
    if (m_ivs_roi_data_1 >= 0)
        *attr_ivsTRoi1_read = m_ivs_roi_data_1;
	else //ROI is not valid
		*attr_ivsTRoi1_read = yat::IEEE_NAN;
    //To set value on attribut
	attr.set_value(attr_ivsTRoi1_read);
}

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::read_ivsTRoi2
// 
// description : 	Extract real attribute values for ivsTRoi2 acquisition result.
//
//-----------------------------------------------------------------------------
void UviewCCD::read_ivsTRoi2(Tango::Attribute &attr)
{
	DEBUG_STREAM << "UviewCCD::read_ivsTRoi2(Tango::Attribute &attr) entering... "<< endl;
	//To check if ROI is valid (if window is open and if ROI is specified)
    if (m_ivs_roi_data_2 >= 0)
        *attr_ivsTRoi2_read = m_ivs_roi_data_2;
	else //ROI is not valid
		*attr_ivsTRoi2_read = yat::IEEE_NAN;
    //To set value on attribut
	attr.set_value(attr_ivsTRoi2_read);
}

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::read_ivsTRoi3
// 
// description : 	Extract real attribute values for ivsTRoi3 acquisition result.
//
//-----------------------------------------------------------------------------
void UviewCCD::read_ivsTRoi3(Tango::Attribute &attr)
{
	DEBUG_STREAM << "UviewCCD::read_ivsTRoi3(Tango::Attribute &attr) entering... "<< endl;
	//To check if ROI is valid (if window is open and if ROI is specified)
    if (m_ivs_roi_data_3 >= 0)
        *attr_ivsTRoi3_read = m_ivs_roi_data_3;
	else //ROI is not valid
		*attr_ivsTRoi3_read = yat::IEEE_NAN;
    //To set value on attribut
	attr.set_value(attr_ivsTRoi3_read);
}

//+----------------------------------------------------------------------------
//
// method : 		UviewCCD::read_ivsTRoi4
// 
// description : 	Extract real attribute values for ivsTRoi4 acquisition result.
//
//-----------------------------------------------------------------------------
void UviewCCD::read_ivsTRoi4(Tango::Attribute &attr)
{
	DEBUG_STREAM << "UviewCCD::read_ivsTRoi4(Tango::Attribute &attr) entering... "<< endl;
	//To check if ROI is valid (if window is open and if ROI is specified)
    if (m_ivs_roi_data_4 >= 0)
        *attr_ivsTRoi4_read = m_ivs_roi_data_4;
	else //ROI is not valid
		*attr_ivsTRoi4_read = yat::IEEE_NAN;
    //To set value on attribut
	attr.set_value(attr_ivsTRoi4_read);	
}
//+------------------------------------------------------------------
/**
 *	method:	UviewCCD::set_average_images
 *
 *	description:	method to execute "SetAverageImages"
 *	Argin :
 *	0 no average,
 *	1 sliding average,
 *	1-99 :  nb image to average
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void UviewCCD::set_average_images(Tango::DevLong argin)
{
	DEBUG_STREAM << "UviewCCD::set_average_images(): entering... !" << endl;

	//	Add your own code to control device here

	long value = argin;

	if (0 <= value &&  value <= maxNbImagesAverage) 
		m_camera->setAverage(value);
	else
	{
	    //- throw exception
        Tango::Except::throw_exception( "TANGO_DEVICE_ERROR",
                                        "incorrect entry, must be between 0 and 99",
                                        "UviewCCD::set_average_images");
	}
}


}	//	namespace
