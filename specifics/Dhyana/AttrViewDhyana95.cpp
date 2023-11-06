#include "AttrViewDhyana95.h"
#include <Dhyana.h>
#include <yat/utils/Logging.h>


namespace Dhyana_ns
{

//-----------------------------------------------------
//AttrViewDhyana95::AttrViewDhyana95()
//-----------------------------------------------------
AttrViewDhyana95::AttrViewDhyana95(Tango::DeviceImpl *dev)
    : AttrView(dev)
{
    init();
}

//-----------------------------------------------------
//AttrViewDhyana95::~AttrViewDhyana95()
//-----------------------------------------------------
AttrViewDhyana95::~AttrViewDhyana95()
{
}

//-----------------------------------------------------
//AttrViewDhyana95::init()
//-----------------------------------------------------
void AttrViewDhyana95::init()
{
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

            dai.set_user_data(m_dyn_model);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_STRING;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.description = "The model of the camera. Available values :\n- Dhyana95V1\n- Dhyana95V2\n- Dhyana6060\n";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
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
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
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
            dai.tai.description = "Temperature of the detector (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
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
            dai.tai.description = "Set the Temperature target of the detector (in Celsius)";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
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
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%d";
            dai.tai.description = "The fan speed of the detector [0..5]";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
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
            dai.tai.enum_labels.push_back("HDR");
            dai.tai.enum_labels.push_back("HIGH");
            dai.tai.enum_labels.push_back("LOW");
            dai.tai.description = "Define the gain of the detector :\n";
            for( size_t i=0 ; i<dai.tai.enum_labels.size() ; i++ )
            {
                dai.tai.description += "- " + dai.tai.enum_labels[i] + "\n";
            }

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
        }

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

