static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         Dhyana.cpp
//
// description :  C++ source for the Dhyana and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                Dhyana are implemented in this file.
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
//  Command name|  Method name
//	----------------------------------------
//  State   |  dev_state()
//  Status  |  dev_status()
//
//===================================================================


#include <tango.h>
#include <PogoHelper.h>
#include <Dhyana.h>
#include <DhyanaClass.h>

namespace Dhyana_ns
{

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::Dhyana(string &s)
// 
// description : 	constructor for simulated Dhyana
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
Dhyana::Dhyana(Tango::DeviceClass *cl, string &s)
:Tango::Device_4Impl(cl, s.c_str())
{
	init_device();
}
Dhyana::Dhyana(Tango::DeviceClass *cl, const char *s)
:Tango::Device_4Impl(cl, s)
{
	init_device();
}
Dhyana::Dhyana(Tango::DeviceClass *cl, const char *s, const char *d)
:Tango::Device_4Impl(cl, s, d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		Dhyana::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void Dhyana::delete_device()
{
	DELETE_DEVSTRING_ATTRIBUTE(attr_tucamVersion_read);
	DELETE_DEVSTRING_ATTRIBUTE(attr_globalGain_read);	
	DELETE_SCALAR_ATTRIBUTE(attr_temperatureTarget_read);
	DELETE_SCALAR_ATTRIBUTE(attr_temperature_read);
	DELETE_SCALAR_ATTRIBUTE(attr_fanSpeed_read);
	//	Delete device allocated objects

	// No Inner Appender

	//!!!! ONLY LimaDetector device can do this !!!!
	//if(m_ct!=0)
	//{
	//    ControlFactory::instance().reset("Dhyana");
	//    m_ct = 0;
	//}    
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void Dhyana::init_device()
{
	INFO_STREAM << "Dhyana::Dhyana() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	get_device_property();

	CREATE_DEVSTRING_ATTRIBUTE(attr_tucamVersion_read, MAX_ATTRIBUTE_STRING_LENGTH);
	CREATE_DEVSTRING_ATTRIBUTE(attr_globalGain_read, MAX_ATTRIBUTE_STRING_LENGTH);
	CREATE_SCALAR_ATTRIBUTE(attr_temperatureTarget_read, 0.0);
	CREATE_SCALAR_ATTRIBUTE(attr_temperature_read, 0.0);
	CREATE_SCALAR_ATTRIBUTE(attr_fanSpeed_read);


	m_is_device_initialized = false;
	set_state(Tango::INIT);
	m_status_message.str("");
	
	// No Inner Appender

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
	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

	m_is_device_initialized = true;
	try
	{
		INFO_STREAM << "Write tango hardware at Init - temperatureTarget." << endl;
		Tango::WAttribute &temperatureTarget = dev_attr->get_w_attr_by_name("temperatureTarget");
		*attr_temperatureTarget_read = memorizedTemperatureTarget;
		temperatureTarget.set_write_value(*attr_temperatureTarget_read);
		write_temperatureTarget(temperatureTarget);

		INFO_STREAM << "Write tango hardware at Init - fanSpeed." << endl;
		Tango::WAttribute &fanSpeed = dev_attr->get_w_attr_by_name("fanSpeed");
		*attr_fanSpeed_read = memorizedFanSpeed;
		fanSpeed.set_write_value(*attr_fanSpeed_read);
		write_fanSpeed(fanSpeed);

		INFO_STREAM << "Write tango hardware at Init - globalGain." << endl;
		Tango::WAttribute &globalGain = dev_attr->get_w_attr_by_name("globalGain");
		strcpy(*attr_globalGain_read, memorizedGlobalGain.c_str());
		m_global_gain = memorizedGlobalGain;
		globalGain.set_write_value(*attr_globalGain_read);
		write_globalGain(globalGain);

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
	catch(Exception& e)
	{
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}

	set_state(Tango::STANDBY);
	dev_state();
}


//+----------------------------------------------------------------------------
//
// method : 		Dhyana::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void Dhyana::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("MemorizedTemperatureTarget"));
	dev_prop.push_back(Tango::DbDatum("MemorizedFanSpeed"));
	dev_prop.push_back(Tango::DbDatum("MemorizedGlobalGain"));
	dev_prop.push_back(Tango::DbDatum("__ExpertTimerPeriod"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	DhyanaClass	*ds_class =
		(static_cast<DhyanaClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize MemorizedTemperatureTarget from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedTemperatureTarget;
	else {
		//	Try to initialize MemorizedTemperatureTarget from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedTemperatureTarget;
	}
	//	And try to extract MemorizedTemperatureTarget value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedTemperatureTarget;

	//	Try to initialize MemorizedFanSpeed from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedFanSpeed;
	else {
		//	Try to initialize MemorizedFanSpeed from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedFanSpeed;
	}
	//	And try to extract MemorizedFanSpeed value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedFanSpeed;

	//	Try to initialize MemorizedGlobalGain from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedGlobalGain;
	else {
		//	Try to initialize MemorizedGlobalGain from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedGlobalGain;
	}
	//	And try to extract MemorizedGlobalGain value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedGlobalGain;

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



	//	End of Automatic code generation
	//------------------------------------------------------------------
	PropertyHelper::create_property_if_empty(this, dev_prop,"0","MemorizedTemperatureTarget");	
	PropertyHelper::create_property_if_empty(this, dev_prop,"1","MemorizedFanSpeed");	
	PropertyHelper::create_property_if_empty(this, dev_prop,"LOW","MemorizedGlobalGain");	
	PropertyHelper::create_property_if_empty(this, dev_prop,"1","__ExpertTimerPeriod");	


}
//+----------------------------------------------------------------------------
//
// method : 		Dhyana::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void Dhyana::always_executed_hook()
{
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
	catch(Exception& e)
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
}
//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void Dhyana::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "Dhyana::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	//	Add your own code here
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::write_temperatureTarget
// 
// description : 	Write temperatureTarget attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Dhyana::write_temperatureTarget(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Dhyana::write_temperatureTarget(Tango::WAttribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		attr.get_write_value(attr_temperatureTarget_write);
		m_camera->setTemperatureTarget(attr_temperatureTarget_write);
		yat4tango::PropertyHelper::set_property(this, "MemorizedTemperatureTarget", attr_temperatureTarget_write);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::write_temperatureTarget");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::write_temperatureTarget");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_temperature
// 
// description : 	Extract real attribute values for temperature acquisition result.
//
//-----------------------------------------------------------------------------
void Dhyana::read_temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Dhyana::read_temperature(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		double value;
		m_camera->getTemperature(value);
		*attr_temperature_read = value;
		attr.set_value(attr_temperature_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::read_temperature");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::read_temperature");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_fanSpeed
// 
// description : 	Extract real attribute values for fanSpeed acquisition result.
//
//-----------------------------------------------------------------------------
void Dhyana::read_fanSpeed(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Dhyana::read_fanSpeed(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		unsigned value;
		m_camera->getFanSpeed(value);
		*attr_fanSpeed_read = value;
		attr.set_value(attr_fanSpeed_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::read_fanSpeed");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::read_fanSpeed");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::write_fanSpeed
// 
// description : 	Write fanSpeed attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Dhyana::write_fanSpeed(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Dhyana::write_fanSpeed(Tango::WAttribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		attr.get_write_value(attr_fanSpeed_write);
		m_camera->setFanSpeed(attr_fanSpeed_write);
		yat4tango::PropertyHelper::set_property(this, "MemorizedFanSpeed", attr_fanSpeed_write);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::write_fanSpeed");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::write_fanSpeed");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_globalGain
// 
// description : 	Extract real attribute values for globalGain acquisition result.
//
//-----------------------------------------------------------------------------
void Dhyana::read_globalGain(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Dhyana::read_globalGain(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		unsigned nVal;
		std::string gain;
		m_camera->getGlobalGain(nVal);
		if(nVal == 2)
			gain = "LOW";
		else if(nVal == 1)
			gain = "HIGH";
		else //(nVal == 0)
			gain = "HDR";
		strcpy(*attr_globalGain_read, gain.c_str());
		attr.set_value(attr_globalGain_read);
	}
	catch(Tango::DevFailed& df)
	{

		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  std::string(df.errors[0].desc).c_str(),
										  "Dhyana::read_globalGain");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::write_globalGain
// 
// description : 	Write globalGain attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Dhyana::write_globalGain(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Dhyana::write_globalGain(Tango::WAttribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		m_global_gain = *attr_globalGain_read;//memorize previous valid value
		attr.get_write_value(attr_globalGain_write);
		std::string current = attr_globalGain_write;
		transform(current.begin(), current.end(), current.begin(), ::toupper);
		if((current != "LOW") &&
		   (current != "HIGH") &&
		   (current != "HDR")
		   )
		{
			attr_globalGain_write = const_cast<Tango::DevString> (m_global_gain.c_str());
			Tango::Except::throw_exception("CONFIGURATION_ERROR",
										   "Possible globalGain values are :"
										   "\nHDR"
										   "\nHIGH"
										   "\nLOW\n",
										   "Dhyana::write_globalGain");
		}

		//- THIS IS AN AVAILABLE globalGain     
		m_global_gain = current;
		unsigned nVal;
		if(m_global_gain == "LOW")
			nVal = 2;
		else if(m_global_gain == "HIGH")
			nVal = 1;
		else //(m_global_gain == "HDR")
			nVal = 0;
		m_camera->setGlobalGain(nVal);
		PropertyHelper::set_property(this, "MemorizedGlobalGain", m_global_gain);
	}
	catch(Tango::DevFailed& df)
	{

		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  std::string(df.errors[0].desc).c_str(),
										  "Dhyana::write_globalGain");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_temperatureTarget
// 
// description : 	Extract real attribute values for temperatureTarget acquisition result.
//
//-----------------------------------------------------------------------------
void Dhyana::read_temperatureTarget(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Dhyana::read_temperatureTarget(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		double value;
		m_camera->getTemperatureTarget(value);
		*attr_temperatureTarget_read = value;
		attr.set_value(attr_temperatureTarget_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::read_temperatureTarget");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::read_temperatureTarget");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Dhyana::read_tucamVersion
// 
// description : 	Extract real attribute values for tucamVersion acquisition result.
//
//-----------------------------------------------------------------------------
void Dhyana::read_tucamVersion(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Dhyana::read_tucamVersion(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
	try
	{
		std::string version;
		m_camera->getTucamVersion(version);
		strcpy(*attr_tucamVersion_read, version.c_str());

		attr.set_value(attr_tucamVersion_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										  "TANGO_DEVICE_ERROR",
										  string(df.errors[0].desc).c_str(),
										  "Dhyana::read_tucamVersion");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
									   e.getErrMsg().c_str(),
									   "Dhyana::read_tucamVersion");
	}
}


//+------------------------------------------------------------------
/**
 *    method:    Dhyana::dev_state
 *
 *    description:    method to execute "State"
 *    This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return    State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState Dhyana::dev_state()
{
	Tango::DevState argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "Dhyana::dev_state(): entering... !" << endl;

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
}



}	//	namespace
