/*----- PROTECTED REGION ID(SlsJungfrau.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        SlsJungfrau.cpp
//
// description : C++ source for the SlsJungfrau class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               SlsJungfrau are implemented in this file.
//
// project :     Sls dectector TANGO specific device.
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


#include <SlsJungfrau.h>
#include <SlsJungfrauClass.h>

// SYSTEM
#include <map>
#include <string>

/*----- PROTECTED REGION END -----*/	//	SlsJungfrau.cpp

/**
 *  SlsJungfrau class description:
 *    Device for sls detectors from PSI. 
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//  SetCmd        |  set_cmd
//  GetCmd        |  get_cmd
//  ResetCamera   |  reset_camera
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  clockDivider             |  Tango::DevString	Scalar
//  configFileName           |  Tango::DevString	Scalar
//  delayAfterTrigger        |  Tango::DevDouble	Scalar
//  detectorFirmwareVersion  |  Tango::DevString	Scalar
//  detectorSoftwareVersion  |  Tango::DevString	Scalar
//  gainMode                 |  Tango::DevString	Scalar
//================================================================

namespace SlsJungfrau_ns
{
/*----- PROTECTED REGION ID(SlsJungfrau::namespace_starting) ENABLED START -----*/

//	static initializations
//-------------------------------------------------------------------------
// CLOCK DIVIDER
//-------------------------------------------------------------------------
static const std::vector<std::string> TANGO_CLOCK_DIVIDER_LABELS{"FULL_SPEED", "HALF_SPEED", "QUARTER_SPEED", "SUPER_SLOW_SPEED" }; // labels of clock divider

std::vector<enum lima::SlsJungfrau::Camera::ClockDivider> TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE{lima::SlsJungfrau::Camera::ClockDivider::FullSpeed     ,
                                                                                             lima::SlsJungfrau::Camera::ClockDivider::HalfSpeed     ,
                                                                                             lima::SlsJungfrau::Camera::ClockDivider::QuarterSpeed  ,
                                                                                             lima::SlsJungfrau::Camera::ClockDivider::SuperSlowSpeed};

//-------------------------------------------------------------------------
// GAIN MODE
//-------------------------------------------------------------------------
static const std::vector<std::string> TANGO_GAIN_MODE_LABELS{"DYNAMIC", "DYNAMICHG0", "FIXGAIN1", "FIXGAIN2", "FORCESWITCHG1", "FORCESWITCHG2", "UNDEFINED"}; // labels of gain mode

std::vector<enum lima::SlsJungfrau::Camera::GainMode>
  TANGO_GAIN_MODE_LABELS_TO_TYPE{lima::SlsJungfrau::Camera::GainMode::dynamic      ,
                                 lima::SlsJungfrau::Camera::GainMode::dynamichg0   ,
                                 lima::SlsJungfrau::Camera::GainMode::fixgain1     ,
                                 lima::SlsJungfrau::Camera::GainMode::fixgain2     ,
                                 lima::SlsJungfrau::Camera::GainMode::forceswitchg1,
                                 lima::SlsJungfrau::Camera::GainMode::forceswitchg2,
                                 lima::SlsJungfrau::Camera::GainMode::undefined    };

/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::SlsJungfrau()
 *	Description : Constructors for a Tango device
 *                implementing the classSlsJungfrau
 */