            dai.set_user_data(m_dyn_frame_rate);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_DOUBLE;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%6.2f";
            dai.tai.description = "Get frame rate value";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_attribute_callback);
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
        }

        //We do not create trigger out attributes if they're not availbable for the current detector model
        if(dynamic_cast<Dhyana*>(m_device)->get_camera()->is_trigOutput_available())
        {
            for (int i = 1; i < 4; i++)
            {
                std::string name = "trigOutputKind" + std::to_string(i);
                INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
                yat4tango::DynamicAttributeInfo dai;
                dai.dev = m_device;
                //- specify the dyn. attr.  name
                dai.tai.name = name;
                //- associate the dyn. attr. with its data 
                m_dyn_trig_output_kind[i - 1] = new EnumUserData(name);
                dai.set_user_data(m_dyn_trig_output_kind[i - 1]);
                //Describe the dynamic attr
                dai.tai.data_type = Tango::DEV_ENUM;
                dai.tai.data_format = Tango::SCALAR;
                dai.tai.writable = Tango::READ_WRITE;
                dai.tai.disp_level = Tango::EXPERT;
                dai.tai.unit = " ";
                dai.tai.format = "%s";
                dai.tai.enum_labels.push_back("ExposureStart");
                dai.tai.enum_labels.push_back("Global");
                dai.tai.enum_labels.push_back("Readout");
                dai.tai.description = "Set trigger output mode on channel " + std::to_string(i) + ":\n";
                for( size_t i=0 ; i<dai.tai.enum_labels.size() ; i++ )
                {
                    dai.tai.description += "- " + dai.tai.enum_labels[i] + "\n";
                }

                //Instanciate the read callback (called when the dyn. attr. is read)    
                dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_trigger_attribute_callback);
                //Instanciate the write callback
                dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_trigger_attribute_callback);
                //Do not clear attribute properties
                dai.cdb = false;
                //Add the dyn. attr. to the device
                m_dim->dynamic_attributes_manager().add_attribute(dai);
            }

            for (int i = 1; i < 4; i++)
            {
                std::string name = "trigOutputWidth" + std::to_string(i);
                INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
                yat4tango::DynamicAttributeInfo dai;
                dai.dev = m_device;
                //- specify the dyn. attr.  name
                dai.tai.name = name;
                //- associate the dyn. attr. with its data 
                m_dyn_trig_output_width[i - 1] = new DoubleUserData(name);

                dai.set_user_data(m_dyn_trig_output_width[i - 1]);
                //Describe the dynamic attr
                dai.tai.data_type = Tango::DEV_DOUBLE;
                dai.tai.data_format = Tango::SCALAR;
                dai.tai.writable = Tango::READ_WRITE;
                dai.tai.disp_level = Tango::EXPERT;
                dai.tai.unit = "ms";
                dai.tai.format = "%s";
                dai.tai.description = "Set width value option on channel " + std::to_string(i);

                //Instanciate the read callback (called when the dyn. attr. is read)    
                dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_trigger_attribute_callback);
                //Instanciate the write callback
                dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_trigger_attribute_callback);
                //Do not clear attribute properties
                dai.cdb = false;
                //Add the dyn. attr. to the device
                m_dim->dynamic_attributes_manager().add_attribute(dai);
            }

            for (int i = 1; i < 4; i++)
            {
                std::string name = "trigOutputDelay" + std::to_string(i);
                INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
                yat4tango::DynamicAttributeInfo dai;
                dai.dev = m_device;
                //- specify the dyn. attr.  name
                dai.tai.name = name;
                //- associate the dyn. attr. with its data 
                m_dyn_trig_output_delay[i - 1] = new DoubleUserData(name);

                dai.set_user_data(m_dyn_trig_output_delay[i - 1]);
                //Describe the dynamic attr
                dai.tai.data_type = Tango::DEV_DOUBLE;
                dai.tai.data_format = Tango::SCALAR;
                dai.tai.writable = Tango::READ_WRITE;
                dai.tai.disp_level = Tango::EXPERT;
                dai.tai.unit = "ms";
                dai.tai.format = "%s";
                dai.tai.description = "Set delay value option on channel " + std::to_string(i);

                //Instanciate the read callback (called when the dyn. attr. is read)    
                dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_trigger_attribute_callback);
                //Instanciate the write callback
                dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_trigger_attribute_callback);
                //Do not clear attribute properties
                dai.cdb = false;
                //Add the dyn. attr. to the device
                m_dim->dynamic_attributes_manager().add_attribute(dai);
            }

            for (int i = 1; i < 4; i++)
            {
                std::string name = "trigOutputEdge" + std::to_string(i);
                INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
                yat4tango::DynamicAttributeInfo dai;
                dai.dev = m_device;
                //- specify the dyn. attr.  name
                dai.tai.name = name;
                //- associate the dyn. attr. with its data 
                m_dyn_trig_output_edge[i - 1] = new EnumUserData(name);

                dai.set_user_data(m_dyn_trig_output_edge[i - 1]);
                //Describe the dynamic attr
                dai.tai.data_type = Tango::DEV_ENUM;
                dai.tai.data_format = Tango::SCALAR;
                dai.tai.writable = Tango::READ_WRITE;
                dai.tai.disp_level = Tango::EXPERT;
                dai.tai.unit = " ";
                dai.tai.format = "%s";
                dai.tai.enum_labels.push_back("RISING");
                dai.tai.enum_labels.push_back("FALLING");
                dai.tai.description = "Set edge option value on channel " + std::to_string(i) + ":\n";
                for( size_t i=0 ; i<dai.tai.enum_labels.size() ; i++ )
                {
                    dai.tai.description += "- " + dai.tai.enum_labels[i] + "\n";
                }

                //Instanciate the read callback (called when the dyn. attr. is read)    
                dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana95::read_dynamic_trigger_attribute_callback);
                //Instanciate the write callback
                dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana95::write_dynamic_trigger_attribute_callback);
                //Do not clear attribute properties
                dai.cdb = false;
                //Add the dyn. attr. to the device
                m_dim->dynamic_attributes_manager().add_attribute(dai);
            }
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

