#include "AttrViewDhyana6060.h"
#include "Dhyana6060.h"
#include <yat/utils/Logging.h>


namespace Dhyana6060_ns
{

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::AttrViewDhyana6060
//---------------------------------------------------------------------------------------
AttrViewDhyana6060::AttrViewDhyana6060(Tango::DeviceImpl *dev)
    : AttrView(dev)
{
    init();
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::~AttrViewDhyana6060
//---------------------------------------------------------------------------------------
AttrViewDhyana6060::~AttrViewDhyana6060()
{
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::init
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::init()
{
    m_dim.dynamic_attributes_manager().remove_attributes();
    try
    {
        //Create tucamVersion attribute
        {
            std::string name = "tucamVersion";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_version = new StringUserData(name);

            dai.set_user_data(m_dyn_version);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_STRING;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "Tucam Library Version.";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create sensorTemperature attribute
        {
            std::string name = "sensorTemperature";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_sensor_temperature = new DoubleUserData(name);

            dai.set_user_data(m_dyn_sensor_temperature);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = "Celsius";
            dai.tai.format = "%6.2f";
            dai.tai.description = "Get the temperature of the sensor in real time (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create cameraTemperature attribute
        {
            std::string name = "cameraTemperature";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_camera_temperature = new DoubleUserData(name);

            dai.set_user_data(m_dyn_camera_temperature);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = "Celsius";
            dai.tai.format = "%6.2f";
            dai.tai.description = "Real-time access to display device temperature (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create sensorTemperatureTarget attribute
        {
            std::string name = "sensorTemperatureTarget";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_sensor_temperature_target = new DoubleUserData(name);

            dai.set_user_data(m_dyn_sensor_temperature_target);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = "Celsius";
            dai.tai.format = "%6.2f";
            dai.tai.description = "Customizable sensor temperature target value (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create sensorCoolingType attribute
        {
            std::string name = "sensorCoolingType";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_sensor_cooling_type = new EnumUserData(name);

            dai.set_user_data(m_dyn_sensor_cooling_type);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Fan");
            dai.tai.enum_labels.push_back("Water");
            dai.tai.description = "Set the sensor cooling type, support fan cooling and water cooling";

            //Instanciate the read callback (called when the dyn. attr. is read)
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create sensorCooling attribute
        {
            std::string name = "sensorCooling";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_sensor_cooling = new EnumUserData(name);

            dai.set_user_data(m_dyn_sensor_cooling);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Off");
            dai.tai.enum_labels.push_back("On");
            dai.tai.description = "Set the sensor cooling switch (ON/OFF)";

            //Instanciate the read callback (called when the dyn. attr. is read)
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create fanSpeed attribute
        {
            std::string name = "fanSpeed";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_fan_speed = new ULongUserData(name);

            dai.set_user_data(m_dyn_fan_speed);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_USHORT;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%d";
            dai.tai.description = "Set the fan speed gear, support 0~100, default 100, 0 means the fan is off";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create fanType attribute
        {
            std::string name = "fanType";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_fan_type = new EnumUserData(name);

            dai.set_user_data(m_dyn_fan_type);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Automatic");
            dai.tai.enum_labels.push_back("Manual");
            dai.tai.description = "Set the fan control type, support automatic and manual";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_cooling_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_cooling_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create globalGain attribute
        {
            std::string name = "globalGain";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_global_gain = new EnumUserData(name);

            dai.set_user_data(m_dyn_global_gain);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("HDR_16bit");
            dai.tai.description = "Switch sensor gain mode, support:";
            for( size_t i=0 ; i<dai.tai.enum_labels.size() ; i++ )
            {
                dai.tai.description += "- " + dai.tai.enum_labels[i] + "\n";
            }
            dai.tai.description += "There exists more mode but there are not supported yet";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create trigOutputPort attribute
        {
            std::string name = "trigOutputPort";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trig_output_port = new EnumUserData(name);

            dai.set_user_data(m_dyn_trig_output_port);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Port1");
            dai.tai.enum_labels.push_back("Port2");
            dai.tai.enum_labels.push_back("Port3");
            dai.tai.description = "";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_trigger_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_trigger_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create trigOutputKind attribute
        {
            std::string name = "trigOutputKind";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trig_output_kind = new EnumUserData(name);

            dai.set_user_data(m_dyn_trig_output_kind);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Low");
            dai.tai.enum_labels.push_back("High");
            dai.tai.enum_labels.push_back("ExposureStart");
            dai.tai.enum_labels.push_back("GlobalExposure");
            dai.tai.enum_labels.push_back("ReadoutEnd");
            dai.tai.description = "Configure the parameters of the trigger output signal";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_trigger_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_trigger_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create trigOutputWidth attribute
        {
            std::string name = "trigOutputWidth";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trig_output_width = new DoubleUserData(name);

            dai.set_user_data(m_dyn_trig_output_width);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = "us";
            dai.tai.format = "%s";
            dai.tai.description = "Set width value option";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_trigger_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_trigger_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create trigOutputDelay attribute
        {
            std::string name = "trigOutputDelay";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trig_output_delay = new DoubleUserData(name);

            dai.set_user_data(m_dyn_trig_output_delay);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = "us";
            dai.tai.format = "%s";
            dai.tai.description = "Set delay value option";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_trigger_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_trigger_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
        //Create trigOutputEdge attribute
        {
            std::string name = "trigOutputEdge";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trig_output_edge = new EnumUserData(name);

            dai.set_user_data(m_dyn_trig_output_edge);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("Rising");
            dai.tai.enum_labels.push_back("Falling");
            dai.tai.description = "Set edge option value (Rising, Falling)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_trigger_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana6060::write_dynamic_trigger_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrView::init()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::read_dynamic_cooling_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::read_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT)
        {
            std::string reason = "It's currently not allowed to read attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::read_dynamic_cooling_attribute_callback()");
        }


        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::read_dynamic_cooling_attribute_callback");
        }

        if(cbd.dya->get_name() == "sensorTemperature")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double temperature;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getSensorTemperature(temperature);
            user_data->set_value(temperature);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "cameraTemperature")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double temperature;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getCameraTemperature(temperature);
            user_data->set_value(temperature);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "sensorTemperatureTarget")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double temperature;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getSensorTemperatureTarget(temperature);
            user_data->set_value(temperature);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "sensorCoolingType")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned type;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getSensorCoolingType(type);
            user_data->set_value(type);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "fanSpeed")
        {
            ULongUserData* user_data = cbd.dya->get_user_data<ULongUserData>();
            //- set the attribute value
            unsigned speed;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getFanSpeed(speed);
            user_data->set_value(speed);
            cbd.tga->set_value((Tango::DevUShort*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "fanType")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned type;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getFanType(type);
            user_data->set_value(type);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "sensorCooling")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned type;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getSensorCooling(type);
            user_data->set_value(type);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::read_dynamic_cooling_attribute_callback()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::write_dynamic_cooling_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::write_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT
            || state == Tango::RUNNING)
        {
            std::string reason = "It's currently not allowed to write attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::write_dynamic_cooling_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::write_dynamic_cooling_attribute_callback");
        }

        if(cbd.dya->get_name() == "sensorTemperatureTarget")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setSensorTemperatureTarget(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevUShort>(m_device, "sensorTemperatureTarget", val);
        }
        else
        if(cbd.dya->get_name() == "sensorCoolingType")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setSensorCoolingType(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevUShort>(m_device, "sensorCoolingType", val);
        }
        else
        if(cbd.dya->get_name() == "fanSpeed")
        {
            Tango::DevUShort val;
            cbd.tga->get_write_value( val);

            ULongUserData* user_data = cbd.dya->get_user_data<ULongUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setFanSpeed(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevUShort>(m_device, "fanSpeed", val);
        }
        else
        if(cbd.dya->get_name() == "fanType")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setFanType(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevUShort>(m_device, "fanType", val);
        }
        else
        if(cbd.dya->get_name() == "sensorCooling")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setSensorCooling(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "sensorCooling", val);
        }
        
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::write_dynamic_cooling_attribute_callback()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::read_dynamic_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT)
        {
            std::string reason = "It's currently not allowed to read attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::read_dynamic_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::read_dynamic_attribute_callback");
        }

        if(cbd.dya->get_name() == "globalGain")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned global_gain;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getGlobalGain(global_gain);
            user_data->set_value(global_gain);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "tucamVersion")
        {
            StringUserData* user_data = cbd.dya->get_user_data<StringUserData>();
            //- set the attribute value
            std::string version;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTucamVersion(version);
            m_dyn_version->set_value(version);
            cbd.tga->set_value((Tango::DevString*)&user_data->get_value());
        }


    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::read_dynamic_attribute_callback()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::write_dynamic_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
     try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT 
            || state == Tango::RUNNING)
        {
            std::string reason = "It's currently not allowed to write attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::write_dynamic_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::write_dynamic_attribute_callback");
        }

        if(cbd.dya->get_name() == "globalGain")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setGlobalGain(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "globalGain", val);
        }

    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::write_dynamic_attribute_callback()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::read_dynamic_trigger_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT)
        {
            std::string reason = "It's currently not allowed to read attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::read_dynamic_trigger_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::read_dynamic_trigger_attribute_callback");
        }

        if(cbd.dya->get_name() == "trigOutputPort")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned port;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTrigOutputPort(port);
            user_data->set_value(port);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "trigOutputKind")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned kind;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTrigOutputKind(kind);
            user_data->set_value(kind);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "trigOutputWidth")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double width;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTrigOutputWidth(width);
            user_data->set_value(width);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "trigOutputDelay")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double delay;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTrigOutputDelay(delay);
            user_data->set_value(delay);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "trigOutputEdge")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned edge;
            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->getTrigOutputEdge(edge);
            user_data->set_value(edge);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }

    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::read_dynamic_trigger_attribute_callback()");
    }
}

