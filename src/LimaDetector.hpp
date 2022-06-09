//=============================================================================
//! 
//  \file   LimaDetector.hpp
//  \brief  class LimaDetector
//  \author Arafat NOUREDDINE
// 
//=============================================================================
#ifndef _LimaDetector_HPP
#define _LimaDetector_HPP

//- TANGO
#include <tango.h>

///////////////////////////////////////////////////////////////////////////////
//// TEMPLATE IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////    
namespace LimaDetector_ns
{

template <class F1, class F2>
void LimaDetector::create_attribute(std::string name,
        int data_type,
        Tango::AttrDataFormat data_format ,
        Tango::AttrWriteType access_type,
        Tango::DispLevel    disp_level,
        const std::string& unit,
        const std::string& format,
        const std::string& desc,
        F1 read_callback,
        F2 write_callback)
{
    DEBUG_STREAM << "LimaDetector::create_attribute() - [BEGIN]" << endl;
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
    //- cleanup tango db option: cleanup tango db when removing this dyn. attr. (i.e. erase its properties fom db)
    //	dai.cdb = true;

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
    DEBUG_STREAM << "LimaDetector::create_attribute() - [END]" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////  
template <class F1>
void LimaDetector::create_command(std::string name,
        long in_type,
        long out_type,
        Tango::DispLevel    disp_level,
        F1 execute_callback)
{
    DEBUG_STREAM << "LimaDetector::create_command() - [BEGIN]" << endl;
    INFO_STREAM << "\t- Create dynamic command [" << name << "]" << endl;

    //- populate the command info data struct
    yat4tango::DynamicCommandInfo dci;

    //- the device to hosting the dynamic interface we are building
    dci.dev = this;
    dci.tci.cmd_name = name;
    dci.tci.in_type  = in_type;
    dci.tci.out_type = out_type;
    //- operator command
    dci.tci.disp_level = disp_level;
    //- instanciate the execute callback (called when the dyn. attr. is read)
    dci.ecb = yat4tango::DynamicCommandExecuteCallback::instanciate(*this,	execute_callback);

    //- add the dyn. attr. to the device
    m_dim.dynamic_commands_manager().add_command(dci);
    DEBUG_STREAM << "LimaDetector::create_command() - [END]" << endl;
}
////////////////////////////////////////////////////////////////////////////////////////  
}

#endif //
