/*************************************************************************
/*! 
 *  \file   Xspress3.hpp
 *  \brief  class Xspress3
 *  \author Arafat NOUREDDINE
 */
/*************************************************************************/
#ifndef ATTR_VIEW_HPP
#define ATTR_VIEW_HPP

//- TANGO
#include <tango.h>

///////////////////////////////////////////////////////////////////////////////
//// TEMPLATE IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////    
namespace Xspress3_ns
{

template <class F1, class F2>
void Xspress3::create_attribute(std::string name,
								 int data_type,
								 Tango::AttrDataFormat data_format ,
								 Tango::AttrWriteType access_type,
                                 Tango::DispLevel disp_level,
								 const std::string& unit,
								 const std::string& format,
								 const std::string& desc,
								 F1 read_callback,
								 F2 write_callback,
                                 yat::Any user_data,
                                 unsigned int max_dim_x,    //used ONLY for Tango::SPECTRUM or Tango::IMAGE
                                 unsigned int max_dim_y     //used ONLY for Tango::SPECTRUM or Tango::IMAGE
                                )
{
    DEBUG_STREAM << "Xspress3::create_attribute() - [BEGIN]" << endl;
    INFO_STREAM << "\t- Create dynamic attribute [" << name << "]" << endl;
    ////////////////////////////////////////////////////////////////////////////////////////    
    yat4tango::DynamicAttributeInfo dai;
    dai.dev = this;
    //- specify the dyn. attr.  name
    dai.tai.name = name;
    //- associate the dyn. attr. with its data
    dai.set_user_data(user_data);
    //- describe the dynamic attr we want...
    dai.tai.data_type = data_type;
    dai.tai.data_format = data_format;
    if(data_format == Tango::SPECTRUM)
    {
        dai.tai.max_dim_x = max_dim_x;
    }
    if(data_format == Tango::IMAGE)
    {
        dai.tai.max_dim_x = max_dim_x;    
        dai.tai.max_dim_y = max_dim_y;
    }
    dai.tai.writable = access_type;
    dai.tai.disp_level = disp_level;
    dai.tai.unit = unit;
    dai.tai.format = format;
    dai.tai.description = desc;
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
    DEBUG_STREAM << "\t- add the dyn. attr. to the device [" << this << "]" << endl;
    m_dim.dynamic_attributes_manager().add_attribute(dai);
    DEBUG_STREAM << "Xspress3::create_attribute() - [END]" << endl;
}

}

#endif // ATTR_VIEW_HPP
