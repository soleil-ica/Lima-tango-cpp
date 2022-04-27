/*************************************************************************/
/*! 
 *  \file   Lambda.hpp
 *  \brief  class Lambda
 *  \author C�dric Castel - SOLEIL (MEDIANE SYSTEME - IT consultant) 
 */
/*************************************************************************/
#ifndef Lambda_HPP
#define Lambda_HPP

//- TANGO
#include <tango.h>

//============================================================================================================
// TEMPLATE IMPLEMENTATION
//============================================================================================================
/*************************************************************************************************************
 * \brief Use to update a static attribute and the hardware with a property value
 * \param[in]  T1                    TANGO data type for read attribute variable (Tango::DevFloat for example)
 * \param[in]  T2                    Data type for memorized property (string for example)
 * \param[in]  in_attribute_name     Name of the attribute linked to the property value
 * \param[out] out_attr_read         Tango attribute member to filled with the data value
 * \param[in]  in_memorized_property Property variable
 * \param[in]  in_write_method       Pointer on a controller method to call to set the data
*************************************************************************************************************/
template< typename T1, typename T2>
void Lambda::write_property_in_static_attribute(const std::string & in_attribute_name,
                                                T1 * out_attr_read,
                                                const T2 & in_memorized_property,
                                                void (Lambda_ns::Lambda::*in_write_method)(Tango::WAttribute &))
{
	INFO_STREAM << "Write tango hardware at Init - " << in_attribute_name << "." << endl;

    *out_attr_read = in_memorized_property;
	Tango::WAttribute & attribute = dev_attr->get_w_attr_by_name(in_attribute_name.c_str());
	attribute.set_write_value(*out_attr_read);
    (this->*in_write_method)(attribute);
}

#endif // Lambda_HPP
