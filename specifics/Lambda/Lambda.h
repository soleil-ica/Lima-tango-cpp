/*----- PROTECTED REGION ID(Lambda.h) ENABLED START -----*/
//=============================================================================
//
// file :        Lambda.h
//
// description : Include file for the Lambda class
//
// project :     XSpectrum Lambda detector TANGO specific device.
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


#ifndef Lambda_H
#define Lambda_H

#include <tango.h>

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/DynamicInterfaceManager.h>
#include <yat4tango/InnerAppender.h>

#include "Factory.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"

#include "LambdaInclude.h"
#include "LambdaCamera.h"

/*----- PROTECTED REGION END -----*/	//	Lambda.h

/**
 *  Lambda class description:
 *    Device for Lambda detectors from XSpectrum.
 */

namespace Lambda_ns
{
enum _hwAcquisitionModeEnum {
	_24_BITS,
	_12_BITS,
	_6_BITS,
	_1_BIT,
} ;
typedef _hwAcquisitionModeEnum hwAcquisitionModeEnum;

/*----- PROTECTED REGION ID(Lambda::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	Lambda::Additional Class Declarations

class Lambda : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(Lambda::Data Members) ENABLED START -----*/

//	Add your own data members

/*----- PROTECTED REGION END -----*/	//	Lambda::Data Members

//	Device property data members
public:
	//	ConfigFile:	Configuration file used to initialize the detector.
	string	configFile;
	//	DistortionCorrection:	set distortion correction.<br>
	//  When distortion correction is enabled :<br>
	//  - Large pixels are divided according to predefined denominator. <br>
	//  - The values of the pixels are rounded during division. <br>
	//  - If pixel value is saturated, the division is not applied.<br>
	Tango::DevBoolean	distortionCorrection;
	//	ChargeSumming:	Indicates wether charge summing is used or not.
	Tango::DevBoolean	chargeSumming;

//	Attribute data members
public:
	Tango::DevString	*attr_configFile_read;
	Tango::DevBoolean	*attr_distortionCorrection_read;
	Tango::DevString	*attr_libraryVersion_read;
	Tango::DevDouble	*attr_highVoltage_read;
	Tango::DevDouble	*attr_humidity_read;
	Tango::DevDouble	*attr_temperature_read;
	Tango::DevBoolean	*attr_linearityCorrection_read;
	Tango::DevBoolean	*attr_saturationFlag_read;
	Tango::DevLong	*attr_saturationThreshold_read;
	Tango::DevBoolean	*attr_chargeSumming_read;
	Tango::DevDouble	*attr_lowerThreshold_read;
	Tango::DevDouble	*attr_upperThreshold_read;
	hwAcquisitionModeEnum	*attr_hwAcquisitionMode_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Lambda(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Lambda(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	Lambda(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~Lambda() {delete_device();};


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
	 *	Method      : Lambda::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : Lambda::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute configFile related methods
 *	Description: Configuration file used to initialize the detector
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_configFile(Tango::Attribute &attr);
	virtual bool is_configFile_allowed(Tango::AttReqType type);
/**
 *	Attribute distortionCorrection related methods
 *	Description: distortion correction.<br>
 *               When distortion correction is enabled :<br>
 *               - Large pixels are divided according to predefined denominator. <br>
 *               - The values of the pixels are rounded during division. <br>
 *               - If pixel value is saturated, the division is not applied.<br>
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_distortionCorrection(Tango::Attribute &attr);
	virtual bool is_distortionCorrection_allowed(Tango::AttReqType type);
/**
 *	Attribute libraryVersion related methods
 *	Description: Version of the xsp library
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_libraryVersion(Tango::Attribute &attr);
	virtual bool is_libraryVersion_allowed(Tango::AttReqType type);
/**
 *	Attribute highVoltage related methods
 *	Description: Value in V of the high Voltage
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_highVoltage(Tango::Attribute &attr);
	virtual bool is_highVoltage_allowed(Tango::AttReqType type);
/**
 *	Attribute humidity related methods
 *	Description: measured humidity in %
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_humidity(Tango::Attribute &attr);
	virtual bool is_humidity_allowed(Tango::AttReqType type);
/**
 *	Attribute temperature related methods
 *	Description: measured temperature in deg C
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_temperature(Tango::Attribute &attr);
	virtual bool is_temperature_allowed(Tango::AttReqType type);
/**
 *	Attribute linearityCorrection related methods
 *	Description: Enable/Disable countrate correction.
 *               linearityCorrection is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_linearityCorrection(Tango::Attribute &attr);
	virtual void write_linearityCorrection(Tango::WAttribute &attr);
	virtual bool is_linearityCorrection_allowed(Tango::AttReqType type);
/**
 *	Attribute saturationFlag related methods
 *	Description: Enable/Disable flagging of pixel saturation.
 *               saturationFlag is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_saturationFlag(Tango::Attribute &attr);
	virtual void write_saturationFlag(Tango::WAttribute &attr);
	virtual bool is_saturationFlag_allowed(Tango::AttReqType type);
/**
 *	Attribute saturationThreshold related methods
 *	Description: Saturation threshold in counts per second per pixel.<br>
 *               saturationThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_saturationThreshold(Tango::Attribute &attr);
	virtual void write_saturationThreshold(Tango::WAttribute &attr);
	virtual bool is_saturationThreshold_allowed(Tango::AttReqType type);
/**
 *	Attribute chargeSumming related methods
 *	Description: charge summing mode.
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
	virtual void read_chargeSumming(Tango::Attribute &attr);
	virtual bool is_chargeSumming_allowed(Tango::AttReqType type);
/**
 *	Attribute lowerThreshold related methods
 *	Description: lower threshold in KeV.<br>
 *               The photon is counted If the energy is above this threshold.<br>
 *               lowerThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_lowerThreshold(Tango::Attribute &attr);
	virtual void write_lowerThreshold(Tango::WAttribute &attr);
	virtual bool is_lowerThreshold_allowed(Tango::AttReqType type);
/**
 *	Attribute upperThreshold related methods
 *	Description: upper threshold in KeV.<br>
 *               The photon is counted If the energy is under this threshold.<br>
 *               upperThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_upperThreshold(Tango::Attribute &attr);
	virtual void write_upperThreshold(Tango::WAttribute &attr);
	virtual bool is_upperThreshold_allowed(Tango::AttReqType type);
/**
 *	Attribute hwAcquisitionMode related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEnum
 *	Attr type:	Scalar
 */
	virtual void read_hwAcquisitionMode(Tango::Attribute &attr);
	virtual void write_hwAcquisitionMode(Tango::WAttribute &attr);
	virtual bool is_hwAcquisitionMode_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : Lambda::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:


	//--------------------------------------------------------
	/**
	 *	Method      : Lambda::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(Lambda::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
private:
	//-------------------------------------------------------------	
    /// Create the static attributes
    void create_static_attributes(void);

    /// Release the static attributes
    void release_static_attributes(void);

    //-------------------------------------------------------------	
    /// Update the hardware with the properties data
    void write_at_init(void);

    //-------------------------------------------------------------	
    /// Force the precompressEnabled option
    void force_precompressEnabled(bool value);

    //-------------------------------------------------------------	
    /**
     * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
     *	@return	State Code
     *	@exception DevFailed
     */
	Tango::DevState	dev_state();

    /**
     *	method:	SlsJungfrau::manage_devfailed_exception
     *
     *	description: method which manages DevFailed exceptions
     */
    void manage_devfailed_exception(Tango::DevFailed & in_exception, const std::string & in_caller_method_name);

    /**
     *	method:	SlsJungfrau::manage_lima_exception
     *
     *	description: method which manages lima exceptions
     */
    void manage_lima_exception(lima::Exception & in_exception, const std::string & in_caller_method_name);

	//-------------------------------------------------------------	
    /// Return true if the device is correctly initialized in init_device
	bool is_device_initialized();

protected :	
    //- lima stuff
    lima::Lambda::Interface* 	m_hw;
    lima::CtControl*			m_ct;
    lima::Lambda::Camera* 		m_camera;
	//- Tango device stuff
	bool                      	m_is_device_initialized;
    std::stringstream         	m_status_message;
	//- Lambda stuff
	std::string					m_library_version;
	std::string					m_config_file;
	bool						m_has_hv_feature;

/*----- PROTECTED REGION END -----*/	//	Lambda::Additional Method prototypes
};

/*----- PROTECTED REGION ID(Lambda::Additional Classes Definitions) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	Lambda::Additional Classes Definitions

}	//	End of namespace

#endif   //	Lambda_H