//---------------------------------------------------------------------------------------
// AttrViewDhyana6060::write_dynamic_trigger_attribute_callback
//---------------------------------------------------------------------------------------
void AttrViewDhyana6060::write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
     try
    {
        Tango::DevState state = static_cast<Dhyana6060*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana6060*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT 
            || state == Tango::RUNNING)
        {
            std::string reason = "It's currently not allowed to write attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana6060::write_dynamic_trigger_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana6060::write_dynamic_trigger_attribute_callback");
        }

        if(cbd.dya->get_name() == "trigOutputPort")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setTrigOutputPort(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "trigOutputPort", val);
        }
        else
        if(cbd.dya->get_name() == "trigOutputKind")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setTrigOutputKind(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "trigOutputKind", val);
        }
        else
        if(cbd.dya->get_name() == "trigOutputWidth")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setTrigOutputWidth(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevDouble>(m_device, "trigOutputWidth", val);
        }
        else
        if(cbd.dya->get_name() == "trigOutputDelay")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setTrigOutputDelay(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevDouble>(m_device, "trigOutputDelay", val);
        }
        else
        if(cbd.dya->get_name() == "trigOutputEdge")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana6060*>(m_device)->get_camera()->setTrigOutputEdge(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "trigOutputEdge", val);
        }

    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::write_dynamic_trigger_attribute_callback()");
    }
}

} //namespace