//-----------------------------------------------------
//AttrViewDhyana95::read_dynamic_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana95::read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT)
        {
            std::string reason = "It's currently not allowed to read attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana95::read_dynamic_attribute_callback()");
        }


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
            //- set the attribute value
            std::string model;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getDetectorModel(model);
            m_dyn_model->set_value(model);
            cbd.tga->set_value((Tango::DevString*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_name() == "tucamVersion")
        {
            StringUserData* user_data = cbd.dya->get_user_data<StringUserData>();
            //- set the attribute value
            std::string version;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTucamVersion(version);
            m_dyn_version->set_value(version);
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
            double temperature;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTemperature(temperature);
            m_dyn_sensor_temperature->set_value(temperature);
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
            unsigned global_gain;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getGlobalGain(global_gain);
            user_data->set_value(global_gain);
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
                                        "AttrViewDhyana95::read_dynamique_attribute_callback()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana95::write_dynamic_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana95::write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT
            || state == Tango::RUNNING)
        {
            std::string reason = "It's currently not allowed to write attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana95::write_dynamic_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana95::write_dynamic_attribute_callback");
        }
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
            Tango::DevUShort val;
            cbd.tga->get_write_value( val);

            ULongUserData* user_data = cbd.dya->get_user_data<ULongUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setFanSpeed(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevUShort>(m_device, "fanSpeed", val);
        }
        else
        if(cbd.dya->get_name() == "globalGain")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setGlobalGain(static_cast<GlobalGain>(val));
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
                                        "AttrViewDhyana95::write_dynamic_attribute_callback()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana95::read_dynamic_trigger_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana95::read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{
    try
    {
        Tango::DevState state = static_cast<Dhyana*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT)
        {
            std::string reason = "It's currently not allowed to read attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana95::read_dynamic_trigger_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana95::read_dynamic_trigger_attribute_callback");
        }


        if(cbd.dya->get_tango_data_type() == Tango::DEV_DOUBLE)
        {
            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            cbd.tga->set_value((Tango::DevDouble*)&user_data->get_value());
        }
        else
        if(cbd.dya->get_tango_data_type() == Tango::DEV_ENUM)
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
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
                                        "AttrViewDhyana95::read_dynamic_trigger_attribute_callback()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana95::write_dynamic_trigger_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana95::write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{
     try
    {
        Tango::DevState state = static_cast<Dhyana*>(m_device)->get_state();
        bool is_device_initialized = static_cast<Dhyana*>(m_device)->is_device_initialized();
        if ((state == Tango::FAULT && !is_device_initialized)
            || state == Tango::INIT 
            || state == Tango::RUNNING)
        {
            std::string reason = "It's currently not allowed to write attribute " + cbd.dya->get_name();
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                        reason.c_str(),
                                        "AttrViewDhyana95::write_dynamic_trigger_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana95::read_dynamique_attribute_callback");
        }

        std::string attr_name  = cbd.dya->get_name();
        int index = 0;
        //get string containing the 'i'
        std::string str_index = attr_name.substr(attr_name.length() - 1);
        std::stringstream(str_index)>>index;
        attr_name = attr_name.substr(0, attr_name.length() - 1);
        if(attr_name == "trigOutputKind")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setOutputSignal(index - 1, static_cast<lima::Dhyana::Camera::TucamSignal>(m_dyn_trig_output_kind[index - 1]->get_value() + 3),
                                                                            static_cast<lima::Dhyana::Camera::TucamSignalEdge>(m_dyn_trig_output_edge[index - 1]->get_value()),
                                                                            m_dyn_trig_output_delay[index - 1]->get_value(), m_dyn_trig_output_width[index - 1]->get_value());
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum > (m_device, cbd.dya->get_name(), val);
        }
        else
        if(attr_name == "trigOutputWidth")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setOutputSignal(index - 1, static_cast<lima::Dhyana::Camera::TucamSignal>(m_dyn_trig_output_kind[index - 1]->get_value() + 3),
                                                                            static_cast<lima::Dhyana::Camera::TucamSignalEdge>(m_dyn_trig_output_edge[index - 1]->get_value()),
                                                                            m_dyn_trig_output_delay[index - 1]->get_value(), m_dyn_trig_output_width[index - 1]->get_value());
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevDouble > (m_device, cbd.dya->get_name(), val);
        }
        else
        if(attr_name == "trigOutputDelay")
        {
            Tango::DevDouble val;
            cbd.tga->get_write_value( val);

            DoubleUserData* user_data = cbd.dya->get_user_data<DoubleUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setOutputSignal(index - 1, static_cast<lima::Dhyana::Camera::TucamSignal>(m_dyn_trig_output_kind[index - 1]->get_value() + 3),
                                                                            static_cast<lima::Dhyana::Camera::TucamSignalEdge>(m_dyn_trig_output_edge[index - 1]->get_value()),
                                                                            m_dyn_trig_output_delay[index - 1]->get_value(), m_dyn_trig_output_width[index - 1]->get_value());
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevDouble > (m_device, cbd.dya->get_name(), val);
        }
        else
        if(attr_name == "trigOutputEdge")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setOutputSignal(index - 1, static_cast<lima::Dhyana::Camera::TucamSignal>(m_dyn_trig_output_kind[index - 1]->get_value() + 3),
                                                                            static_cast<lima::Dhyana::Camera::TucamSignalEdge>(m_dyn_trig_output_edge[index - 1]->get_value()),
                                                                            m_dyn_trig_output_delay[index - 1]->get_value(), m_dyn_trig_output_width[index - 1]->get_value());
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum > (m_device, cbd.dya->get_name(), val);
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana95::read_dynamique_attribute_callback()");
    }
}

} //namespace