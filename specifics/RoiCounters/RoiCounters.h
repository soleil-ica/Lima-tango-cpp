//=============================================================================
//
// file :        RoiCounters.h
//
// description : Include for the RoiCounters class.
//
// project :	Lima
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
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
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _ROICOUNTERS_H
#define _ROICOUNTERS_H


//using namespace Tango;

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

//	Add your own constant definitions here.
//-----------------------------------------------
#include "Factory.h"
#include <tango.h>
#include <yat4tango/DynamicInterfaceManager.h>
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>
#include <yat/threading/Mutex.h>
#include <yat/utils/XString.h>

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include "lima/CtVideo.h"
#include "lima/SoftOpId.h"
#include "lima/SoftOpExternalMgr.h"
#include "processlib/Data.h"
#include "processlib/TaskMgr.h"
#include <map>


#define MAX_ATTRIBUTE_STRING_LENGTH     256
#define MAX_NB_ROICOUNTERS              32
#define CURRENT_VERSION                 "1.2.0"


namespace RoiCounters_ns
{

/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class RoiCounters : public Tango::Device_4Impl
{
public:
    //	Add your own data members here
    //-----------------------------------------


    //	Here is the Start of the automatic code generation part
    //-------------------------------------------------------------	
    /**
     *	@name attributes
     *	Attribute member data.
     */
    //@{
		Tango::DevString	*attr_version_read;
		Tango::DevULong	attr_runLevel_write;
		Tango::DevString	*attr_operationsList_read;
//@}

    /**
     * @name Device properties
     * Device properties member data.
     */
    //@{
/**
 *	Fix the number of Region Of Interest.<br>
 *	Statistical calculations  (sum, average, std, min, max) will be made for these regions of interest.
 */
	Tango::DevULong	nbRoiCounters;
/**
 *	For each Region of Interest . (Origin X)
 */
	vector<long>	__x;
/**
 *	For each Region of Interest . (Origin Y)
 */
	vector<long>	__y;
/**
 *	For each Region of Interest . (Width)
 */
	vector<long>	__width;
/**
 *	For each Region of Interest . (Height)
 */
	vector<long>	__height;
/**
 *	Memorize/Define the runLevel attribute<br>
 */
	Tango::DevULong	memorizedRunLevel;
//@}

    /**
     *	@name Device properties
     *	Device property member data.
     */
    //@{
    //@}

    /**@name Constructors
     * Miscellaneous constructors */
    //@{
    /**
     * Constructs a newly allocated Command object.
     *
     *	@param cl	Class.
     *	@param s 	Device Name
     */
    RoiCounters(Tango::DeviceClass *cl, string &s);
    /**
     * Constructs a newly allocated Command object.
     *
     *	@param cl	Class.
     *	@param s 	Device Name
     */
    RoiCounters(Tango::DeviceClass *cl, const char *s);
    /**
     * Constructs a newly allocated Command object.
     *
     *	@param cl	Class.
     *	@param s 	Device name
     *	@param d	Device description.
     */
    RoiCounters(Tango::DeviceClass *cl, const char *s, const char *d);
    //@}

    /**@name Destructor
     * Only one destructor is defined for this class */
    //@{
    /**
     * The object destructor.
     */
    ~RoiCounters()
    {
        delete_device();
    };
    /**
     *	will be called at device destruction or at init command.
     */
    void delete_device();
    //@}


    /**@name Miscellaneous methods */
    //@{
    /**
     *	Initialize the device
     */
    virtual void init_device();
    /**
     *	Always executed method before execution command method.
     */
    virtual void always_executed_hook();

//@}

/**
 * @name RoiCounters methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for version acquisition result.
 */
	virtual void read_version(Tango::Attribute &attr);
/**
 *	Extract real attribute values for runLevel acquisition result.
 */
	virtual void read_runLevel(Tango::Attribute &attr);
/**
 *	Write runLevel attribute values to hardware.
 */
	virtual void write_runLevel(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for operationsList acquisition result.
 */
	virtual void read_operationsList(Tango::Attribute &attr);
/**
 *	Read/Write allowed for version attribute.
 */
	virtual bool is_version_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for runLevel attribute.
 */
	virtual bool is_runLevel_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for operationsList attribute.
 */
	virtual bool is_operationsList_allowed(Tango::AttReqType type);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

    //	Here is the end of the automatic code generation part
    //-------------------------------------------------------------	
    void update_roi();
    void read_roi();
    void remove_roi(std::string id);

    ///generic methode to copy a region of interest from the image
    template <typename T>
    Data copy_roi_from_image(Data& image_data, int roi_num);

    ///generic method to create a tango dynamic attribute
    template <class F1, class F2>
    void create_attribute(	std::string name,
            int data_type,
            Tango::AttrDataFormat data_format,
            Tango::AttrWriteType access_type,
            Tango::DispLevel disp_level,
            const std::string& unit,
            const std::string& format,
            const std::string& desc,
            F1 read_callback,
            F2 write_callback,
            yat::Any user_data); //put any user data attached to this attribute

    bool create_scalar_dynamic_attributes(void);
    bool create_image_dynamic_attributes(void);
    bool is_device_initialized()
    {
        return m_is_device_initialized;
    };

    //- the dyn. attrs. read callback
    void read_stats_callback (yat4tango::DynamicAttributeReadCallbackData& cbd);

    //- the dyn. attrs. read callback    
    void read_rois_callback (yat4tango::DynamicAttributeReadCallbackData& cbd);

    //- the dyn. attrs. write callback
    void write_rois_callback (yat4tango::DynamicAttributeWriteCallbackData& cbd);

    //- the dyn. attrs. read callback
    void read_image_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    
    /// callback methods for tango dyn attributes - NULL
    void read_callback_null(yat4tango::DynamicAttributeReadCallbackData& cbd)
    {
        /*nop*/
    }

    /// callback methods for tango dyn attributes - NULL
    void write_callback_null(yat4tango::DynamicAttributeWriteCallbackData& cbd)
    {
        /*nop*/
    }

protected:
    //	Add your own data members here
    //-----------------------------------------
    bool            m_is_device_initialized;
    stringstream    m_status_message;

    //LIMA objects
    lima::CtControl*      m_ct;
    lima::SoftOpInstance  m_soft_operation;

    //dynamic attributes objects        
    yat4tango::DynamicInterfaceManager m_dim;
    Tango::DevULong     attr_frameNumber_value;
    Data                m_image_data_roi;
    //at maximum 32 rois counters can be managed    
    std::vector<Tango::DevULong>     attr_x_arrays;
    std::vector<Tango::DevULong>     attr_y_arrays;
    std::vector<Tango::DevULong>     attr_width_arrays;
    std::vector<Tango::DevULong>     attr_height_arrays;
    std::vector<Tango::DevString>    attr_coordinates_arrays;
    std::vector<Tango::DevDouble>    attr_sum_arrays;
    std::vector<Tango::DevDouble>    attr_average_arrays;
    std::vector<Tango::DevDouble>    attr_std_arrays;
    std::vector<Tango::DevDouble>    attr_minValue_arrays;
    std::vector<Tango::DevLong>      attr_minX_arrays;
    std::vector<Tango::DevLong>      attr_minY_arrays;
    std::vector<Tango::DevDouble>    attr_maxValue_arrays;    
    std::vector<Tango::DevLong>      attr_maxX_arrays;
    std::vector<Tango::DevLong>      attr_maxY_arrays;    
    std::vector<std::string>         m_operations_list;

    // Parse the string into 4 numbers and push it into current attributes
    void process_coordinates(Tango::DevString* str,int attrIndex);
} ;

}	// namespace_ns

///////////////////////////////////////////////////////////////////////////////
//// INCLUDE TEMPLATE IMPLEMENTAION
///////////////////////////////////////////////////////////////////////////////    
#include "RoiCounters.hpp"

#endif // _ROICOUNTERS_H
