/*************************************************************************
/*! 
 *  \file   Mask.hpp
 *  \brief  class Mask
 *  \author Arafat NOUREDDINE
 */
/*************************************************************************/
#ifndef _MASK_HPP
#define _MASK_HPP

//- TANGO
#include <tango.h>
#include <yat/time/Timer.h>

///////////////////////////////////////////////////////////////////////////////
//// TEMPLATE IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////    
namespace Mask_ns
{


//-------------------------------------------------------------------
//-------------------------------------------------------------------
template <typename OUTPUT>
Data Mask::create_data_from_mask(Tango::DevShort* mask_image, long mask_dim_x, long mask_dim_y, Data::TYPE data_type, long data_depth)
{
    INFO_STREAM << "Mask::create_data_from_mask() : [BEGIN]" << endl;
    yat::Timer t1;    
    Data image_data;
    image_data.type = data_type;
    //image_data.frameNumber = image_data.frameNumber;
    //image_data.timestamp = image_data.timestamp;
    //image_data.header = image_data.header;  
    image_data.dimensions.resize(2);    
    image_data.dimensions[WIDTH_INDEX] = mask_dim_x;  
    image_data.dimensions[HEIGHT_INDEX] = mask_dim_y;  
    image_data.buffer = new Buffer(mask_dim_x * mask_dim_y * data_depth);
        
    INFO_STREAM << "Data type = "      << image_data.type                      << endl;
    INFO_STREAM << "Data depth = "     << image_data.depth()                   << endl;    
    INFO_STREAM << "Data Width = "     << image_data.dimensions[WIDTH_INDEX]   << endl;
    INFO_STREAM << "Data Height = "    << image_data.dimensions[HEIGHT_INDEX]  << endl;    

    OUTPUT* dst = (OUTPUT*)image_data.data();
    for(int i = 0; i < mask_dim_y; i++)
    {
        for(int j = 0; j < mask_dim_x; j++)
        {
            dst[i*mask_dim_x + j]  = mask_image[i*mask_dim_x + j];
        }
    }
    
    INFO_STREAM << "duration creating Data image for Mask : " << t1.elapsed_msec() << " (ms)" << std::endl;    
    INFO_STREAM << "Mask::create_data_from_mask() : [END]" << endl;
    return image_data;
}

}

#endif // _MASK_H
