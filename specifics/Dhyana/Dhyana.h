/*----- PROTECTED REGION ID(Dhyana.h) ENABLED START -----*/
//=============================================================================
//
// file :        Dhyana.h
//
// description : Include file for the Dhyana class
//
// project :     Device specific for Dhyana detector
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef Dhyana_H
#define Dhyana_H

#include <tango.h>
#include "Factory.h"
#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>
#include "DhyanaInterface.h"

#include <yat/memory/UniquePtr.h>

#include "DhyanaCamera.h"

#include "AttrView.h"

#define TUCAM_VERSION  "1.0.0"

#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2

using namespace lima;
using namespace std;
using namespace yat4tango;
 
/*----- PROTECTED REGION END -----*/	//	Dhyana.h

/**
 *  Dhyana class description:
 *    Interface the camera Dhyana using  the TUCAM Library
 */

namespace Dhyana_ns
{
/*----- PROTECTED REGION ID(Dhyana::Additional Class Declarations) ENABLED START -----*/

enum class TriggeroutMode : short
{
	kEXPOSURESTART,
	kREADOUT,
	kGLOBAL
};

enum class EdgeMode : short
{
	kRISING,
	kFAILING
};

/*----- PROTECTED REGION END -----*/	//	Dhyana::Additional Class Declarations

class Dhyana : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(Dhyana::Data Members) ENABLED START -----*/

//	Add your own data members
public:
	/*Tango::DevString	attr_globalGain_write;
	Tango::DevUShort	attr_fanSpeed_write;
	Tango::DevDouble	attr_temperatureTarget_write;
	channel1Enum	attr_channel1_write;
	channel2Enum	attr_channel2_write;
	channel3Enum	attr_channel3_write;
	Tango::DevDouble	attr_width1_write;
	Tango::DevDouble	attr_width2_write;
	Tango::DevDouble	attr_width3_write;
	Tango::DevDouble	attr_delay1_write;
	Tango::DevDouble	attr_delay2_write;
	Tango::DevDouble	attr_delay3_write;
	edge1Enum	attr_edge1_write;
	edge2Enum	attr_edge2_write;
	edge3Enum	attr_edge3_write;*/
	yat::UniquePtr<AttrView> m_attr_view;
/*----- PROTECTED REGION END -----*/	//	Dhyana::Data Members

//	Device property data members
public:
	//	__ExpertTimerPeriod:	Timer period in ms.<cr>
	//  useful only for Internal Trigger
	Tango::DevUShort	__ExpertTimerPeriod;


//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Dhyana(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Dhyana(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	Dhyana(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~Dhyana() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : Dhyana::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);


	//--------------------------------------------------------
	/**
	 *	Method      : Dhyana::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command State related method
	 *	Description: This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
	 *
	 *	@returns State Code
	 */
	virtual Tango::DevState dev_state();
	/**
	 *	Command GetAllParameters related method
	 *	Description: Return the list of all the camera available parameters and their values in the following format:
	 *               GROUP_OF_PROPERTIES:ParameterName = value
	 *               
	 *               Available values for GROUP_OF_PROPERTIES are:
	 *               - PROP fo Control properties
	 *               - CAPA for Control capability properties
	 *               - VENDOR for Vendor control properties
	 *               - ROIS for Process image properties
	 *
	 *	@returns 
	 */
	virtual Tango::DevString get_all_parameters();
	virtual bool is_GetAllParameters_allowed(const CORBA::Any &any);
	/**
	 *	Command GetParameter related method
	 *	Description: Return the current value of a specified parameter
	 *               
	 *               Input argument has to be in the following format:
	 *               GROUP_OF_PROPERTIES:parameter_name
	 *
	 *	@param argin 
	 *	@returns 
	 */
	virtual Tango::DevString get_parameter(Tango::DevString argin);
	virtual bool is_GetParameter_allowed(const CORBA::Any &any);
	/**
	 *	Command SetParameter related method
	 *	Description: Set the value of a specific parameter. 
	 *               The parameter is identified by its GROUP and name.
	 *               
	 *               Input argument has to be in the following format:
	 *               GROUP_OF_PROPERTY:parameter_name, value
	 *
	 *	@param argin 
	 */
	virtual void set_parameter(const Tango::DevVarDoubleStringArray *argin);
	virtual bool is_SetParameter_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : Dhyana::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(Dhyana::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
// return true if the device is correctly initialized in init_device
	bool is_device_initialized();

	void build_view(std::string model);

	void write_attr_at_init();

	lima::Dhyana::Camera* get_camera();

protected :	
	//	Add your own data members here
	//-----------------------------------------
    //state & status stuff
    bool                      m_is_device_initialized ;
    stringstream              m_status_message;
    std::string               m_global_gain;
    
    //lima OBJECTS
    lima::Dhyana::Interface*  m_hw;
    lima::CtControl*          m_ct;
    lima::Dhyana::Camera*     m_camera;
	double 					  m_delay_ch1;
	double 					  m_delay_ch2;
	double 					  m_delay_ch3;
	double 					  m_width_ch1;
	double 					  m_width_ch2;
	double 					  m_width_ch3;
	short 					  m_edge_ch1;
	short 					  m_edge_ch2;
	short 					  m_edge_ch3;
	lima::Dhyana::Camera::TucamSignal m_signal1;
	lima::Dhyana::Camera::TucamSignal m_signal2;
	lima::Dhyana::Camera::TucamSignal m_signal3;
/*----- PROTECTED REGION END -----*/	//	Dhyana::Additional Method prototypes
};

/*----- PROTECTED REGION ID(Dhyana::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	Dhyana::Additional Classes Definitions

}	//	End of namespace

#endif   //	Dhyana_H