//--------------------------------------------------------
SlsJungfrau::SlsJungfrau(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str()),m_dim(this)
{
	/*----- PROTECTED REGION ID(SlsJungfrau::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::constructor_1
}
//--------------------------------------------------------
SlsJungfrau::SlsJungfrau(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s),m_dim(this)
{
	/*----- PROTECTED REGION ID(SlsJungfrau::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::constructor_2
}
//--------------------------------------------------------
SlsJungfrau::SlsJungfrau(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d),m_dim(this)
{
	/*----- PROTECTED REGION ID(SlsJungfrau::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void SlsJungfrau::delete_device()
{
	DEBUG_STREAM << "SlsJungfrau::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::delete_device) ENABLED START -----*/
	delete[] attr_clockDivider_read           [0];
	delete[] attr_configFileName_read         [0];
	delete[] attr_detectorFirmwareVersion_read[0];
	delete[] attr_detectorSoftwareVersion_read[0];
	delete[] attr_gainMode_read               [0];

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::delete_device
	delete[] attr_clockDivider_read;
	delete[] attr_configFileName_read;
	delete[] attr_delayAfterTrigger_read;
	delete[] attr_detectorFirmwareVersion_read;
	delete[] attr_detectorSoftwareVersion_read;
	delete[] attr_gainMode_read;

    INFO_STREAM << "Remove the inner-appender." << endl;
    yat4tango::InnerAppender::release(this);
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void SlsJungfrau::init_device()
{
	DEBUG_STREAM << "SlsJungfrau::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::init_device_before) ENABLED START -----*/
	INFO_STREAM << "SlsJungfrau::init_device() create device " << device_name << endl;

    m_is_device_initialized = false;
    set_state(Tango::INIT);
    m_status_message.str("");

    INFO_STREAM << "Create the inner-appender in order to manage logs." << endl;  
    yat4tango::InnerAppender::initialize(this, 512);

	try
	{
		//- get the main object used to pilot the lima framework		
		m_ct = ControlFactory::instance().get_control("SlsJungfrau");
		
		//- get interface to specific camera
		m_hw = dynamic_cast<lima::SlsJungfrau::Interface*>(m_ct->hwInterface());
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
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

	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	attr_clockDivider_read = new Tango::DevString[1];
	attr_configFileName_read = new Tango::DevString[1];
	attr_delayAfterTrigger_read = new Tango::DevDouble[1];
	attr_detectorFirmwareVersion_read = new Tango::DevString[1];
	attr_detectorSoftwareVersion_read = new Tango::DevString[1];
	attr_gainMode_read = new Tango::DevString[1];

	/*----- PROTECTED REGION ID(SlsJungfrau::init_device) ENABLED START -----*/
    attr_clockDivider_read           [0] = new char[ 256];
    attr_configFileName_read         [0] = new char[1024];
    attr_detectorFirmwareVersion_read[0] = new char[ 256];
    attr_detectorSoftwareVersion_read[0] = new char[ 256];
    attr_gainMode_read               [0] = new char[ 256];

    ::strcpy(attr_clockDivider_read           [0], "");
    ::strcpy(attr_configFileName_read         [0], "");
    ::strcpy(attr_detectorFirmwareVersion_read[0], "");
    ::strcpy(attr_detectorSoftwareVersion_read[0], "");
    ::strcpy(attr_gainMode_read               [0], "");
        
    //	Initialize device
	m_is_device_initialized = true;
	set_state(Tango::STANDBY);
	dev_state();	
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::init_device
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void SlsJungfrau::get_device_property()
{
	/*----- PROTECTED REGION ID(SlsJungfrau::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("ConfigFileName"));
	dev_prop.push_back(Tango::DbDatum("ExpertReadoutTime"));
	dev_prop.push_back(Tango::DbDatum("ExpertReceiverFifoDepth"));
	dev_prop.push_back(Tango::DbDatum("ExpertFramePacketNumber"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on SlsJungfrauClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		SlsJungfrauClass	*ds_class =
			(static_cast<SlsJungfrauClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize ConfigFileName from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  configFileName;
		else {
			//	Try to initialize ConfigFileName from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  configFileName;
		}
		//	And try to extract ConfigFileName value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  configFileName;

		//	Try to initialize ExpertReadoutTime from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  expertReadoutTime;
		else {
			//	Try to initialize ExpertReadoutTime from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  expertReadoutTime;
		}
		//	And try to extract ExpertReadoutTime value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  expertReadoutTime;

		//	Try to initialize ExpertReceiverFifoDepth from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  expertReceiverFifoDepth;
		else {
			//	Try to initialize ExpertReceiverFifoDepth from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  expertReceiverFifoDepth;
		}
		//	And try to extract ExpertReceiverFifoDepth value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  expertReceiverFifoDepth;

		//	Try to initialize ExpertFramePacketNumber from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  expertFramePacketNumber;
		else {
			//	Try to initialize ExpertFramePacketNumber from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  expertFramePacketNumber;
		}
		//	And try to extract ExpertFramePacketNumber value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  expertFramePacketNumber;

	}

	/*----- PROTECTED REGION ID(SlsJungfrau::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, ""       , "ConfigFileName"         );
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "0.00004", "ExpertReadoutTime"      ); // 40µs by default
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "2500"   , "ExpertReceiverFifoDepth"); // 2500 frames by default
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "128"    , "ExpertFramePacketNumber"); // 128 packets by default
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void SlsJungfrau::always_executed_hook()
{
	DEBUG_STREAM << "SlsJungfrau::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
    try
    {
        m_status_message.str("");

        //update state
        dev_state();
    }
    catch (Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        m_status_message << "always_executed_hook : " << e.getErrMsg() << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (...)
    {
        ERROR_STREAM << "always_executed_hook : UNKNOWN" << endl;
        m_status_message << "always_executed_hook : UNKNOWN" << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void SlsJungfrau::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "SlsJungfrau::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void SlsJungfrau::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "SlsJungfrau::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::write_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute clockDivider related method
 *	Description: Changes the readout clock.<br>
 *               Available clock Divider :<br>
 *               FULL_SPEED<br>
 *               HALF_SPEED<br>
 *               QUARTER_SPEED<br>
 *               SUPER_SLOW_SPEED<br>
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_clockDivider(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_clockDivider(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_clockDivider) ENABLED START -----*/

    try
    {
        enum lima::SlsJungfrau::Camera::ClockDivider clock_divider;

        clock_divider = m_camera->getClockDivider();

        const std::vector<enum lima::SlsJungfrau::Camera::ClockDivider>::const_iterator 
        iterator = find(TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE.begin(), 
                        TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE.end  (),
                        clock_divider                             );

        // found it
        if (iterator != TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE.end()) 
        {
            // if an acquisition is running, the attribute is in alarm because we return the latest cache value.
            bool attribute_is_in_alarm = (get_state() == Tango::RUNNING);

            string clock_divider_label = TANGO_CLOCK_DIVIDER_LABELS[iterator - TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE.begin()]; // calculation gives the index

            //Set the attribute value
            strcpy(*attr_clockDivider_read, clock_divider_label.c_str());
            attr.set_value(attr_clockDivider_read);
            attr.set_quality((attribute_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
        }
        else
        {
            std::ostringstream MsgErr;
            MsgErr << "Impossible to found the clock divider mode " << clock_divider << std::endl;

            Tango::Except::throw_exception("LOGIC_ERROR",
                                           MsgErr.str().c_str(),
                                           "SlsJungfrau::read_clockDivider");
        }
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_clockDivider");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_clockDivider");
    }

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_clockDivider
}
//--------------------------------------------------------
/**
 *	Write attribute clockDivider related method
 *	Description: Changes the readout clock.<br>
 *               Available clock Divider :<br>
 *               FULL_SPEED<br>
 *               HALF_SPEED<br>
 *               QUARTER_SPEED<br>
 *               SUPER_SLOW_SPEED<br>
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::write_clockDivider(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::write_clockDivider(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevString	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(SlsJungfrau::write_clockDivider) ENABLED START -----*/
	
    // we need to convert the clock divider string to the hardware clock divider
    enum lima::SlsJungfrau::Camera::ClockDivider clock_divider;

    const std::vector<string>::const_iterator 
    iterator = find(TANGO_CLOCK_DIVIDER_LABELS.begin(), 
                    TANGO_CLOCK_DIVIDER_LABELS.end  (),
                    string(w_val)                    );

    // found it
    if (iterator != TANGO_CLOCK_DIVIDER_LABELS.end()) 
    {
        clock_divider = TANGO_CLOCK_DIVIDER_LABELS_TO_TYPE[iterator - TANGO_CLOCK_DIVIDER_LABELS.begin()]; // calculation gives the index
    }
    else
    {
        std::stringstream message;
        message.str("");
        message << "Incorrect clock divider : " << w_val << std::endl;
        message << "Available clock divider modes are :" << std::endl;
        message << "FULL_SPEED"       << std::endl;
        message << "HALF_SPEED"       << std::endl;
        message << "QUARTER_SPEED"    << std::endl;
        message << "SUPER_SLOW_SPEED" << std::endl;

        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       message.str().c_str(), 
                                       "Controller::write_clockDivider()");
    }

    try
    {
        // set the camera value
        m_camera->setClockDivider(clock_divider);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::write_clockDivider");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::write_clockDivider");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::write_clockDivider
}
//--------------------------------------------------------
/**
 *	Read attribute configFileName related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_configFileName(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_configFileName(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_configFileName) ENABLED START -----*/
	
    try
    {
        //Set the attribute value
        strcpy(*attr_configFileName_read, configFileName.c_str());
        attr.set_value(attr_configFileName_read);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_configFileName");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_configFileName");
    }

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_configFileName
}
//--------------------------------------------------------
/**
 *	Read attribute delayAfterTrigger related method
 *	Description: set/get delay after trigger in ms.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_delayAfterTrigger(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_delayAfterTrigger(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_delayAfterTrigger) ENABLED START -----*/

    try
    {
        // if an acquisition is running, the attribute is in alarm because we return the latest cache value.
        bool attribute_is_in_alarm = (get_state() == Tango::RUNNING);

        // get the camera value
        // converting delay after trigger because 
        // - camera delay after trigger is in seconds
        // - lima delays are in ms
        double delay_after_trigger = m_camera->getDelayAfterTrigger() * 1000.0;

        // set the attribute value
        *attr_delayAfterTrigger_read = (Tango::DevDouble)(delay_after_trigger);
        attr.set_value(attr_delayAfterTrigger_read);
        attr.set_quality((attribute_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_delayAfterTrigger");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_delayAfterTrigger");
    }

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_delayAfterTrigger
}
//--------------------------------------------------------
/**
 *	Write attribute delayAfterTrigger related method
 *	Description: set/get delay after trigger in ms.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::write_delayAfterTrigger(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::write_delayAfterTrigger(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(SlsJungfrau::write_delayAfterTrigger) ENABLED START -----*/

    try
    {
        // set the camera value
        // converting delay after trigger because 
        // - camera delay after trigger is in seconds
        // - lima delays are in ms
        m_camera->setDelayAfterTrigger(static_cast<double>(w_val) / 1000.0);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::write_delayAfterTrigger");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::write_delayAfterTrigger");
    }	
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::write_delayAfterTrigger
}
//--------------------------------------------------------
/**
 *	Read attribute detectorFirmwareVersion related method
 *	Description: Get detector firmware version.
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_detectorFirmwareVersion(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_detectorFirmwareVersion(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_detectorFirmwareVersion) ENABLED START -----*/
	//	Set the attribute value
    try
    {
        // if an acquisition is running, the attribute is in alarm because we return the latest cache value.
        bool attribute_is_in_alarm = (get_state() == Tango::RUNNING);

        // get the camera data
        std::string version = m_camera->getDetectorFirmwareVersion();

        //Set the attribute value
        strcpy(*attr_detectorFirmwareVersion_read, version.c_str());
        attr.set_value(attr_detectorFirmwareVersion_read);
        attr.set_quality((attribute_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_detectorFirmwareVersion");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_detectorFirmwareVersion");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_detectorFirmwareVersion
}
//--------------------------------------------------------
/**
 *	Read attribute detectorSoftwareVersion related method
 *	Description: Get detector software version.
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_detectorSoftwareVersion(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_detectorSoftwareVersion(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_detectorSoftwareVersion) ENABLED START -----*/
	//	Set the attribute value
    try
    {
        // if an acquisition is running, the attribute is in alarm because we return the latest cache value.
        bool attribute_is_in_alarm = (get_state() == Tango::RUNNING);

        // get the camera data
        std::string version = m_camera->getDetectorSoftwareVersion();

        //Set the attribute value
        strcpy(*attr_detectorSoftwareVersion_read, version.c_str());
        attr.set_value(attr_detectorSoftwareVersion_read);
        attr.set_quality((attribute_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_detectorSoftwareVersion");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_detectorSoftwareVersion");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_detectorSoftwareVersion
}
//--------------------------------------------------------
/**
 *	Read attribute gainMode related method
 *	Description: Changes the gain mode.<br>
 *               Available gain modes:<br>
 *               DYNAMIC -> dynamic gain settings<br>
 *               DYNAMICHG0 -> dynamic high gain 0<br>
 *               FIXGAIN1 -> fix gain 1<br>
 *               FIXGAIN2 -> fix gain 2<br>
 *               FORCESWITCHG1 -> force switch gain 1<br>
 *               FORCESWITCHG2 -> force switch gain 2<br>
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::read_gainMode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::read_gainMode(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::read_gainMode) ENABLED START -----*/
	//	Set the attribute value
    try
    {
        enum lima::SlsJungfrau::Camera::GainMode gain_mode = m_camera->getGainMode();

        const std::vector<enum lima::SlsJungfrau::Camera::GainMode>::const_iterator 
            iterator = find(TANGO_GAIN_MODE_LABELS_TO_TYPE.begin(), 
                            TANGO_GAIN_MODE_LABELS_TO_TYPE.end  (),
                            gain_mode                            );
        // found it
        if (iterator != TANGO_GAIN_MODE_LABELS_TO_TYPE.end()) 
        {
            // if an acquisition is running, the attribute is in alarm because we return the latest cache value.
            bool attribute_is_in_alarm = (get_state() == Tango::RUNNING);

            string gain_mode_label = TANGO_GAIN_MODE_LABELS[iterator - TANGO_GAIN_MODE_LABELS_TO_TYPE.begin()]; // calculation gives the index

            //Set the attribute value
            strcpy(*attr_gainMode_read, gain_mode_label.c_str());
            attr.set_value(attr_gainMode_read);
            attr.set_quality((attribute_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
        }
        else
        {
            std::ostringstream MsgErr;
            MsgErr << "Impossible to found the gain mode " << gain_mode << std::endl;

            Tango::Except::throw_exception("LOGIC_ERROR",
                                           MsgErr.str().c_str(),
                                           "SlsJungfrau::read_gainMode");
        }
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::read_gainMode");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::read_gainMode");
    }

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::read_gainMode
}
//--------------------------------------------------------
/**
 *	Write attribute gainMode related method
 *	Description: Changes the gain mode.<br>
 *               Available gain modes:<br>
 *               DYNAMIC -> dynamic gain settings<br>
 *               DYNAMICHG0 -> dynamic high gain 0<br>
 *               FIXGAIN1 -> fix gain 1<br>
 *               FIXGAIN2 -> fix gain 2<br>
 *               FORCESWITCHG1 -> force switch gain 1<br>
 *               FORCESWITCHG2 -> force switch gain 2<br>
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void SlsJungfrau::write_gainMode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "SlsJungfrau::write_gainMode(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevString	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(SlsJungfrau::write_gainMode) ENABLED START -----*/
	
    // we need to convert the gain mode string to the hardware clock divider
    enum lima::SlsJungfrau::Camera::GainMode gain_mode;
    const std::vector<string>::const_iterator 
    iterator = find(TANGO_GAIN_MODE_LABELS.begin(), 
                    TANGO_GAIN_MODE_LABELS.end  (),
                    string(w_val)                 );
    // found it
    if (iterator != TANGO_GAIN_MODE_LABELS.end()) 
    {
        // calculation gives the index
        gain_mode = TANGO_GAIN_MODE_LABELS_TO_TYPE[iterator - TANGO_GAIN_MODE_LABELS.begin()];
    }
    else
    {
        std::stringstream message;
        message.str("");
        message << "Incorrect gain mode : " << w_val << std::endl;
        message << "Available gain modes are :" << std::endl;

        for(size_t index = 0 ; index < TANGO_GAIN_MODE_LABELS.size() ; index++)
        {
            message << TANGO_GAIN_MODE_LABELS[index] << std::endl;
        }

        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       message.str().c_str(), 
                                       "SlsJungfrau::write_gainMode()");
    }
    try
    {
        // set the camera value
        m_camera->setGainMode(gain_mode);
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::write_gainMode");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::write_gainMode");
    }

	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::write_gainMode
}

