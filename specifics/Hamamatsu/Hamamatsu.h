//=============================================================================
//
// file :        Hamamatsu.h
//
// description : Include for the Hamamatsu class.
//
// project :	
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
#ifndef _HAMAMATSU_H
#define _HAMAMATSU_H

#include <tango.h>

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>
#include <yat4tango/DynamicInterfaceManager.h>

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
#include "HamamatsuInterface.h"
#include "HamamatsuCamera.h"

//using namespace lima::Hamamatsu;
using namespace lima;
using namespace yat4tango;

namespace Hamamatsu_ns
{

/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class Hamamatsu: public Tango::Device_4Impl
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
		Tango::DevLong	*attr_lostFrames_read;
		Tango::DevDouble	*attr_fps_read;
		Tango::DevBoolean	*attr_wViewEnabled_read;
		Tango::DevBoolean	attr_wViewEnabled_write;
		Tango::DevDouble	*attr_topViewExposureTime_read;
		Tango::DevDouble	attr_topViewExposureTime_write;
		Tango::DevDouble	*attr_bottomViewExposureTime_read;
		Tango::DevDouble	attr_bottomViewExposureTime_write;
		Tango::DevUShort	*attr_channel1Polarity_read;
		Tango::DevUShort	attr_channel1Polarity_write;
		Tango::DevUShort	*attr_channel2Polarity_read;
		Tango::DevUShort	attr_channel2Polarity_write;
		Tango::DevUShort	*attr_channel3Polarity_read;
		Tango::DevUShort	attr_channel3Polarity_write;
		Tango::DevUShort	*attr_channel1Kind_read;
		Tango::DevUShort	attr_channel1Kind_write;
		Tango::DevUShort	*attr_channel2Kind_read;
		Tango::DevUShort	attr_channel2Kind_write;
		Tango::DevUShort	*attr_channel3Kind_read;
		Tango::DevUShort	attr_channel3Kind_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	id of the camera
 */
	Tango::DevLong	detectorNum;
/**
 *	Memorize/Define the readoutSpeed attribute at Init device<br>
 *	Availables values :<br>
 *	NORMAL<br>
 *	SLOW<br>
 */
	string	memorizedReadoutSpeed;
/**
 *	Allows you to select the blank of synreadout:<BR>
 *	Availables values :<br>
 *	- STANDARD<BR>
 *	- MINIMUM<BR>
 *	
 */
	string	blankOfSyncreadoutTrigger;
/**
 *	Memorize/Define the Top View exposure time attribute at Init device<br>
 */
	Tango::DevDouble	memorizedTopViewExposureTime;
/**
 *	Memorize/Define the Bottom View exposure time attribute at Init device<br>
 */
	Tango::DevDouble	memorizedBottomViewExposureTime;
/**
 *	Memorize/Define the W-VIEW mode attribute at Init device<br>
 */
	Tango::DevBoolean	memorizedWViewEnabled;
/**
 *	Memorize/Define the HighDynamicRangeEnabled attribute at Init device<br>
 */
	Tango::DevBoolean	memorizedHighDynamicRangeEnabled;
/**
 *	Only an expert User could change this property.<br>
 *	This is the DCAM frame buffer size used during the acquisition.<BR>
 */
	Tango::DevLong	expertFrameBufferSize;
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
	Hamamatsu(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	Hamamatsu(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	Hamamatsu(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~Hamamatsu() {delete_device();};
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
 * @name Hamamatsu methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for lostFrames acquisition result.
 */
	virtual void read_lostFrames(Tango::Attribute &attr);
/**
 *	Extract real attribute values for fps acquisition result.
 */
	virtual void read_fps(Tango::Attribute &attr);
/**
 *	Extract real attribute values for wViewEnabled acquisition result.
 */
	virtual void read_wViewEnabled(Tango::Attribute &attr);
/**
 *	Write wViewEnabled attribute values to hardware.
 */
	virtual void write_wViewEnabled(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for topViewExposureTime acquisition result.
 */
	virtual void read_topViewExposureTime(Tango::Attribute &attr);
/**
 *	Write topViewExposureTime attribute values to hardware.
 */
	virtual void write_topViewExposureTime(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for bottomViewExposureTime acquisition result.
 */
	virtual void read_bottomViewExposureTime(Tango::Attribute &attr);
/**
 *	Write bottomViewExposureTime attribute values to hardware.
 */
	virtual void write_bottomViewExposureTime(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel1Polarity acquisition result.
 */
	virtual void read_channel1Polarity(Tango::Attribute &attr);
/**
 *	Write channel1Polarity attribute values to hardware.
 */
	virtual void write_channel1Polarity(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel2Polarity acquisition result.
 */
	virtual void read_channel2Polarity(Tango::Attribute &attr);
/**
 *	Write channel2Polarity attribute values to hardware.
 */
	virtual void write_channel2Polarity(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel3Polarity acquisition result.
 */
	virtual void read_channel3Polarity(Tango::Attribute &attr);
/**
 *	Write channel3Polarity attribute values to hardware.
 */
	virtual void write_channel3Polarity(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel1Kind acquisition result.
 */
	virtual void read_channel1Kind(Tango::Attribute &attr);
/**
 *	Write channel1Kind attribute values to hardware.
 */
	virtual void write_channel1Kind(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel2Kind acquisition result.
 */
	virtual void read_channel2Kind(Tango::Attribute &attr);
/**
 *	Write channel2Kind attribute values to hardware.
 */
	virtual void write_channel2Kind(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for channel3Kind acquisition result.
 */
	virtual void read_channel3Kind(Tango::Attribute &attr);
/**
 *	Write channel3Kind attribute values to hardware.
 */
	virtual void write_channel3Kind(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for lostFrames attribute.
 */
	virtual bool is_lostFrames_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for fps attribute.
 */
	virtual bool is_fps_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for wViewEnabled attribute.
 */
	virtual bool is_wViewEnabled_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for topViewExposureTime attribute.
 */
	virtual bool is_topViewExposureTime_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for bottomViewExposureTime attribute.
 */
	virtual bool is_bottomViewExposureTime_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel1Polarity attribute.
 */
	virtual bool is_channel1Polarity_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel2Polarity attribute.
 */
	virtual bool is_channel2Polarity_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel3Polarity attribute.
 */
	virtual bool is_channel3Polarity_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel1Kind attribute.
 */
	virtual bool is_channel1Kind_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel2Kind attribute.
 */
	virtual bool is_channel2Kind_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for channel3Kind attribute.
 */
	virtual bool is_channel3Kind_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for GetAllParameters command.
 */
	virtual bool is_GetAllParameters_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for GetParameter command.
 */
	virtual bool is_GetParameter_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SetParameter command.
 */
	virtual bool is_SetParameter_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * Return the list of all the camera parameters in the following format:
 *	ID = idNb; ParameterName = value
 *	@return	
 *	@exception DevFailed
 */
	Tango::DevString	get_all_parameters();
/**
 * Return the name and value of a specific ID
 *	@param	argin	ID of the parameter
 *	@return	
 *	@exception DevFailed
 */
	Tango::DevString	get_parameter(Tango::DevULong);
/**
 * Set the value of a parameter using it's ID
 *	@param	argin	First argument is the ID, Second is the value
 *	@exception DevFailed
 */
	void	set_parameter(const Tango::DevVarDoubleArray *);

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	



private :
/**
 *	method:	Hamamatsu::manage_devfailed_exception
 *
 *	description: method which manages DevFailed exceptions
 */
    void manage_devfailed_exception(Tango::DevFailed & in_exception, const std::string & in_caller_method_name);

/**
 *	method:	Hamamatsu::manage_lima_exception
 *
 *	description: method which manages lima exceptions
 */
    void manage_lima_exception(lima::Exception & in_exception, const std::string & in_caller_method_name);

/**
 *	method:	Hamamatsu::create_dynamics_attributes
 *
 *	description: Create all dynamics attributes.
 */
    void create_dynamics_attributes(void);

/**
 *	method:	Hamamatsu::release_dynamics_attributes
 *
 *	description: Release all dynamics attributes.
 */
    void release_dynamics_attributes(void);

/**
 *	method:	Hamamatsu::write_at_init
 *
 *	description: Update the hardware with the properties data.
 */
    void write_at_init(void);

/**
 *	method:	Hamamatsu::create_attribute
 *
 *	description: Create a dynamic attribute
 */
	template <class F1, class F2>
    void create_dynamic_attribute(const std::string &   name                ,
                                  int                   data_type           ,
                                  Tango::AttrDataFormat data_format         ,
                                  Tango::AttrWriteType  access_type         ,
                                  Tango::DispLevel      disp_level          ,
                                  size_t                polling_period_in_ms,
                                  const std::string &   unit                ,
                                  const std::string &   format              ,
                                  const std::string &   desc                ,
                                  F1                    read_callback       ,
                                  F2                    write_callback      ,
                                  yat::Any              user_data           );

/**
 *	method:	Hamamatsu::read_dynamic_attribute
 *
 *	description: Fill a dynamic attribute with a information from the plugin
 */
    template< typename T1, typename T2>
    void read_dynamic_attribute(yat4tango::DynamicAttributeReadCallbackData& out_cbd,
                                T2 (lima::Hamamatsu::Camera::*in_method)(void),
                                const std::string & in_caller_name,
                                const bool in_is_enabled_during_running = false);

/**
 *	method:	Hamamatsu::read_dynamic_string_attribute
 *
 *	description: Fill the read dynamic attribute (string) with the plugin informations
 */
    template< typename T1, typename T2>
    void read_dynamic_string_attribute(yat4tango::DynamicAttributeReadCallbackData& out_cbd,
                                       T2 (lima::Hamamatsu::Camera::*in_method)(void),
                                       const std::string & in_caller_name,
                                       const bool in_is_enabled_during_running = false);

/**
 *	method:	Hamamatsu::write_dynamic_attribute
 *
 *	description: Use the write dynamic attribut to set informations in the plugin
 */
    template< typename T1, typename T2>
    void write_dynamic_attribute(yat4tango::DynamicAttributeWriteCallbackData & in_cbd,
                                 void (lima::Hamamatsu::Camera::*in_method)(const T2 &),
                                 const char * in_optional_memorized_property,
                                 const std::string & in_caller_name);

/**
 *	method:	Hamamatsu::write_dynamic_string_attribute
 *
 *	description: Use the write dynamic attribut (string) to set informations in the plugin
 */
    template< typename T1, typename T2>
    void write_dynamic_string_attribute(yat4tango::DynamicAttributeWriteCallbackData & in_cbd,
                                        void (lima::Hamamatsu::Camera::*in_method)(const T2 &),
                                        const char * in_optional_memorized_property,
                                        const std::string & in_caller_name);

/**
 *	method:	Hamamatsu::write_property_in_dynamic_attribute
 *
 *	description: Use to update a dynamic attribute and the hardware with a property value
 */
    template< typename T1>
    void write_property_in_dynamic_attribute(const std::string & in_attribute_name,
                                             const std::string & in_property_name ,
                                             void (Hamamatsu_ns::Hamamatsu::*in_write_method)(yat4tango::DynamicAttributeWriteCallbackData &));

/**
 *	method:	Hamamatsu::write_property_in_dynamic_string_attribute
 *
 *	description: Use to update a dynamic attribute (string) and the hardware with a property value
 */
    template< typename T1>
    void write_property_in_dynamic_string_attribute(const std::string & in_attribute_name,
                                                    const std::string & in_property_name ,
                                                    void (Hamamatsu_ns::Hamamatsu::*in_write_method)(yat4tango::DynamicAttributeWriteCallbackData &));


/**
 *	method:	Hamamatsu::read_temperature_callback
 *
 *	description: read temperature callback
 */
    void read_temperature_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::read_temperatureStatus_callback
 *
 *	description: read temperature status callback
 */
    void read_temperatureStatus_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::read_coolerMode_callback
 *
 *	description: read cooler mode callback
 */
    void read_coolerMode_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::read_coolerMode_callback
 *
 *	description: read cooler mode callback
 */
    void read_coolerStatus_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::read_highDynamicRangeEnabled_callback
 *
 *	description: read high dynamic range enabled callback
 */
    void read_highDynamicRangeEnabled_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::write_highDynamicRangeEnabled_callback
 *
 *	description: write high dynamic range enabled callback
 */
    void write_highDynamicRangeEnabled_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

/**
 *	method:	Hamamatsu::read_readoutSpeed_callback
 *
 *	description: Extract real attribute values for readoutSpeed.
 */
    void read_readoutSpeed_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);

/**
 *	method:	Hamamatsu::write_readoutSpeed_callback
 *
 *	description: Set real attribute values for readoutSpeed.
 */
    void write_readoutSpeed_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

    // method for tango dyn attributes WHEN no write part is available - NULL
    void write_callback_null(yat4tango::DynamicAttributeWriteCallbackData& cbd){/*nop*/}

    

protected :	
	//	Add your own data members here
	//-----------------------------------------
	bool                                                m_is_device_initialized    ;
    stringstream                                        m_status_message           ;
    enum lima::Hamamatsu::Camera::SyncReadOut_BlankMode m_sync_readout_blank_mode  ;
	double                                              m_top_view_exposure_time   ;
	double                                              m_bottom_view_exposure_time;
	bool                                                m_wView_enabled            ;
	

    /// yat4tango Dynamic Interface Manager
    yat4tango::DynamicInterfaceManager m_dim;

    /// read attributes for dynamic attributes
    Tango::DevDouble  *attr_dyn_temperature_read  ;
    Tango::DevString  *attr_dyn_coolerMode_read  ;
    Tango::DevString  *attr_dyn_coolerStatus_read;
    Tango::DevString  *attr_dyn_temperatureStatus_read;
    Tango::DevBoolean *attr_dyn_highDynamicRangeEnabled_read;
    Tango::DevString  *attr_dyn_readoutSpeed_read;

    /// lima OBJECTS
    lima::Hamamatsu::Interface * m_hw    ;
    CtControl                  * m_ct    ;
    lima::Hamamatsu::Camera    * m_camera;
};

}	// namespace_ns

//	Additional Classes Definitions for templates
#include "Hamamatsu.hpp"

#endif	// _HAMAMATSU_H
