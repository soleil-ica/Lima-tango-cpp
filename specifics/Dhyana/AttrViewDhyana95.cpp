#include "AttrViewDhyana95.h"
#include <Dhyana.h>
#include <yat/utils/Logging.h>


namespace Dhyana_ns
{


AttrViewDhyana95::AttrViewDhyana95(Tango::DeviceImpl *dev)
    : AttrView(dev)
{
    init();
}

AttrViewDhyana95::~AttrViewDhyana95()
{
}

void AttrViewDhyana95::init()
{
    m_dim.dynamic_attributes_manager().remove_attributes();
    try
    {
        //Create model attribute
        {
            std::string name = "model";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_model = new StringUserData(name);
            std::string model;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getDetectorModel(model);
            m_dyn_model->set_value(model);
            dai.set_user_data(m_dyn_model);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_STRING;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "The model of the camera. Available values :\n- Dhyana95V1\n- Dhyana95V1\n- Dhyana6060\n";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }

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
            std::string version;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTucamVersion(version);
            m_dyn_version->set_value(version);
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
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
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
            double temperature;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTemperature(temperature);
            m_dyn_sensor_temperature->set_value(temperature);
            dai.set_user_data(m_dyn_sensor_temperature);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "Temperature of the detector (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamique_attribute_callback);
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
            double target;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTemperatureTarget(target);
            m_dyn_sensor_temperature_target->set_value(target);
            dai.set_user_data(m_dyn_sensor_temperature_target);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "Set the Temperature target of the detector (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamique_attribute_callback);
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
            unsigned speed;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getFanSpeed(speed);
            m_dyn_fan_speed->set_value(speed);
            dai.set_user_data(m_dyn_fan_speed);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_USHORT;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "The fan speed of the detector [0..5]";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamique_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }

        //Create globalGain attribute
        /*{
            std::string name = "globalGain";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_global_gain = new EnumUserData(name);
            unsigned gain;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getGlobalGain(gain);
            m_dyn_global_gain->set_value(gain);
            dai.set_user_data(m_dyn_global_gain);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("HDR");
            dai.tai.enum_labels.push_back("HIGH");
            dai.tai.enum_labels.push_back("LOW");
            dai.tai.description = "Define the gain of the detector :\n";
            for( size_t i=0 ; i<dai.tai.enum_labels.size() ; i++ )
            {
                dai.tai.description += "- " + dai.tai.enum_labels[i] + "\n";
            }

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamique_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }*/

        //Create frameRate attribute
        {
            std::string name = "frameRate";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_frame_rate = new DoubleUserData(name);
            double frame_rate;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getFPS(frame_rate);
            m_dyn_frame_rate->set_value(frame_rate);
            dai.set_user_data(m_dyn_frame_rate);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "Get frame rate value";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamique_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }

        /*for (int i = 1; i < 4; i++)
        {
            std::string name = "trigOutputKind" + std::to_string(i);;
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_trigOutputKind = new EnumUserData(name);
            //TucamTriggerMode mode;
            //dynamic_cast<Dhyana*>(m_device)->get_camera()->getTriggerMode(mode);
            dai.set_user_data(m_dyn_model);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::EXPERT;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "Set trigger output mode (ExposureStart, Readout, Global)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_callback_null);
            //Add the dyn. attr. to the device
            m_dim.dynamic_attributes_manager().add_attribute(dai);
        }*/
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

void AttrViewDhyana95::read_dynamique_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana95::read_dynamique_attribute_callback");
        }

        if(cbd.dya->get_name() == "model")
        {
            StringUserData* user_data = cbd.dya->get_user_data<StringUserData>();
            cbd.tga->set_value((Tango::DevString*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "tucamVersion")
        {
            StringUserData* user_data = cbd.dya->get_user_data<StringUserData>();
            cbd.tga->set_value((Tango::DevString*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "sensorTemperature")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double temperature;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTemperature(temperature);
            user_data->set_value(temperature);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "sensorTemperatureTarget")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double target;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTemperatureTarget(target);
            user_data->set_value(target);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "fanSpeed")
        {
            ULongUserData* user_data = cbd.dya->get_user_data<ULongUserData>();
            //- set the attribute value
            unsigned speed;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getFanSpeed(speed);
            user_data->set_value(speed);
            cbd.tga->set_value((Tango::DevUShort*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "globalGain")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned gain;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getGlobalGain(gain);
            user_data->set_value(gain);
            cbd.tga->set_value((Tango::DevEnum*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "frameRate")
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            //- set the attribute value
            double frame_rate;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getFPS(frame_rate);
            user_data->set_value(frame_rate);
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrView::read_dynamique_attribute_callback()");
    }
}

void AttrViewDhyana95::write_dynamique_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
    try
    {
        std::cout << "I was here\n";
        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana95::read_dynamique_attribute_callback");
        }
        std::cout << cbd.dya->get_name();
        if(cbd.dya->get_name() == "sensorTemperatureTarget")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setTemperatureTarget(val);
        }
        else
        if(cbd.dya->get_name() == "fanSpeed")
        {
           Tango::DevULong val;
            cbd.tga->get_write_value( val);

            ULongUserData* user_data = cbd.dya->get_user_data<ULongUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setFanSpeed(val);
        }
        else
        if(cbd.dya->get_name() == "globalGain")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setGlobalGain(val);
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrView::read_dynamique_attribute_callback()");
    }
}

} //namespace