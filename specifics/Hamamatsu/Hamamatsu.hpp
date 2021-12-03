//=============================================================================
//
// file :        Hamamatsu.hpp
//
// description : Include for templates of the Hamamatsu class.
//
// project :	
//
// $Author:  Cedric Castel
//
// $Revision:  $
// $Date:  16/04/2020
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
//		 BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
#ifndef _HAMAMATSU_HPP
#define _HAMAMATSU_HPP

#include <tango.h>

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>

/**
 * @author	$Author:  Cedric Castel
 * @version	$Revision:  $
 */

//using namespace lima::Hamamatsu;
using namespace lima;
using namespace yat4tango;

namespace Hamamatsu_ns
{

//============================================================================================================
// TEMPLATE IMPLEMENTATION
//============================================================================================================
template <class F1, class F2>
void Hamamatsu::create_dynamic_attribute(const std::string &   name                ,
                                         int                   data_type           ,
                                         Tango::AttrDataFormat data_format         ,
                                         Tango::AttrWriteType  access_type         ,
                                         Tango::DispLevel      disp_level          ,
                                         size_t                polling_period_in_ms,
                                         const std::string &   unit                ,
                                         const std::string &   format              ,
                                         const std::string &   desc                ,
                                         F1                    read_callback       ,
                                         F2                    write_callback      ,
                                         yat::Any              user_data           )
{
	DEBUG_STREAM << "Hamamatsu::create_dynamic_attribute() - [BEGIN]" << endl;
	INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << endl;

    ////////////////////////////////////////////////////////////////////////////////////////    
	yat4tango::DynamicAttributeInfo dai;
	dai.dev = this;
	//- specify the dyn. attr.  name
	dai.tai.name = name;

    //- associate the dyn. attr. with its data
    if(!user_data.empty())
    {
    	dai.set_user_data(user_data);
    }
    
	//- describe the dynamic attr we want...
	dai.tai.data_type        = data_type;
	dai.tai.data_format      = data_format;
	dai.tai.writable         = access_type;
	dai.tai.disp_level       = disp_level;
	dai.tai.unit             = unit;
	dai.tai.format           = format;
	dai.tai.description      = desc;
    dai.polling_period_in_ms = polling_period_in_ms;
    dai.cdb                  = false;

	//- cleanup tango db option: cleanup tango db when removing this dyn. attr. (i.e. erase its properties fom db)
	//	dai.cdb = true;
	
	//- instanciate the read callback (called when the dyn. attr. is read)    
	if(access_type == Tango::READ ||access_type == Tango::READ_WRITE)
	{
		dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, read_callback);
	}

	//- instanciate the write callback (called when the dyn. attr. is read)    
	if(access_type == Tango::WRITE ||access_type == Tango::READ_WRITE)
	{
		dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, write_callback);
	}
	
	//- add the dyn. attr. to the device
	m_dim.dynamic_attributes_manager().add_attribute(dai);
	DEBUG_STREAM << "Hamamatsu::create_dynamic_attribute() - [END]" << endl;
}

