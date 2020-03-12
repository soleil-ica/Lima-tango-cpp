//=============================================================================
//
// file :        PerkinElmer.h
//
// description : Include for the PerkinElmer class.
//
// project :	Device specific for Perkin Elmer detector
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
#ifndef _PERKINELMER_H
#define _PERKINELMER_H

#include <tango.h>
//using namespace Tango;

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

 //	Add your own constant definitions here.
 //-----------------------------------------------
#include "tango.h"
#include "Factory.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include <PerkinElmerInterface.h>

// Yat4Tango
#include <yat4tango/InnerAppender.h>


#define MAX_ATTRIBUTE_STRING_LENGTH     256


namespace PerkinElmer_ns
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


class PerkinElmer: public TANGO_BASE_CLASS
{
public :
	//	Add your own data members here
	//-----------------------------------------


	//	Here is the Start of the automatic code generation part
	//-------------------------------------------------------------	
/**
 *	@name attributes
 *	Attribute member data.
 */
//@{
		Tango::DevString	*attr_correctionMode_read;
		Tango::DevString	attr_correctionMode_write;
		Tango::DevBoolean	*attr_keepFirstImage_read;
		Tango::DevBoolean	attr_keepFirstImage_write;
		Tango::DevLong	*attr_gain_read;
		Tango::DevLong	attr_gain_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
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
	PerkinElmer(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device Name
 */
	PerkinElmer(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *	@param cl	Class.
 *	@param s 	Device name
 *	@param d	Device description.
 */
	PerkinElmer(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */	
	~PerkinElmer() {delete_device();};
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
 * @name PerkinElmer methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for correctionMode acquisition result.
 */
	virtual void read_correctionMode(Tango::Attribute &attr);
/**
 *	Write correctionMode attribute values to hardware.
 */
	virtual void write_correctionMode(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for keepFirstImage acquisition result.
 */
	virtual void read_keepFirstImage(Tango::Attribute &attr);
/**
 *	Write keepFirstImage attribute values to hardware.
 */
	virtual void write_keepFirstImage(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gain acquisition result.
 */
	virtual void read_gain(Tango::Attribute &attr);
/**
 *	Write gain attribute values to hardware.
 */
	virtual void write_gain(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for correctionMode attribute.
 */
	virtual bool is_correctionMode_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for keepFirstImage attribute.
 */
	virtual bool is_keepFirstImage_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gain attribute.
 */
	virtual bool is_gain_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for StartAcqOffsetImage command.
 */
	virtual bool is_StartAcqOffsetImage_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for StartAcqGainImage command.
 */
	virtual bool is_StartAcqGainImage_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * startAcqOffsetImage: ?
 *	@param	argin	nb frames, integration time
 *	@exception DevFailed
 */
	void	start_acq_offset_image(const Tango::DevVarDoubleArray *);
/**
 * startAcqGainImage: ?
 *	@param	argin	nb frames, integration time
 *	@exception DevFailed
 */
	void	start_acq_gain_image(const Tango::DevVarDoubleArray *);

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

	//	Here is the end of the automatic code generation part
	//-------------------------------------------------------------	



protected :	
	//	Add your own data members here
	//-----------------------------------------

    //state & status stuff
    bool                        m_is_device_initialized ;
    stringstream                m_status_message;
    //lima OBJECTS
	lima::PerkinElmer::Interface*		m_hw;
    lima::CtControl*                    m_ct;
	
	std::string                 m_correction_mode;	//correction mode 	(NO, OFFSET ONLY, OFFSET AND GAIN )
};

}	// namespace_ns

#endif	// _PERKINELMER_H
