/*************************************************************************
/*! 
 *  \file   RoiCounters.hpp
 *  \brief  class RoiCounters
 *  \author Arafat NOUREDDINE
 */
/*************************************************************************/
#ifndef _ROICOUNTERS_HPP
#define _ROICOUNTERS_HPP

//- TANGO
#include <tango.h>
#include <yat/time/Timer.h>

///////////////////////////////////////////////////////////////////////////////
//// TEMPLATE IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////    
namespace RoiCounters_ns
{
template <class F1, class F2>
void RoiCounters::create_attribute(std::string name,
        int data_type,
        Tango::AttrDataFormat data_format ,
        Tango::AttrWriteType access_type,
        Tango::DispLevel disp_level,
        const std::string& unit,
        const std::string& format,
        const std::string& desc,
        F1 read_callback,
        F2 write_callback,
        yat::Any user_data)
{
    DEBUG_STREAM << "RoiCounters::create_attribute() - [BEGIN]" << endl;
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
    dai.tai.data_type = data_type;
    dai.tai.data_format = data_format;
    if(data_format == Tango::SPECTRUM) dai.tai.max_dim_x = 1000000; //- arbitrary big value
    dai.tai.writable = access_type;
    dai.tai.disp_level = disp_level;
    dai.tai.unit = unit;
    dai.tai.format = format;
    dai.tai.description = desc;
    //- cleanup tango db option: cleanup tango db when removing this dyn. attr. (i.e. erase its properties fom db)
    //	dai.cdb = true;


    //- instanciate the read callback (called when the dyn. attr. is read)    
    if(access_type == Tango::READ || access_type == Tango::READ_WRITE)
    {
        dai.rcb = yat4tango::DynamicAttributeReadCallback::instanciate(*this, read_callback);
    }

    //- instanciate the write callback (called when the dyn. attr. is read)    
    if(access_type == Tango::WRITE || access_type == Tango::READ_WRITE)
    {
        dai.wcb = yat4tango::DynamicAttributeWriteCallback::instanciate(*this, write_callback);
    }

    //- add the dyn. attr. to the device
    DEBUG_STREAM << "\t- add the dyn. attr. to the device [" << this << "]" << endl;
    m_dim.dynamic_attributes_manager().add_attribute(dai);
    DEBUG_STREAM << "RoiCounters::create_attribute() - [END]" << endl;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
template <typename T>
Data RoiCounters::copy_roi_from_image(Data& image_data, int roi_num)
{
    yat::Timer t1;    
    Data image_data_roi;
    image_data_roi.type = image_data.type;
    image_data_roi.frameNumber = image_data.frameNumber;
    image_data_roi.timestamp = image_data.timestamp;
    image_data_roi.header = image_data.header;  
    image_data_roi.dimensions = image_data.dimensions;    
    image_data_roi.dimensions[WIDTH_INDEX] = attr_width_arrays[roi_num];  
    image_data_roi.dimensions[HEIGHT_INDEX] = attr_height_arrays[roi_num];  
    image_data_roi.buffer = new Buffer(attr_width_arrays[roi_num] * attr_height_arrays[roi_num] * sizeof(T));
    
    DEBUG_STREAM << "\n******************************************************"           << endl;
    DEBUG_STREAM << "roi image depth = "     << image_data_roi.depth()                   << endl;
    DEBUG_STREAM << "sizeof(T) = "           << sizeof(T)                                << endl;    
    DEBUG_STREAM << "roi x = "               << attr_x_arrays[roi_num]                   << endl;
    DEBUG_STREAM << "roi width = "           << attr_width_arrays[roi_num]               << endl;
    DEBUG_STREAM << "roi y = "               << attr_y_arrays[roi_num]                   << endl;
    DEBUG_STREAM << "roi height = "          << attr_height_arrays[roi_num]              << endl;    
    DEBUG_STREAM << "\n******************************************************"           << endl;

    for(int i = attr_y_arrays[roi_num], j = 0; i < attr_y_arrays[roi_num] + attr_height_arrays[roi_num]; i++, j++)
    {
        int chunk = attr_width_arrays[roi_num] * sizeof(T);
        memcpy( ((char*)(image_data_roi.data()) + chunk * j),
                ((char*)(image_data.data()) + image_data.dimensions[WIDTH_INDEX] * i * sizeof(T) + attr_x_arrays[roi_num] * sizeof(T)),
                chunk);
    }
    DEBUG_STREAM << "\t- duration memcpy roi from image : " << t1.elapsed_msec() << " (ms)" << std::endl;    
    return image_data_roi;
}

}

#endif // _ROICOUNTERS_H