/********************************************************************************************
 * \brief Fill a dynamic attribute with a information from the plugin
 * \param[in]  T1              TANGO data type (Tango::DevFloat for example)
 * \param[in]  T2              data type of the device
 * \param[out] out_cbd         Tango attribute to update with the new value
 * \param[in]  in_method       Pointer to a plugin get method to call
 * \param[in]  in_caller_name  Class and method name of the caller (for exception management)
 * \param[in]  in_is_enabled_during_running Can we read the attribut during running state ?
*********************************************************************************************/
template< typename T1, typename T2>
void Hamamatsu::read_dynamic_attribute(yat4tango::DynamicAttributeReadCallbackData& out_cbd,
                                       T2 (lima::Hamamatsu::Camera::*in_method)(void),
                                       const std::string & in_caller_name,
                                       const bool in_is_enabled_during_running)
{
    DEBUG_STREAM << in_caller_name << " : " << out_cbd.dya->get_name() << endl;

    try
    {
        const bool      device_was_initialized = m_is_device_initialized;
        Tango::DevState state                  = get_state();

        if ((state == Tango::FAULT && device_was_initialized) || state == Tango::INIT)
        {
            std::string reason = "It is currently not allowed to read attribute ";
            reason += out_cbd.dya->get_name();

            Tango::Except::throw_exception("TANGO_DEVICE_ERROR" ,
                                           reason.c_str()       ,
                                           in_caller_name.c_str());
        }

        //- be sure the pointer to the dyn. attr. is valid
        if(!out_cbd.dya)
        {
            THROW_DEVFAILED("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            in_caller_name.c_str());
        }

        // set the attribute value
        T1 * temp = out_cbd.dya->get_user_data<T1>();

        // if in_is_enabled_during_running is false,
        // during an acquisition, we do not allow the access to the modules to avoid problems.
        // We use the last known value
        bool attribut_is_in_alarm = true;
        
        if((in_is_enabled_during_running) || (state != Tango::RUNNING))
        {       
            T2 data = (m_camera->*in_method)();
            
            *temp = data;
            
            attribut_is_in_alarm = false;
        }

        out_cbd.tga->set_value(temp);
        out_cbd.tga->set_quality((attribut_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          in_caller_name.c_str());
    }
}

/*****************************************************************************************
 * \brief Fill the read dynamic attribute (string) with the plugin informations
 * \param[in]  T1              TANGO data type (Tango::DevString for example)
 * \param[in]  T2              data type of the device (std::string)
 * \param[out] out_cbd         Tango attribute to update with the new value
 * \param[in]  in_method       Pointer to a plugin get method to call
 * \param[in]  in_caller_name  Class and method name of the caller (for exception management)
 * \param[in]  in_is_enabled_during_running Can we read the attribut during running state ?
******************************************************************************************/
template< typename T1, typename T2>
void Hamamatsu::read_dynamic_string_attribute(yat4tango::DynamicAttributeReadCallbackData& out_cbd,
                                              T2 (lima::Hamamatsu::Camera::*in_method)(void),
                                              const std::string & in_caller_name,
                                              const bool in_is_enabled_during_running)
{
    DEBUG_STREAM << in_caller_name << " : " << out_cbd.dya->get_name() << endl;

    try
    {
        const bool      device_was_initialized = m_is_device_initialized;
        Tango::DevState state                  = get_state();

        if ((state == Tango::FAULT && device_was_initialized) || state == Tango::INIT)
        {
            std::string reason = "It is currently not allowed to read attribute ";
            reason += out_cbd.dya->get_name();

            Tango::Except::throw_exception("TANGO_DEVICE_ERROR" ,
                                           reason.c_str()       ,
                                           in_caller_name.c_str());
        }

        //- be sure the pointer to the dyn. attr. is valid
        if(!out_cbd.dya)
        {
            THROW_DEVFAILED("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            in_caller_name.c_str());
        }

        // set the attribute value
        T1 * temp = out_cbd.dya->get_user_data<T1>();

        // if in_is_enabled_during_running is false,
        // during an acquisition, we do not allow the access to the modules to avoid problems.
        // We use the last known value
        bool attribut_is_in_alarm = true;
        
        if((in_is_enabled_during_running) || (state != Tango::RUNNING))
        {       
            T2 data = (m_camera->*in_method)();
            
            strcpy(*temp, data.c_str());
            
            attribut_is_in_alarm = false;
        }

        out_cbd.tga->set_value(temp);
        out_cbd.tga->set_quality((attribut_is_in_alarm) ? Tango::ATTR_ALARM : Tango::ATTR_VALID);
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          in_caller_name.c_str());
    }
}

/********************************************************************************************************
 * \brief Use the write dynamic attribut to set informations in the plugin
 * \param[in]  T1                             TANGO data type (Tango::DevFloat for example)
 * \param[in]  T2                             data type of the device
 * \param[in]  in_cbd                         To get the new Tango value set by the user
 * \param[in]  in_method                      Pointer to a plugin set method to call
 * \param[in]  in_optional_memorized_property Optional memorized property name (NULL if not used)
 *                                            An index will be concatenate. 
 * \param[in]  in_caller_name                 Class and method name of the caller (for exception management)
*********************************************************************************************************/
template< typename T1, typename T2>
void Hamamatsu::write_dynamic_attribute(yat4tango::DynamicAttributeWriteCallbackData & in_cbd,
                                        void (lima::Hamamatsu::Camera::*in_method)(const T2 &),
                                        const char * in_optional_memorized_property,
                                        const std::string & in_caller_name)
{
    DEBUG_STREAM << in_caller_name << " : " << in_cbd.dya->get_name() << endl;

    try
    {
        const bool      device_was_initialized = m_is_device_initialized;
        Tango::DevState state                  = get_state();

        if ((state == Tango::FAULT && device_was_initialized) || (state == Tango::RUNNING))
        {
            std::string reason = "It's currently not allowed to write attribute ";
            reason += in_cbd.dya->get_name();

            Tango::Except::throw_exception("TANGO_DEVICE_ERROR" ,
                                           reason.c_str()       ,
                                           in_caller_name.c_str());
        }

        //- be sure the pointer to the dyn. attr. is valid
        if(!in_cbd.dya)
        {
            THROW_DEVFAILED("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            in_caller_name.c_str());
        }

        // get the write value
        T1 val;
        T2 data;
        in_cbd.tga->get_write_value(val);
        data = val;

        // get the attribute value
        T1 * temp = in_cbd.dya->get_user_data<T1>();

        (m_camera->*in_method)(data);
        *temp = data;

        if(in_optional_memorized_property != NULL)
        {
            std::stringstream tempValue ; // value to store
            std::stringstream tempStream; // property name

            tempValue  << *temp;
            tempStream << in_optional_memorized_property;
    
            yat4tango::PropertyHelper::set_property(this, tempStream.str(), tempValue.str());
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          in_caller_name.c_str());
    }
}

/********************************************************************************************************
 * \brief Use the write dynamic attribut (string) to set informations in the plugin
 * \param[in]  T1                             TANGO data type (Tango::DevString for example)
 * \param[in]  T2                             data type of the device  (std::string)
 * \param[in]  in_cbd                         To get the new Tango value set by the user
 * \param[in]  in_method                      Pointer to a plugin set method to call
 * \param[in]  in_optional_memorized_property Optional memorized property name (NULL if not used)
 *                                            An index will be concatenate. 
 * \param[in]  in_caller_name                 Class and method name of the caller (for exception management)
*********************************************************************************************************/
template< typename T1, typename T2>
void Hamamatsu::write_dynamic_string_attribute(yat4tango::DynamicAttributeWriteCallbackData & in_cbd,
                                               void (lima::Hamamatsu::Camera::*in_method)(const T2 &),
                                               const char * in_optional_memorized_property,
                                               const std::string & in_caller_name)
{
    DEBUG_STREAM << in_caller_name << " : " << in_cbd.dya->get_name() << endl;

    try
    {
        const bool      device_was_initialized = m_is_device_initialized;
        Tango::DevState state                  = get_state();

        if ((state == Tango::FAULT && device_was_initialized) || (state == Tango::RUNNING))
        {
            std::string reason = "It's currently not allowed to write attribute ";
            reason += in_cbd.dya->get_name();

            Tango::Except::throw_exception("TANGO_DEVICE_ERROR" ,
                                           reason.c_str()       ,
                                           in_caller_name.c_str());
        }

        //- be sure the pointer to the dyn. attr. is valid
        if(!in_cbd.dya)
        {
            THROW_DEVFAILED("INTERNAL_ERROR",
                            "unexpected NULL pointer to dynamic attribute",
                            in_caller_name.c_str());
        }

        // get the write value
        T1 val;
        T2 data;
        in_cbd.tga->get_write_value(val);
        data = val;

        // get the attribute value
        T1 * temp = in_cbd.dya->get_user_data<T1>();

        (m_camera->*in_method)(data);
        
        strcpy(*temp, data.c_str());

        if(in_optional_memorized_property != NULL)
        {
            std::stringstream tempValue ; // value to store
            std::stringstream tempStream; // property name

            tempValue  << *temp;
            tempStream << in_optional_memorized_property;
    
            yat4tango::PropertyHelper::set_property(this, tempStream.str(), tempValue.str());
        }
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          in_caller_name.c_str());
    }
}

/**********************************************************************************************************************
 * \brief Use to update a dynamic attribute and the hardware with a property value
 * \param[in]  T1                    TANGO data type for attribute and property variables (Tango::DevFloat for example)
 * \param[in]  in_attribute_name     Name of the attribute linked to the property
 * \param[in]  in_property_name      Name of the property linked to the attribute
 * \param[in]  in_write_method       Pointer on a specific device'set method to call
**********************************************************************************************************************/
template< typename T1>
void Hamamatsu::write_property_in_dynamic_attribute(const std::string & in_attribute_name,
                                                    const std::string & in_property_name ,
                                                    void (Hamamatsu_ns::Hamamatsu::*in_write_method)(yat4tango::DynamicAttributeWriteCallbackData &))
{
    // build the correct attribute and property names
    std::string       attribute_name;
    std::string       property_name ;
    std::stringstream tempStream    ; // built property or attribute name (name + index)

    tempStream.str("");
    tempStream << in_attribute_name;
    attribute_name = tempStream.str();

    tempStream.str("");
    tempStream << in_property_name;
    property_name = tempStream.str();

    INFO_STREAM << "Write tango hardware at Init - " << attribute_name << "." << endl;

    // retrieve the property value using its name
    T1 memorizedValue = yat4tango::PropertyHelper::get_property<T1 >(this, property_name.c_str());

    // retrieve the attribute using its name
	Tango::WAttribute           & attribute     = dev_attr->get_w_attr_by_name(attribute_name.c_str());
    yat4tango::DynamicAttribute & dyn_attribute = m_dim.dynamic_attributes_manager().get_attribute(attribute_name);

    // get the user data
    T1 * user_data = dyn_attribute.get_user_data<T1>();

    // update the attribute user data with the property value
    *user_data = memorizedValue;

    // update the attribute
    attribute.set_write_value(user_data);

    // call the write method of the dynamic attribute
    yat4tango::DynamicAttributeWriteCallbackData cbd;
    cbd.tga = &attribute    ;
    cbd.dya = &dyn_attribute;

    (this->*in_write_method)(cbd);
}

/**********************************************************************************************************************
 * \brief Use to update a dynamic attribute (string) and the hardware with a property value
 * \param[in]  T1                    TANGO data type for attribute and property variables (Tango::DevString)
 * \param[in]  in_attribute_name     Name of the attribute linked to the property
 * \param[in]  in_property_name      Name of the property linked to the attribute
 * \param[in]  in_write_method       Pointer on a specific device'set method to call
**********************************************************************************************************************/
template< typename T1>
void Hamamatsu::write_property_in_dynamic_string_attribute(const std::string & in_attribute_name,
                                                           const std::string & in_property_name ,
                                                           void (Hamamatsu_ns::Hamamatsu::*in_write_method)(yat4tango::DynamicAttributeWriteCallbackData &))
{
    // build the correct attribute and property names
    std::string       attribute_name;
    std::string       property_name ;
    std::stringstream tempStream    ; // built property or attribute name (name + index)

    tempStream.str("");
    tempStream << in_attribute_name;
    attribute_name = tempStream.str();

    tempStream.str("");
    tempStream << in_property_name;
    property_name = tempStream.str();

    INFO_STREAM << "Write tango hardware at Init - " << attribute_name << "." << endl;

    // retrieve the property value using its name
    std::string memorizedValue = yat4tango::PropertyHelper::get_property<std::string >(this, property_name.c_str());

    // retrieve the attribute using its name
	Tango::WAttribute           & attribute     = dev_attr->get_w_attr_by_name(attribute_name.c_str());
    yat4tango::DynamicAttribute & dyn_attribute = m_dim.dynamic_attributes_manager().get_attribute(attribute_name);

    // get the user data
    T1 * user_data = dyn_attribute.get_user_data<T1>();

    // update the attribute user data with the property value
    strcpy(*user_data, memorizedValue.c_str());

    // update the attribute
    attribute.set_write_value(user_data);

    // call the write method of the dynamic attribute
    yat4tango::DynamicAttributeWriteCallbackData cbd;
    cbd.tga = &attribute    ;
    cbd.dya = &dyn_attribute;

    (this->*in_write_method)(cbd);
}

}	// namespace_ns

#endif	// _HAMAMATSU_H
