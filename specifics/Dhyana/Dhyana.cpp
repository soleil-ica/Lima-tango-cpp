/*----- PROTECTED REGION ID(Dhyana.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        Dhyana.cpp
//
// description : C++ source for the Dhyana class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Dhyana are implemented in this file.
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


#include <tango.h>
#include <helpers/PogoHelper.h>
#include <Dhyana.h>
#include <DhyanaClass.h>

#include "AttrViewDhyana95.h"

/*----- PROTECTED REGION END -----*/	//	Dhyana.cpp

/**
 *  Dhyana class description:
 *    Interface the camera Dhyana using  the TUCAM Library
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name      |  Method name
//================================================================
//  State             |  dev_state
//  Status            |  Inherited (no method)
//  GetAllParameters  |  get_all_parameters
//  GetParameter      |  get_parameter
//  SetParameter      |  set_parameter
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace Dhyana_ns
{
/*----- PROTECTED REGION ID(Dhyana::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	Dhyana::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : Dhyana::Dhyana()
 *	Description : Constructors for a Tango device
 *                implementing the classDhyana
 */
//--------------------------------------------------------
Dhyana::Dhyana(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(Dhyana::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::constructor_1
}
//--------------------------------------------------------
Dhyana::Dhyana(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(Dhyana::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::constructor_2
}
//--------------------------------------------------------
Dhyana::Dhyana(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(Dhyana::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void Dhyana::delete_device()
{
	DEBUG_STREAM << "Dhyana::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects

	INFO_STREAM << "Remove the inner-appender." << endl;
    yat4tango::InnerAppender::release(this);

	m_attr_view.reset();

	//!!!! ONLY LimaDetector device can do this !!!!
	//if(m_ct!=0)
	//{
	//    ControlFactory::instance().reset("Dhyana");
	//    m_ct = 0;
	//}

	/*----- PROTECTED REGION END -----*/	//	Dhyana::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void Dhyana::init_device()
{
	DEBUG_STREAM << "Dhyana::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana::init_device_before) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	Dhyana::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	/*----- PROTECTED REGION ID(Dhyana::init_device) ENABLED START -----*/

	m_is_device_initialized = false;
	set_state(Tango::INIT);
	m_status_message.str("");
	
	INFO_STREAM << "Create the inner-appender in order to manage logs." << endl;  
    yat4tango::InnerAppender::initialize(this, 512);

	try
	{
		//- get the main object used to pilot the lima framework
		//in fact LimaDetector is create the singleton control objet
		//so this call, will only return existing object, no need to give it the ip !!
		m_ct = ControlFactory::instance().get_control("Dhyana");

		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Dhyana::Interface*> (m_ct->hwInterface());

		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		
		std::string model;
		m_camera->getDetectorModel(model);
		build_view(model);		
	}
	catch(lima::Exception& e)
	{
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		ERROR_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

	m_is_device_initialized = true;
	

	set_state(Tango::STANDBY);
	dev_state();

	write_attr_at_init();

	/*----- PROTECTED REGION END -----*/	//	Dhyana::init_device
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void Dhyana::get_device_property()
{
	/*----- PROTECTED REGION ID(Dhyana::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	

	/*----- PROTECTED REGION END -----*/	//	Dhyana::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("__ExpertTimerPeriod"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on DhyanaClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		DhyanaClass	*ds_class =
			(static_cast<DhyanaClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize __ExpertTimerPeriod from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  __ExpertTimerPeriod;
		else {
			//	Try to initialize __ExpertTimerPeriod from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  __ExpertTimerPeriod;
		}
		//	And try to extract __ExpertTimerPeriod value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  __ExpertTimerPeriod;

	}

	/*----- PROTECTED REGION ID(Dhyana::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	PropertyHelper::create_property_if_empty(this, dev_prop,"15","TemperatureTargetAtInit");
	PropertyHelper::create_property_if_empty(this, dev_prop,"1","__ExpertTimerPeriod");

	/*----- PROTECTED REGION END -----*/	//	Dhyana::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void Dhyana::always_executed_hook()
{
	/*----- PROTECTED REGION ID(Dhyana::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	try
	{
		yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
		m_status_message.str("");
		//- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("Dhyana");

		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Dhyana::Interface*> (m_ct->hwInterface());

		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());

		//update state
		dev_state();
	}
	catch(lima::Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	catch(...)
	{
		ERROR_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

	/*----- PROTECTED REGION END -----*/	//	Dhyana::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void Dhyana::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	/*----- PROTECTED REGION ID(Dhyana::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	//	Add your own code here

	/*----- PROTECTED REGION END -----*/	//	Dhyana::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : Dhyana::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void Dhyana::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(Dhyana::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command State related method
 *	Description: This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 *	@returns State Code
 */
//--------------------------------------------------------
Tango::DevState Dhyana::dev_state()
{
	/*----- PROTECTED REGION ID(Dhyana::dev_state) ENABLED START -----*/
	
	//	Add your own code
	Tango::DevState argout = DeviceImpl::dev_state();

	//    Add your own code to control device here
	stringstream DeviceStatus;
	DeviceStatus << "";
	Tango::DevState DeviceState = Tango::STANDBY;
	if(!m_is_device_initialized)
	{
		DeviceState = Tango::FAULT;
		DeviceStatus << m_status_message.str();
	}
	else
	{
		// state & status are retrieved from Factory, Factory is updated by Generic device
		DeviceState = ControlFactory::instance().get_state();
		DeviceStatus << ControlFactory::instance().get_status();
	}

	set_state(DeviceState);
	set_status(DeviceStatus.str());

	argout = DeviceState;
	return argout;
	/*----- PROTECTED REGION END -----*/	//	Dhyana::dev_state
	set_state(argout);    // Give the state to Tango.
	if (argout!=Tango::ALARM)
		Tango::DeviceImpl::dev_state();
	return get_state();  // Return it after Tango management.
}
//--------------------------------------------------------
/**
 *	Command GetAllParameters related method
 *	Description: Return the list of all the camera available parameters and their values in the following format:
 *               ParameterName=current_value
 *
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString Dhyana::get_all_parameters()
{
	Tango::DevString argout;
	INFO_STREAM << "Dhyana::GetAllParameters()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana::get_all_parameters) ENABLED START -----*/
	
	//	Add your own code
	try
	{
		return const_cast<Tango::DevString>(m_camera->getAllParameters().c_str());
	}
	catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::get_all_parameters");
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::get_all_parameters");
    }	 
	
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::get_all_parameters
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetParameter related method
 *	Description: Return the current value of the specified parameter
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString Dhyana::get_parameter(Tango::DevString argin)
{
	Tango::DevString argout;
	INFO_STREAM << "Dhyana::GetParameter()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana::get_parameter) ENABLED START -----*/
	//	Add your own code
	try
	{
		std::string result = "";
		result = m_camera->getParameter(std::string(argin));
		argout = new char[result.size() + 1];
		if (result.size() > 0)
        {
            result.copy(argout, result.size());
        }
		argout[result.size()] = '\0'; 
	}
	catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::get_parameter");
					
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::get_parameter");
    }
	
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::get_parameter
	return argout;
}
//--------------------------------------------------------
/**
 *	Command SetParameter related method
 *	Description: Set the value of the specified parameter.
 *
 *	@param argin 
 */
//--------------------------------------------------------
void Dhyana::set_parameter(const Tango::DevVarStringArray *argin)
{
	INFO_STREAM << "Dhyana::SetParameter()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana::set_parameter) ENABLED START -----*/
	if(argin->length() != 2)
	{
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										"Invalid number of parameters. Check input parameters (parameter, value)\n",
										"Dhyana::set_parameter");
	}
    try
    {
		std::string parameter = static_cast<std::string>((*argin)[0]);
		std::string value_str = static_cast<std::string>((*argin)[1]);
		m_camera->setParameter(parameter, value_str);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::set_parameter");
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::set_parameter");
    }	 
	/*----- PROTECTED REGION END -----*/	//	Dhyana::set_parameter
}
//--------------------------------------------------------
/**
 *	Method      : Dhyana::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void Dhyana::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(Dhyana::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana::add_dynamic_commands
}

/*----- PROTECTED REGION ID(Dhyana::namespace_ending) ENABLED START -----*/

bool Dhyana::is_device_initialized()
{
	return m_is_device_initialized;
}

lima::Dhyana::Camera* Dhyana::get_camera()
{
	return m_camera;
}


void Dhyana::build_view(std::string model)
{
	if (model == "Dhyana 95" || model.find("Dhyana 95 V2") != std::string::npos)
	{
		m_attr_view.reset(new AttrViewDhyana95(this));
	}
	else if (model == "Dhyana 6060")
	{
	}

}

void Dhyana::write_attr_at_init()
{
	try
	{
		INFO_STREAM << "Write tango hardware at Init - sensorTemperatureTarget." << endl;
		Tango::WAttribute &temperatureTarget = dev_attr->get_w_attr_by_name("sensorTemperatureTarget");
		double temperature_target = yat4tango::PropertyHelper::get_property<Tango::DevDouble>(this, "TemperatureTargetAtInit");
		temperatureTarget.set_write_value(temperature_target);
		yat4tango::DynamicAttributeWriteCallbackData cbd_temperatureTarget;
        cbd_temperatureTarget.tga = &temperatureTarget;
		cbd_temperatureTarget.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("sensorTemperatureTarget");
        m_attr_view->write_dynamic_attribute_callback(cbd_temperatureTarget);

		INFO_STREAM << "Write tango hardware at Init - fanSpeed." << endl;
		Tango::WAttribute &fanSpeed = dev_attr->get_w_attr_by_name("fanSpeed");
		unsigned short speed = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevUShort>(this, "fanSpeed", 1);
		fanSpeed.set_write_value(speed);
		yat4tango::DynamicAttributeWriteCallbackData cbd_fanSpeed;
        cbd_fanSpeed.tga = &fanSpeed;
		cbd_fanSpeed.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("fanSpeed");
        m_attr_view->write_dynamic_attribute_callback(cbd_fanSpeed);

		INFO_STREAM << "Write tango hardware at Init - globalGain." << endl;
		Tango::WAttribute &globalGain = dev_attr->get_w_attr_by_name("globalGain");
		Tango::DevEnum gain = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, "globalGain", 0);
		globalGain.set_write_value(gain);
		yat4tango::DynamicAttributeWriteCallbackData cbd_globalGain;
        cbd_globalGain.tga = &globalGain;
		cbd_globalGain.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("globalGain");
        m_attr_view->write_dynamic_attribute_callback(cbd_globalGain);
		
		for (int i = 1; i < 4; i++)
        {
            std::string name = "trigOutputKind" + std::to_string(i);
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
			Tango::WAttribute &trigOutputKind = dev_attr->get_w_attr_by_name(name.c_str());
			Tango::DevEnum val = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, name, 0);
			trigOutputKind.set_write_value(val);
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputKind;
			cbd_trigOutputKind.tga = &trigOutputKind;
			cbd_trigOutputKind.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputKind);
		}

		for (int i = 1; i < 4; i++)
        {
            std::string name = "trigOutputWidth" + std::to_string(i);
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
			Tango::WAttribute &trigOutputWidth = dev_attr->get_w_attr_by_name(name.c_str());
			double val = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevDouble>(this, name, 5);
			trigOutputWidth.set_write_value(val);
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputWidth;
			cbd_trigOutputWidth.tga = &trigOutputWidth;
			cbd_trigOutputWidth.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputWidth);
		}

		for (int i = 1; i < 4; i++)
        {
            std::string name = "trigOutputDelay" + std::to_string(i);
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
			Tango::WAttribute &trigOutputDelay = dev_attr->get_w_attr_by_name(name.c_str());
			double val = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevDouble>(this, name, 0);
			trigOutputDelay.set_write_value(val);
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputDelay;
			cbd_trigOutputDelay.tga = &trigOutputDelay;
			cbd_trigOutputDelay.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputDelay);
		}

		for (int i = 1; i < 4; i++)
        {
            std::string name = "trigOutputEdge" + std::to_string(i);
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
			Tango::WAttribute &trigOutputEdge = dev_attr->get_w_attr_by_name(name.c_str());
			Tango::DevEnum val = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, name, 0);
			trigOutputEdge.set_write_value(val);
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputEdge;
			cbd_trigOutputEdge.tga = &trigOutputEdge;
			cbd_trigOutputEdge.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputEdge);
		}

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
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
}


/*----- PROTECTED REGION END -----*/	//	Dhyana::namespace_ending
} //	namespace