//--------------------------------------------------------
/**
 *	Method      : SlsJungfrau::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void SlsJungfrau::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(SlsJungfrau::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command SetCmd related method
 *	Description: Allows to execute a line command (set type)
 *
 *	@param argin SlsDetector command
 *	@returns SlsDetector response
 */
//--------------------------------------------------------
Tango::DevString SlsJungfrau::set_cmd(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "SlsJungfrau::SetCmd()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::set_cmd) ENABLED START -----*/
	
    try
    {
        std::string result = m_camera->setCmd(std::string(argin));

        argout = new char[result.size() + 1];

        if (result.size() > 0)
        {
            result.copy(argout, result.size());
        }

        argout[result.size()] = '\0';
	}
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::SetCmd");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::SetCmd");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::set_cmd
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetCmd related method
 *	Description: Allows to execute a line command (get type)
 *
 *	@param argin SlsDetector command
 *	@returns SlsDetector response
 */
//--------------------------------------------------------
Tango::DevString SlsJungfrau::get_cmd(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "SlsJungfrau::GetCmd()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::get_cmd) ENABLED START -----*/
	
    try
    {
        std::string result = m_camera->getCmd(std::string(argin));

        argout = new char[result.size() + 1];

        if (result.size() > 0)
        {
            result.copy(argout, result.size());
        }

        argout[result.size()] = '\0';
    }
    catch(Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::GetCmd");
    }
    catch(Exception& e)
    {
        manage_lima_exception(e, "SlsJungfrau::GetCmd");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::get_cmd
	return argout;
}
//--------------------------------------------------------
/**
 *	Command ResetCamera related method
 *	Description: Execute an hardware reset of the camera.
 *
 */
//--------------------------------------------------------
void SlsJungfrau::reset_camera()
{
	DEBUG_STREAM << "SlsJungfrau::ResetCamera()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(SlsJungfrau::reset_camera) ENABLED START -----*/
	
    try
    {
        const std::string cmd = "resetfpga 0";
        m_camera->setCmd(cmd);
	}
    catch(Tango::DevFailed & df)
    {
        manage_devfailed_exception(df, "SlsJungfrau::reset_camera");
    }
    catch(Exception & e)
    {
        manage_lima_exception(e, "SlsJungfrau::reset_camera");
    }
	
	/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::reset_camera
}

/*----- PROTECTED REGION ID(SlsJungfrau::namespace_ending) ENABLED START -----*/

//	Additional Methods
//+------------------------------------------------------------------
/**
 *	method:	SlsJungfrau::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState SlsJungfrau::dev_state()
{
    Tango::DevState	argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "SlsJungfrau::dev_state(): entering... !" << endl;

    // Add your own code to control device here
    stringstream    DeviceStatus;
    DeviceStatus     << "";
    Tango::DevState DeviceState    = Tango::STANDBY;
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
 *	method:	SlsJungfrau::manage_devfailed_exception
 *
 *	description: method which manages DevFailed exceptions
 */
//+------------------------------------------------------------------
void SlsJungfrau::manage_devfailed_exception(Tango::DevFailed & in_exception, const std::string & in_caller_method_name)
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
 *	method:	SlsJungfrau::manage_lima_exception
 *
 *	description: method which manages lima exceptions
 */
//+------------------------------------------------------------------
void SlsJungfrau::manage_lima_exception(lima::Exception & in_exception, const std::string & in_caller_method_name)
{
    ERROR_STREAM << in_exception.getErrMsg() << endl;

    // throw exception
    Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                   in_exception.getErrMsg().c_str(),
                                   in_caller_method_name.c_str());
}

/*----- PROTECTED REGION END -----*/	//	SlsJungfrau::namespace_ending
} //	namespace
