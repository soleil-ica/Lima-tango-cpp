#include "AttrViewDhyana4040.h"
#include <Dhyana.h>
#include <yat/utils/Logging.h>


namespace Dhyana_ns
{

//-----------------------------------------------------
//AttrViewDhyana4040::AttrViewDhyana4040()
//-----------------------------------------------------
AttrViewDhyana4040::AttrViewDhyana4040(Tango::DeviceImpl *dev)
    : AttrView(dev)
{
    init();
}

//-----------------------------------------------------
//AttrViewDhyana4040::~AttrViewDhyana4040()
//-----------------------------------------------------
AttrViewDhyana4040::~AttrViewDhyana4040()
{
}

//-----------------------------------------------------
//AttrViewDhyana4040::init()
//-----------------------------------------------------
void AttrViewDhyana4040::init()
{
    try
    {
        //Create tecMode attribute
        {
            std::string name = "tecMode";
            INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << std::endl;       
            yat4tango::DynamicAttributeInfo dai;
            dai.dev = m_device;
            //- specify the dyn. attr.  name
            dai.tai.name = name;
            //- associate the dyn. attr. with its data 
            m_dyn_tec_mode = new EnumUserData(name);
            dai.set_user_data(m_dyn_tec_mode);
            //Describe the dynamic attr
            dai.tai.data_type = Tango::DEV_ENUM;
            dai.tai.data_format = Tango::SCALAR;
            dai.tai.writable = Tango::READ_WRITE;
            dai.tai.disp_level = Tango::OPERATOR;
            dai.tai.unit = " ";
            dai.tai.format = "%s";
            dai.tai.enum_labels.push_back("OFF");
            dai.tai.enum_labels.push_back("ON");
            dai.tai.description = "Set tec mode OFF or ON (default is OFF) ";

            //Instanciate the read callback (called when the dyn. attr. is read)    
            dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, &AttrViewDhyana4040::read_dynamic_attribute_callback);
            //Instanciate the write callback
            dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, &AttrViewDhyana4040::write_dynamic_attribute_callback);
            //Do not clear attribute properties
            dai.cdb = false;
            //Add the dyn. attr. to the device
            m_dim->dynamic_attributes_manager().add_attribute(dai);
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana4040::init()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana4040::read_dynamic_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana4040::read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
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
                                        "AttrViewDhyana4040::read_dynamic_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana4040::read_dynamique_attribute_callback");
        }
        if(cbd.dya->get_name() == "tecMode")
        {
            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            //- set the attribute value
            unsigned tec_mode;
            dynamic_cast<Dhyana*>(m_device)->get_camera()->getTecMode(tec_mode);
            user_data->set_value(tec_mode);
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
                                        "AttrViewDhyana4040::read_dynamique_attribute_callback()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana4040::write_dynamic_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana4040::write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
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
                                        "AttrViewDhyana4040::write_dynamic_attribute_callback()");
        }

        // be sure that the pointer to the dyn. attr. is valid
        if(!cbd.dya)
        {
            Tango::Except::throw_exception("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            "AttrViewDhyana4040::write_dynamic_attribute_callback");
        }
        if(cbd.dya->get_name() == "tecMode")
        {
            Tango::DevEnum val;
            cbd.tga->get_write_value( val);

            EnumUserData* user_data = cbd.dya->get_user_data<EnumUserData>();
            user_data->set_value(val);

            dynamic_cast<Dhyana*>(m_device)->get_camera()->setTecMode(val);
            yat4tango::PropertyHelper::set_memorized_attribute<Tango::DevEnum>(m_device, "tecMode", val);
        }
        
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << std::string(df.errors[0].desc) << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                        "TANGO_DEVICE_ERROR",
                                        std::string(df.errors[0].desc).c_str(),
                                        "AttrViewDhyana4040::write_dynamic_attribute_callback()");
    }
}

//-----------------------------------------------------
//AttrViewDhyana4040::read_dynamic_trigger_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana4040::read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd)
{

}

//-----------------------------------------------------
//AttrViewDhyana4040::write_dynamic_trigger_attribute_callback()
//-----------------------------------------------------
void AttrViewDhyana4040::write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd)
{

}

} //namespace