//=============================================================================
//
// file :        Ufxc.h
//
// description : Include for the Ufxc class.
//
// project :	Device specific for Ufxc detector
//
// $Author:  $
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
//		 BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _UFXC_H
#define _UFXC_H

#include <tango.h>
//using namespace Tango;

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

 //	Add your own constant definitions here.
 //-----------------------------------------------

#include "Factory.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"

#include <yat/memory/SharedPtr.h>
#include <yat/utils/StringTokenizer.h>

#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>
#include <yat4tango/DeviceTask.h>

#include "UfxcInterface.h"
#include "UfxcCamera.h"

#include "MyTask.h"

#define MAX_ATTRIBUTE_STRING_LENGTH     256


using namespace lima;
using namespace std;
using namespace yat4tango;

namespace Ufxc_ns
{
    
/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::FAULT :
*  Tango::INIT :
*  Tango::RUNNING :
*  Tango::STANDBY :
 */


class Ufxc: public TANGO_BASE_CLASS
{
public :
	//	Add your own data members here
	//-----------------------------------------


	//	Here is the Start of the automatic code generation part
	//-------------------------------------------------------------	
/**
 *	@name attributes
 *	Attribute member data.
 */
//@{
		Tango::DevString	*attr_libVersion_read;
		Tango::DevString	*attr_firmwareVersion_read;
		Tango::DevString	*attr_currentAlias_read;
		Tango::DevString	*attr_currentConfigFile_read;
		Tango::DevULong	*attr_detectorTemperature_read;
		Tango::DevFloat	*attr_thresholdLow_read;
		Tango::DevFloat	attr_thresholdLow_write;
		Tango::DevFloat	*attr_thresholdHigh_read;
		Tango::DevFloat	attr_thresholdHigh_write;
		Tango::DevULong	*attr_thresholdLow1_read;
		Tango::DevULong	*attr_thresholdHigh1_read;
		Tango::DevULong	*attr_thresholdLow2_read;
		Tango::DevULong	*attr_thresholdHigh2_read;
		Tango::DevFloat	*attr_triggerAcquisitionFrequency_read;
		Tango::DevFloat	attr_triggerAcquisitionFrequency_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	Allow to Reload the last used Detector Configuration file at each init of the device.
 */
	Tango::DevBoolean	autoLoad;
/**
 *	Define the list of Detector Configuration files and their associated alias.
 */
	vector<string>	detectorConfigFiles;
/**
 *	Config Ip Address
 */
	string	configIpAddress;
/**
 *	Config Port
 */
	Tango::DevULong	configPort;
/**
 *	SFP1 Ip Address
 */
	string	sFP1IpAddress;
/**
 *	SFP1 Port
 */
	Tango::DevULong	sFP1Port;
/**
 *	SFP2 Ip Address
 */
	string	sFP2IpAddress;
/**
 *	SFP2 Port
 */
	Tango::DevULong	sFP2Port;
/**
 *	SFP3 Ip Address
 */
	string	sFP3IpAddress;
/**
 *	SFP3 Port
 */
	Tango::DevULong	sFP3Port;
/**
 *	Timeout in ms
 */
	Tango::DevULong	timeout;
/**
 *	Enable/Disable the geometrical corrections
 */
	Tango::DevBoolean	geometricalCorrectionEnabled;
/**
 *	Enable/Disable the sum of the frames stack
 */
	Tango::DevBoolean	stackFramesSumEnabled;
/**
 *	Only the device could modify this property <br>
 *	The User should never change this property<br>
 */
	Tango::DevFloat	memorizedThresholdLow;
/**
 *	Only the device could modify this property <br>
 *	The User should never change this property<br>
 */
	Tango::DevFloat	memorizedThresholdHigh;
/**
 *	Only the device could modify this property <br>
 *	The User should never change this property<br>
 */
	string	memorizedConfigAlias;
/**
 *	Only the device could modify this property <br>
 *	The User should never change this property<br>
 */
	Tango::DevFloat	memorizedTriggerAcquisitionFrequency;
//@}

/**
 *	@name Device properties
 *	Device property member data.
 */
//@{
//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Ufxc(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Ufxc(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	Ufxc(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~Ufxc() {delete_device();};
/**
 *	will be called at device destruction or at init command.
 */
	void delete_device();
//@}

	
/**@name Miscellaneous methods */
//@{
/**
 *	Initialize the device
 */
	virtual void init_device();
/**
 *	Always executed method before execution command method.
 */
	virtual void always_executed_hook();

//@}

/**
 * @name Ufxc methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for libVersion acquisition result.
 */
	virtual void read_libVersion(Tango::Attribute &attr);
/**
 *	Extract real attribute values for firmwareVersion acquisition result.
 */
	virtual void read_firmwareVersion(Tango::Attribute &attr);
/**
 *	Extract real attribute values for currentAlias acquisition result.
 */
	virtual void read_currentAlias(Tango::Attribute &attr);
/**
 *	Extract real attribute values for currentConfigFile acquisition result.
 */
	virtual void read_currentConfigFile(Tango::Attribute &attr);
/**
 *	Extract real attribute values for detectorTemperature acquisition result.
 */
	virtual void read_detectorTemperature(Tango::Attribute &attr);
/**
 *	Extract real attribute values for thresholdLow acquisition result.
 */
	virtual void read_thresholdLow(Tango::Attribute &attr);
/**
 *	Write thresholdLow attribute values to hardware.
 */
	virtual void write_thresholdLow(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for thresholdHigh acquisition result.
 */
	virtual void read_thresholdHigh(Tango::Attribute &attr);
/**
 *	Write thresholdHigh attribute values to hardware.
 */
	virtual void write_thresholdHigh(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for thresholdLow1 acquisition result.
 */
	virtual void read_thresholdLow1(Tango::Attribute &attr);
/**
 *	Extract real attribute values for thresholdHigh1 acquisition result.
 */
	virtual void read_thresholdHigh1(Tango::Attribute &attr);
/**
 *	Extract real attribute values for thresholdLow2 acquisition result.
 */
	virtual void read_thresholdLow2(Tango::Attribute &attr);
/**
 *	Extract real attribute values for thresholdHigh2 acquisition result.
 */
	virtual void read_thresholdHigh2(Tango::Attribute &attr);
/**
 *	Extract real attribute values for triggerAcquisitionFrequency acquisition result.
 */
	virtual void read_triggerAcquisitionFrequency(Tango::Attribute &attr);
/**
 *	Write triggerAcquisitionFrequency attribute values to hardware.
 */
	virtual void write_triggerAcquisitionFrequency(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for libVersion attribute.
 */
	virtual bool is_libVersion_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for firmwareVersion attribute.
 */
	virtual bool is_firmwareVersion_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for currentAlias attribute.
 */
	virtual bool is_currentAlias_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for currentConfigFile attribute.
 */
	virtual bool is_currentConfigFile_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for detectorTemperature attribute.
 */
	virtual bool is_detectorTemperature_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdLow attribute.
 */
	virtual bool is_thresholdLow_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdHigh attribute.
 */
	virtual bool is_thresholdHigh_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdLow1 attribute.
 */
	virtual bool is_thresholdLow1_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdHigh1 attribute.
 */
	virtual bool is_thresholdHigh1_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdLow2 attribute.
 */
	virtual bool is_thresholdLow2_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for thresholdHigh2 attribute.
 */
	virtual bool is_thresholdHigh2_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for triggerAcquisitionFrequency attribute.
 */
	virtual bool is_triggerAcquisitionFrequency_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for LoadConfigFile command.
 */
	virtual bool is_LoadConfigFile_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * 
 *	@param	argin	alias of the Detector configuration file
 *	@exception DevFailed
 */
	void	load_config_file(Tango::DevString);

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	

	// return true if the device is correctly initialized in init_device
	bool is_device_initialized(){return m_is_device_initialized;};

protected :	
	//	Add your own data members here
	//-----------------------------------------
    //Create Yat::task to manage device LoadConfigFile command
    bool                       create_acquisition_task(void);        
    //state & status stuff
    bool                      m_is_device_initialized ;
    stringstream              m_status_message;
    //- yat4tango::DeviceTask object : manage device LoadConfigFile command
    yat::SharedPtr<MyTask>     m_my_task;
    
    //lima OBJECTS
    lima::Ufxc::Interface*      m_hw;
    lima::CtControl*            m_ct;
    lima::Ufxc::Camera*         m_camera;	    
	std::map<std::string, std::string>  m_map_alias_config_files;
};

}	// namespace_ns

#endif	// _UFXC_H