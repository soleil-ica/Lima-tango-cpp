#include "AttrViewDhyana6060.h"
#include "Dhyana6060.h"
#include <yat/utils/Logging.h>


namespace Dhyana6060_ns
{


AttrViewDhyana6060::AttrViewDhyana6060(Tango::DeviceImpl *dev)
    : AttrView(dev)
{
    init();
}

AttrViewDhyana6060::~AttrViewDhyana6060()
{
}

void AttrViewDhyana6060::init()
{
    m_dim.dynamic_attributes_manager().remove_attributes();
    try
    {
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
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana6060::read_dynamic_attribute_callback);
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
                            "AttrViewDhyana6060::read_dynamique_attribute_callback");
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
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::read_dynamique_attribute_callback()");
    }
}

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
                            "AttrViewDhyana6060::read_dynamique_attribute_callback");
        }

    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana6060::read_dynamique_attribute_callback()");
    }
}

} //namespace