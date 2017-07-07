//=============================================================================
//! 
//  \file   Pco.hpp
//  \brief  class Pco
//  \author FL (Hacked from AN)
// 
//=============================================================================
#ifndef PCO_DEVICE_HPP
#define PCO_DEVICE_HPP

//- TANGO
#include <tango.h>

///////////////////////////////////////////////////////////////////////////////
//// TEMPLATE IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////    
namespace Pco_ns
{

template <class F1, class F2>
void Pco::create_attribute( std::string name,
                            int data_type,
                            Tango::AttrDataFormat data_format ,
                            Tango::AttrWriteType access_type,
                            Tango::DispLevel    disp_level,
                            const std::string& unit,
                            const std::string& format,
                            const std::string& desc,
                            const std::string& label,
                            /*bool memorized,
                            bool write_memorized_value_at_init,*/
                            F1 read_callback,
                            F2 write_callback)
{
    DEBUG_STREAM << "Pco::create_attribute() - [BEGIN]" << endl;
    INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << endl;      
    yat4tango::DynamicAttributeInfo dai;
    dai.dev = this;
    //- specify the dyn. attr.  name
    dai.tai.name = name;
    //    //- associate the dyn. attr. with its data
    //    dai.set_user_data(user);
    //- describe the dynamic attr we want...
    dai.tai.data_type = data_type;
    dai.tai.data_format = data_format;
    dai.tai.writable = access_type;
    dai.tai.disp_level = disp_level;
    dai.tai.unit = unit;
    dai.tai.format = format;
    dai.tai.description = desc;
    dai.tai.label = label;
    //- Not Working:
    /*
    dai.memorized = memorized;
    dai.write_memorized_value_at_init = write_memorized_value_at_init;
    //- cleanup tango db option: cleanup tango db when removing this dyn. attr. (i.e. erase its properties fom db)
    dai.cdb = false;*/

    //- instanciate the read callback (called when the dyn. attr. is read)    
    if (access_type == Tango::READ || access_type == Tango::READ_WRITE)
    {
        dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, read_callback);
    }

    //- instanciate the write callback (called when the dyn. attr. is read)    
    if (access_type == Tango::WRITE || access_type == Tango::READ_WRITE)
    {
        dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, write_callback);
    }

    //- add the dyn. attr. to the device
    m_dim.dynamic_attributes_manager().add_attribute(dai);
    DEBUG_STREAM << "Pco::create_attribute() - [END]" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////  
}

#endif // PCO_DEVICE_HPP