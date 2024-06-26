//=============================================================================
//
// file :        PilatusPixelDetector.h
//
// description : Include for the PilatusPixelDetector class.
//
// project :	
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
//         BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _PILATUSPIXELDETECTOR_H
#define _PILATUSPIXELDETECTOR_H


//using namespace Tango;

/**
 * @author    $Author:  $
 * @version    $Revision:  $
 */

 //    Add your own constant definitions here.
 //-----------------------------------------------

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/InnerAppender.h>

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include <PilatusCamera.h>
#include <PilatusInterface.h>
#include "Factory.h"

#include "tango.h"


#define MAX_ATTRIBUTE_STRING_LENGTH     256

using namespace lima;
using namespace std;
using namespace yat4tango;

namespace PilatusPixelDetector_ns
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


class PilatusPixelDetector: public Tango::Device_4Impl
{
public :
    //    Add your own data members here
    //-----------------------------------------


    //    Here is the Start of the automatic code generation part
    //-------------------------------------------------------------    
/**
 *    @name attributes
 *    Attribute member data.
 */
//@{
		Tango::DevDouble	*attr_energy_read;
		Tango::DevDouble	attr_energy_write;
		Tango::DevLong	*attr_threshold_read;
		Tango::DevLong	attr_threshold_write;
		Tango::DevString	*attr_gain_read;
		Tango::DevString	attr_gain_write;
		Tango::DevString	*attr_imagePath_read;
		Tango::DevString	attr_imagePath_write;
		Tango::DevString	*attr_fileName_read;
		Tango::DevString	attr_fileName_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
/**
 *	Detector port number of CamServer
 */
	Tango::DevLong	detectorPort;
/**
 *	Detector IP address of CamServer
 */
	string	detectorIP;
/**
 *	Detector file containing informations about (model, size, pixeldepth, ...).
 */
	string	detectorCameraDefFileName;
/**
 *	Enable/Disable monitoring of the directory receiving image files in order to read images provided by CamServer & to display image in the attribut image<br>
 *	[default = enable reading directory]
 */
	Tango::DevBoolean	useReader;
/**
 *	This is the elapsed time before declaring that is no available image returned by CamServer during the Acquisition.<br>
 *	[default = 10000 ms]
 */
	Tango::DevULong	readerTimeoutMs;
/**
 *	This is the periodic time Of Reader.<br>
 *	[default = 1000 ms]
 */
	Tango::DevULong	readerPeriodicMs;
/**
 *	Memorize/Define the energy value<br>
 */
	Tango::DevDouble	memorizedEnergy;
/**
 *	Memorize/Define the threshold value<br>
 */
	Tango::DevLong	memorizedThreshold;
/**
 *	Memorize/Define the gain value<br>
 */
	string	memorizedGain;
/**
 *	Memorize/Define the imagePath value<br>
 */
	string	memorizedImagePath;
/**
 *	Memorize/Define the fileName value<br>
 */
	string	memorizedFileName;
//@}

/**
 *    @name Device properties
 *    Device property member data.
 */
//@{
//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device Name
 */
    PilatusPixelDetector(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device Name
 */
    PilatusPixelDetector(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device name
 *    @param d    Device description.
 */
    PilatusPixelDetector(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */    
    ~PilatusPixelDetector() {delete_device();};
/**
 *    will be called at device destruction or at init command.
 */
    void delete_device();
//@}

    
/**@name Miscellaneous methods */
//@{
/**
 *    Initialize the device
 */
    virtual void init_device();
/**
 *    Always executed method before execution command method.
 */
    virtual void always_executed_hook();

//@}

/**
 * @name PilatusPixelDetector methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for energy acquisition result.
 */
	virtual void read_energy(Tango::Attribute &attr);
/**
 *	Write energy attribute values to hardware.
 */
	virtual void write_energy(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for threshold acquisition result.
 */
	virtual void read_threshold(Tango::Attribute &attr);
/**
 *	Write threshold attribute values to hardware.
 */
	virtual void write_threshold(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gain acquisition result.
 */
	virtual void read_gain(Tango::Attribute &attr);
/**
 *	Write gain attribute values to hardware.
 */
	virtual void write_gain(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for imagePath acquisition result.
 */
	virtual void read_imagePath(Tango::Attribute &attr);
/**
 *	Write imagePath attribute values to hardware.
 */
	virtual void write_imagePath(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for fileName acquisition result.
 */
	virtual void read_fileName(Tango::Attribute &attr);
/**
 *	Write fileName attribute values to hardware.
 */
	virtual void write_fileName(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for energy attribute.
 */
	virtual bool is_energy_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for threshold attribute.
 */
	virtual bool is_threshold_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gain attribute.
 */
	virtual bool is_gain_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for imagePath attribute.
 */
	virtual bool is_imagePath_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for fileName attribute.
 */
	virtual bool is_fileName_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for SetEnergy command.
 */
	virtual bool is_SetEnergy_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SetThresholdAndGain command.
 */
	virtual bool is_SetThresholdAndGain_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SetMxSettings command.
 */
	virtual bool is_SetMxSettings_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SendAnyCommand command.
 */
	virtual bool is_SendAnyCommand_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for GetTH command.
 */
	virtual bool is_GetTH_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for DeleteRemainingFiles command.
 */
	virtual bool is_DeleteRemainingFiles_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * Define Energy in eV.
 *	@param	argin	
 *	@exception DevFailed
 */
	void	set_energy(Tango::DevDouble);
/**
 * Define Threshold (eV) and Gain (LOW, MID, HIGH, UHIGH).
 *	@param	argin	
 *	@exception DevFailed
 */
	void	set_threshold_and_gain(const Tango::DevVarLongStringArray *);
/**
 * Set crystallographic parameters reported in the image header. <br>
 *	
 *	[param_name value] [param_name value] ... <br>
 *	
 *	List of availables param_name :<br>
 *	Wavelength, Energy_range, Detector_distance, Detector_Voffset, Beam_xy, <br>
 *	Beam_x, Beam_y, Flux, Filter_transmission, Start_angle, Angle_increment, <br>
 *	Detector_2theta, Polarization, Alpha, Kappa, Phi, Phi_increment, Chi, <br>
 *	Chi_increment, Oscillation_axis, N_oscillations, Start_position, <br>
 *	Position_increment, Shutter_time, CBF_template_file <br>
 *	@param	argin	
 *	@exception DevFailed
 */
	void	set_mx_settings(Tango::DevString);
/**
 * Allow to send any command to Camserver.<br>
 *	See documentation of Pilatus/Camserver.
 *	@param	argin	
 *	@exception DevFailed
 */
	void	send_any_command(Tango::DevString);
/**
 * Read temperature (of nb sensors) and humidity (of nb sensors) of the detector
 *	@return	
 *	@exception DevFailed
 */
	Tango::DevVarDoubleArray	*get_th();
/**
 * Delete Tif remaining Files
 *	@exception DevFailed
 */
	void	delete_remaining_files();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

    //    Here is the end of the automatic code generation part
    //-------------------------------------------------------------    
	// return true if the device is correctly initialized in init_device
	bool is_device_initialized(){return m_is_device_initialized;};


protected :    
    //    Add your own data members here
    //-----------------------------------------

    
    bool                    m_is_device_initialized ;
    stringstream            m_status_message;
    string                  m_gain;    
    
    //LIMA objects
    Pilatus::Interface*     m_hw;
    Pilatus::Camera*        m_camera;
    CtControl*              m_ct;    
};

}    // namespace_ns

#endif    // _PILATUSPIXELDETECTOR_H
