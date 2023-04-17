/*----- PROTECTED REGION ID(Lambda.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        Lambda.cpp
//
// description : C++ source for the Lambda class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Lambda are implemented in this file.
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


#include <Lambda.h>
#include <LambdaClass.h>
#include <PogoHelper.h>

namespace Lambda_ns
{
	//-------------------------------------------------------------------------
	// MAX SIZES FOR STRING ATTRIBUTES
	//-------------------------------------------------------------------------
	static const size_t STR_ATTR_SIZE_MAX = 255; // size max
}

/*----- PROTECTED REGION END -----*/	//	Lambda.cpp

/**
 *  Lambda class description:
 *    Device for Lambda detectors from XSpectrum.
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  configFile            |  Tango::DevString	Scalar
//  distortionCorrection  |  Tango::DevBoolean	Scalar
//  energyThreshold       |  Tango::DevDouble	Scalar
//  libraryVersion        |  Tango::DevString	Scalar
//  highVoltage           |  Tango::DevDouble	Scalar
//  humidity              |  Tango::DevDouble	Scalar
//  temperature           |  Tango::DevDouble	Scalar
//  linearityCorrection   |  Tango::DevBoolean	Scalar
//  saturationFlag        |  Tango::DevBoolean	Scalar
//  saturationThreshold   |  Tango::DevLong	Scalar
//================================================================

namespace Lambda_ns
{
/*----- PROTECTED REGION ID(Lambda::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	Lambda::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : Lambda::Lambda()
 *	Description : Constructors for a Tango device
 *                implementing the classLambda
 */
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(Lambda::constructor_1) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_1
}
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(Lambda::constructor_2) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_2
}
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(Lambda::constructor_3) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void Lambda::delete_device()
{
	DEBUG_STREAM << "Lambda::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::delete_device) ENABLED START -----*/
	
    //	Delete device allocated objects
    DELETE_SCALAR_ATTRIBUTE(attr_distortionCorrection_read);
    DELETE_SCALAR_ATTRIBUTE(attr_energyThreshold_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_configFile_read);
	DELETE_SCALAR_ATTRIBUTE(attr_highVoltage_read);
	DELETE_SCALAR_ATTRIBUTE(attr_humidity_read);
	DELETE_SCALAR_ATTRIBUTE(attr_temperature_read);
	DELETE_DEVSTRING_ATTRIBUTE(attr_libraryVersion_read);

	DELETE_SCALAR_ATTRIBUTE(attr_linearityCorrection_read);
	DELETE_SCALAR_ATTRIBUTE(attr_saturationFlag_read);
	DELETE_SCALAR_ATTRIBUTE(attr_saturationThreshold_read);

    m_is_device_initialized = false;

	/*----- PROTECTED REGION END -----*/	//	Lambda::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void Lambda::init_device()
{
	DEBUG_STREAM << "Lambda::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::init_device_before) ENABLED START -----*/

	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	/*----- PROTECTED REGION ID(Lambda::init_device) ENABLED START -----*/
    //	Initialize device
    CREATE_SCALAR_ATTRIBUTE(attr_distortionCorrection_read);
    CREATE_SCALAR_ATTRIBUTE(attr_energyThreshold_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_configFile_read,Lambda_ns::STR_ATTR_SIZE_MAX);
    CREATE_SCALAR_ATTRIBUTE(attr_highVoltage_read);
    CREATE_SCALAR_ATTRIBUTE(attr_humidity_read);
    CREATE_SCALAR_ATTRIBUTE(attr_temperature_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_libraryVersion_read, Lambda_ns::STR_ATTR_SIZE_MAX);
	CREATE_SCALAR_ATTRIBUTE(attr_linearityCorrection_read);
	CREATE_SCALAR_ATTRIBUTE(attr_saturationFlag_read);
	CREATE_SCALAR_ATTRIBUTE(attr_saturationThreshold_read);
    
    m_is_device_initialized = false;
	m_has_hv_feature 		= false;
    set_state(Tango::INIT);
    m_status_message.str("");

    try
	{
		//- get the main object used to pilot the lima framework		
		m_ct = ControlFactory::instance().get_control("Lambda");
		
		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Lambda::Interface*>(m_ct->hwInterface());
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
	}
	catch(Exception& e)
	{
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		ERROR_STREAM     << m_status_message.str() << endl;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		m_status_message << "Initialization Failed : Unknown Error" << endl;
		ERROR_STREAM     << m_status_message.str() << endl;
		set_state(Tango::FAULT);
		return;
	}
    //	Initialize device
	m_is_device_initialized = true;
    try
	{
		// Update the hardware with the memorized attributes data
		write_at_init();

		//- Set the distortion correction (from property)
		m_camera->setDistortionCorrection(distortionCorrection);
		//- Get the distortion correction (from hardware), only once
		m_camera->getDistortionCorrection(*attr_distortionCorrection_read);

		//- Get the lib version, only once
		m_library_version = m_camera->getLibVersion();
		strcpy(*attr_libraryVersion_read, m_library_version.c_str());
		//- Get the config file name, only once
		m_config_file = m_camera->getConfigFile();
		strcpy(*attr_configFile_read, m_config_file.c_str());
		//- Check if camera has the High Voltage feature, only once
		if (m_camera->hasFeature(xsp::lambda::Feature::FEAT_HV))
			m_has_hv_feature = true;
	}
    catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		m_status_message << "Initialization Failed : ";
		for(unsigned i = 0;i < df.errors.length();i++)
		{
			m_status_message << df.errors[i].desc << endl;
		}
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(lima::Exception& e)
	{
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		ERROR_STREAM     << m_status_message.str() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		m_status_message << "Initialization Failed : Unknown Error" << endl;
		ERROR_STREAM     << m_status_message.str() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}

	dev_state();

	/*----- PROTECTED REGION END -----*/	//	Lambda::init_device
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void Lambda::get_device_property()
{
	/*----- PROTECTED REGION ID(Lambda::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("ConfigFile"));
	dev_prop.push_back(Tango::DbDatum("DistortionCorrection"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on LambdaClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		LambdaClass	*ds_class =
			(static_cast<LambdaClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize ConfigFile from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  configFile;
		else {
			//	Try to initialize ConfigFile from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  configFile;
		}
		//	And try to extract ConfigFile value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  configFile;

		//	Try to initialize DistortionCorrection from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  distortionCorrection;
		else {
			//	Try to initialize DistortionCorrection from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  distortionCorrection;
		}
		//	And try to extract DistortionCorrection value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  distortionCorrection;

	}

	/*----- PROTECTED REGION ID(Lambda::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "/opt/xsp/config/system.yml", "ConfigFile");
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "True"  , "DistortionCorrection");
	/*----- PROTECTED REGION END -----*/	//	Lambda::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void Lambda::always_executed_hook()
{
	DEBUG_STREAM << "Lambda::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
    try
    {
		if(m_is_device_initialized)
		{
        	m_status_message.str("");
		}

        //update state
        dev_state();
    }
    catch (lima::Exception& e)
    {
		m_status_message << "always_executed_hook : " << e.getErrMsg() << endl;
        ERROR_STREAM << m_status_message.str() << endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (...)
    {
		m_status_message << "always_executed_hook : Unknown Error" << endl;
        ERROR_STREAM << m_status_message.str() << endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void Lambda::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Lambda::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : Lambda::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void Lambda::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Lambda::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::write_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute configFile related method
 *	Description: Configuration file used to initialize the detector
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_configFile(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_configFile(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_configFile) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_configFile_read);
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_configFile
}
//--------------------------------------------------------
/**
 *	Read attribute distortionCorrection related method
 *	Description: distortion correction.<br>
 *               When distortion correction is enabled :<br>
 *               - Large pixels are divided according to predefined denominator. <br>
 *               - The values of the pixels are rounded during division. <br>
 *               - If pixel value is saturated, the division is not applied.<br>
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_distortionCorrection(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_distortionCorrection(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_distortionCorrection) ENABLED START -----*/
    attr.set_value(attr_distortionCorrection_read);
    
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_distortionCorrection
}
//--------------------------------------------------------
/**
 *	Read attribute energyThreshold related method
 *	Description: energy threshold in KeV.<br>
 *               The photon is counted If the energy is above this threshold.<br>
 *               energyThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_energyThreshold(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_energyThreshold(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_energyThreshold) ENABLED START -----*/
	try
    {
		m_camera->getEnergyThreshold(*attr_energyThreshold_read);
		attr.set_value(attr_energyThreshold_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_energyThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_energyThreshold");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_energyThreshold
}
//--------------------------------------------------------
/**
 *	Write attribute energyThreshold related method
 *	Description: energy threshold in KeV.<br>
 *               The photon is counted If the energy is above this threshold.<br>
 *               energyThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::write_energyThreshold(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Lambda::write_energyThreshold(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(Lambda::write_energyThreshold) ENABLED START -----*/
	try
    {
		// set the camera value
        m_camera->setEnergyThreshold(w_val);
		//- Memorize the write value
		yat4tango::PropertyHelper::set_memorized_attribute(this, "energyThreshold", w_val);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "write_energyThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "write_energyThreshold");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_energyThreshold
}
//--------------------------------------------------------
/**
 *	Read attribute libraryVersion related method
 *	Description: Version of the xsp library
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_libraryVersion(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_libraryVersion(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_libraryVersion) ENABLED START -----*/
	attr.set_value(attr_libraryVersion_read);

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_libraryVersion
}
//--------------------------------------------------------
/**
 *	Read attribute highVoltage related method
 *	Description: Value in V of the high Voltage
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_highVoltage(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_highVoltage(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_highVoltage) ENABLED START -----*/
	try
    {
		//- High Voltage has been checked at init
		if (m_has_hv_feature)
		{
			m_camera->getHighVoltage(*attr_highVoltage_read);
    		attr.set_value(attr_highVoltage_read);
		}
		else 
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
        
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_highVoltage");
    }
    catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_highVoltage");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_highVoltage
}
//--------------------------------------------------------
/**
 *	Read attribute humidity related method
 *	Description: measured humidity in %
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_humidity(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_humidity(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_humidity) ENABLED START -----*/
	try
    {
        m_camera->getHumidity(*attr_humidity_read);

		//if the humidity returns 0.0 it means that this function is not supported by the firmware.
		if (*attr_humidity_read == 0.0)
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
		else 
		{
			attr.set_value(attr_humidity_read);
		}
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_humidity");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_humidity");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_humidity
}
//--------------------------------------------------------
/**
 *	Read attribute temperature related method
 *	Description: measured temperature in deg C
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_temperature(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_temperature) ENABLED START -----*/
	
	try
    {
        m_camera->getTemperature(*attr_temperature_read);

		// if the temperature returns 0 it means that this function is not supported by the firmware.
		if (*attr_temperature_read == 0)
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
		else
		{
    		attr.set_value(attr_temperature_read);
		}
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_temperature");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_temperature");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_temperature
}
//--------------------------------------------------------
/**
 *	Read attribute linearityCorrection related method
 *	Description: Enable/Disable countrate correction.
 *               linearityCorrection is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_linearityCorrection(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_linearityCorrection(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_linearityCorrection) ENABLED START -----*/
	//	Set the attribute value
	
	try
	{
		bool enabled = false;
        m_camera->getLinearityCorrection(enabled);
		*attr_linearityCorrection_read = enabled;
		attr.set_value(attr_linearityCorrection_read);
	}
    catch(Tango::DevFailed & df)
    {
        manage_devfailed_exception(df, "Lambda::read_linearityCorrection");
    }
    catch(Exception & e)
    {
        manage_lima_exception(e, "Lambda::read_linearityCorrection");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_linearityCorrection
}
//--------------------------------------------------------
/**
 *	Write attribute linearityCorrection related method
 *	Description: Enable/Disable countrate correction.
 *               linearityCorrection is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::write_linearityCorrection(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Lambda::write_linearityCorrection(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(Lambda::write_linearityCorrection) ENABLED START -----*/
	try
    {
        // set the camera value
        m_camera->setLinearityCorrection(static_cast<bool>(w_val));
		//- Memorize the write value
		yat4tango::PropertyHelper::set_memorized_attribute(this, "linearityCorrection", w_val);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "Lambda::write_linearityCorrection");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "Lambda::write_linearityCorrection");
    }	
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_linearityCorrection
}
//--------------------------------------------------------
/**
 *	Read attribute saturationFlag related method
 *	Description: Enable/Disable flagging of pixel saturation.
 *               saturationFlag is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_saturationFlag(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_saturationFlag(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_saturationFlag) ENABLED START -----*/
	//	Set the attribute value
	try
	{
		bool enabled = false;
        m_camera->getSaturationFlag(enabled);
		*attr_saturationFlag_read = enabled;
		attr.set_value(attr_saturationFlag_read);
	}
    catch(Tango::DevFailed & df)
    {
        manage_devfailed_exception(df, "Lambda::read_saturationFlag");
    }
    catch(Exception & e)
    {
        manage_lima_exception(e, "Lambda::read_saturationFlag");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_saturationFlag
}
//--------------------------------------------------------
/**
 *	Write attribute saturationFlag related method
 *	Description: Enable/Disable flagging of pixel saturation.
 *               saturationFlag is a memorized attribute
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::write_saturationFlag(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Lambda::write_saturationFlag(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(Lambda::write_saturationFlag) ENABLED START -----*/
	try
    {
        // set the camera value
        m_camera->setSaturationFlag(static_cast<bool>(w_val));
		//- Memorize the write value
		yat4tango::PropertyHelper::set_memorized_attribute(this, "saturationFlag", w_val);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "Lambda::write_saturationFlag");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "Lambda::write_saturationFlag");
    }	
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_saturationFlag
}
//--------------------------------------------------------
/**
 *	Read attribute saturationThreshold related method
 *	Description: Saturation threshold in counts per second per pixel.<br>
 *               saturationThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_saturationThreshold(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_saturationThreshold(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_saturationThreshold) ENABLED START -----*/
	//	Set the attribute value
	try
    {
		m_camera->getSaturationThreshold(*attr_saturationThreshold_read);
		attr.set_value(attr_saturationThreshold_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_saturationThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_saturationThreshold");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_saturationThreshold
}
//--------------------------------------------------------
/**
 *	Write attribute saturationThreshold related method
 *	Description: Saturation threshold in counts per second per pixel.<br>
 *               saturationThreshold is a memorized attribute.<br>
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::write_saturationThreshold(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Lambda::write_saturationThreshold(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevLong	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(Lambda::write_saturationThreshold) ENABLED START -----*/

	try
    {
		// set the camera value
        m_camera->setSaturationThreshold(w_val);
		//- Memorize the write value
		yat4tango::PropertyHelper::set_memorized_attribute(this, "saturationThreshold", w_val);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "write_saturationThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "write_saturationThreshold");
    }
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_saturationThreshold
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void Lambda::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(Lambda::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void Lambda::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(Lambda::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::add_dynamic_commands
}

/*----- PROTECTED REGION ID(Lambda::namespace_ending) ENABLED START -----*/

//	Additional Methods
//+------------------------------------------------------------------
/**
 *	method:	Lambda::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState Lambda::dev_state()
{
    Tango::DevState	argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "Lambda::dev_state(): entering... !" << endl;

    // Add your own code to control device here
    stringstream DeviceStatus;
    DeviceStatus << "";
    Tango::DevState DeviceState = Tango::STANDBY;

    if(!m_is_device_initialized )
    {
        DeviceState  = Tango::FAULT;
        DeviceStatus << m_status_message.str();
    }
    else
    {
        // state & status are retrieved from Factory, Factory is updated by Generic device
        DeviceState = ControlFactory::instance().get_state();
        DeviceStatus << ControlFactory::instance().get_status();
    }

    set_state (DeviceState);
    set_status(DeviceStatus.str());

    return DeviceState;
}

//+------------------------------------------------------------------
/**
 *	method:	Lambda::manage_devfailed_exception
 *
 *	description: method which manages DevFailed exceptions
 */
//+------------------------------------------------------------------
void Lambda::manage_devfailed_exception(Tango::DevFailed & in_exception, const std::string & in_caller_method_name)
{
    ERROR_STREAM << in_exception << endl;
	
    // rethrow exception
    Tango::Except::re_throw_exception(in_exception,
                                      "TANGO_DEVICE_ERROR",
                                      string(in_exception.errors[0].desc).c_str(),
                                      in_caller_method_name.c_str());
}

//+------------------------------------------------------------------
/**
 *	method:	Lambda::manage_lima_exception
 *
 *	description: method which manages lima exceptions
 */
//+------------------------------------------------------------------
void Lambda::manage_lima_exception(lima::Exception & in_exception, const std::string & in_caller_method_name)
{
    ERROR_STREAM << in_exception.getErrMsg() << endl;

    // throw exception
    Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                   in_exception.getErrMsg().c_str(),
                                   in_caller_method_name.c_str());
}


/*****************************************************************************
 * \brief Update the hardware with the properties data
 *****************************************************************************/
void Lambda::write_at_init(void)
{
	try
	{
		INFO_STREAM << "Write tango hardware at Init - energyThreshold." << endl;
		Tango::WAttribute &energyThreshold = dev_attr->get_w_attr_by_name("energyThreshold");
		double energy_threshold = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevDouble>(this, "energyThreshold", 2.0);
		energyThreshold.set_write_value(energy_threshold);
		write_energyThreshold(energyThreshold);

		//Init Correction attributes
		INFO_STREAM << "Write tango attribute at Init - linearityCorrection." << std::endl;
		Tango::WAttribute &linearityCorrection = dev_attr->get_w_attr_by_name("linearityCorrection");
		bool is_linearity_correction = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevBoolean>(this, "linearityCorrection", false);
		linearityCorrection.set_write_value(is_linearity_correction);
		write_linearityCorrection(linearityCorrection);

		INFO_STREAM << "Write tango attribute at Init - saturationFlag." << std::endl;
		Tango::WAttribute &saturationFlag = dev_attr->get_w_attr_by_name("saturationFlag");
		bool is_saturation_flag = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevBoolean>(this, "saturationFlag", false);
		saturationFlag.set_write_value(is_saturation_flag);
		write_saturationFlag(saturationFlag);

		INFO_STREAM << "Write tango attribute at Init - saturationThreshold." << std::endl;
		Tango::WAttribute &saturationThreshold = dev_attr->get_w_attr_by_name("saturationThreshold");
		long saturation_threshold = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevLong>(this, "saturationThreshold", 0);
		saturationThreshold.set_write_value(saturation_threshold);
		write_saturationThreshold(saturationThreshold);
	}
	catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_energyThreshold");
    }
	catch (lima::Exception& le)
    {						
        manage_lima_exception(le, "read_energyThreshold");
    }
}
/*----- PROTECTED REGION END -----*/	//	Lambda::namespace_ending
} //	namespace
