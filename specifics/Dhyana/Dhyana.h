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


#include "Factory.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"

#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>

#include "DhyanaInterface.h"
#include "DhyanaCamera.h"

#define MAX_ATTRIBUTE_STRING_LENGTH     256
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
enum _channel1Enum :short {
} ;
typedef _channel1Enum channel1Enum;

enum _channel2Enum :short {
} ;
typedef _channel2Enum channel2Enum;

enum _channel3Enum :short {
} ;
typedef _channel3Enum channel3Enum;

enum _edge1Enum : short {
} ;
typedef _edge1Enum edge1Enum;

enum _edge2Enum :short {
} ;
typedef _edge2Enum edge2Enum;

enum _edge3Enum :short {
} ;
typedef _edge3Enum edge3Enum;

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
	Tango::DevString	attr_globalGain_write;
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
	edge3Enum	attr_edge3_write;
/*----- PROTECTED REGION END -----*/	//	Dhyana::Data Members

//	Device property data members
public:
	//	TemperatureTargetAtInit:	Memorize/Define the temperatureTarget  attribute  at Init device<br>
	Tango::DevDouble	temperatureTargetAtInit;
	//	MemorizedFanSpeed:	Memorize/Define the fanSpeed  attribute  at Init device<br>
	Tango::DevUShort	memorizedFanSpeed;
	//	MemorizedGlobalGain:	Memorize/Define the globalGain  attribute  at Init device<br>
	string	memorizedGlobalGain;
	//	__ExpertTimerPeriod:	Timer period in ms.<cr>
	//  useful only for Internal Trigger
	Tango::DevUShort	__ExpertTimerPeriod;

//	Attribute data members
public:
	Tango::DevString	*attr_tucamVersion_read;
	Tango::DevDouble	*attr_temperature_read;
	Tango::DevDouble	*attr_temperatureTarget_read;
	Tango::DevUShort	*attr_fanSpeed_read;
	Tango::DevString	*attr_globalGain_read;
	Tango::DevDouble	*attr_fps_read;
	channel1Enum	*attr_channel1_read;
	channel2Enum	*attr_channel2_read;
	channel3Enum	*attr_channel3_read;
	Tango::DevDouble	*attr_width1_read;
	Tango::DevDouble	*attr_width2_read;
	Tango::DevDouble	*attr_width3_read;
	Tango::DevDouble	*attr_delay1_read;
	Tango::DevDouble	*attr_delay2_read;
	Tango::DevDouble	*attr_delay3_read;
	edge1Enum	*attr_edge1_read;
	edge2Enum	*attr_edge2_read;
	edge3Enum	*attr_edge3_read;

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
	/*
	 *	Method      : Dhyana::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute tucamVersion related methods
 *	Description: Dhyana Tucam Version.
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_tucamVersion(Tango::Attribute &attr);
	virtual bool is_tucamVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute temperature related methods
 *	Description: Get Temperature of the detector (in Celsius)
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_temperature(Tango::Attribute &attr);
	virtual bool is_temperature_allowed(Tango::AttReqType type);
/**
 *	Attribute temperatureTarget related methods
 *	Description: Set the Temperature target of the detector (in Celsius)
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_temperatureTarget(Tango::Attribute &attr);
	virtual void write_temperatureTarget(Tango::WAttribute &attr);
	virtual bool is_temperatureTarget_allowed(Tango::AttReqType type);
/**
 *	Attribute fanSpeed related methods
 *	Description: Define the fan speed of the detector [0..5]
 *
 *	Data type:	Tango::DevUShort
 *	Attr type:	Scalar
 */
	virtual void read_fanSpeed(Tango::Attribute &attr);
	virtual void write_fanSpeed(Tango::WAttribute &attr);
	virtual bool is_fanSpeed_allowed(Tango::AttReqType type);
/**
 *	Attribute globalGain related methods
 *	Description: Define the gain of the detector [LOW, HIGH, HDR]
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_globalGain(Tango::Attribute &attr);
	virtual void write_globalGain(Tango::WAttribute &attr);
	virtual bool is_globalGain_allowed(Tango::AttReqType type);
/**
 *	Attribute fps related methods
 *	Description: The last computed frame per second (the value is computed every 100 frames only)
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_fps(Tango::Attribute &attr);
	virtual bool is_fps_allowed(Tango::AttReqType type);
/**
 *	Attribute channel1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_channel1(Tango::Attribute &attr);
	virtual void write_channel1(Tango::WAttribute &attr);
	virtual bool is_channel1_allowed(Tango::AttReqType type);
/**
 *	Attribute channel2 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_channel2(Tango::Attribute &attr);
	virtual void write_channel2(Tango::WAttribute &attr);
	virtual bool is_channel2_allowed(Tango::AttReqType type);
/**
 *	Attribute channel3 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_channel3(Tango::Attribute &attr);
	virtual void write_channel3(Tango::WAttribute &attr);
	virtual bool is_channel3_allowed(Tango::AttReqType type);
/**
 *	Attribute width1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_width1(Tango::Attribute &attr);
	virtual void write_width1(Tango::WAttribute &attr);
	virtual bool is_width1_allowed(Tango::AttReqType type);
/**
 *	Attribute width2 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_width2(Tango::Attribute &attr);
	virtual void write_width2(Tango::WAttribute &attr);
	virtual bool is_width2_allowed(Tango::AttReqType type);
/**
 *	Attribute width3 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_width3(Tango::Attribute &attr);
	virtual void write_width3(Tango::WAttribute &attr);
	virtual bool is_width3_allowed(Tango::AttReqType type);
/**
 *	Attribute delay1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_delay1(Tango::Attribute &attr);
	virtual void write_delay1(Tango::WAttribute &attr);
	virtual bool is_delay1_allowed(Tango::AttReqType type);
/**
 *	Attribute delay2 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_delay2(Tango::Attribute &attr);
	virtual void write_delay2(Tango::WAttribute &attr);
	virtual bool is_delay2_allowed(Tango::AttReqType type);
/**
 *	Attribute delay3 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_delay3(Tango::Attribute &attr);
	virtual void write_delay3(Tango::WAttribute &attr);
	virtual bool is_delay3_allowed(Tango::AttReqType type);
/**
 *	Attribute edge1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_edge1(Tango::Attribute &attr);
	virtual void write_edge1(Tango::WAttribute &attr);
	virtual bool is_edge1_allowed(Tango::AttReqType type);
/**
 *	Attribute edge2 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_edge2(Tango::Attribute &attr);
	virtual void write_edge2(Tango::WAttribute &attr);
	virtual bool is_edge2_allowed(Tango::AttReqType type);
/**
 *	Attribute edge3 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_edge3(Tango::Attribute &attr);
	virtual void write_edge3(Tango::WAttribute &attr);
	virtual bool is_edge3_allowed(Tango::AttReqType type);


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
	bool is_device_initialized(){return m_is_device_initialized;};

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
