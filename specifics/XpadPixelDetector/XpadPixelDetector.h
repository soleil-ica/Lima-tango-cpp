//=============================================================================
//
// file :        XpadPixelDetector.h
//
// description : Include for the XpadPixelDetector class.
//
// project :	XPAD Pixel Detector from Lima
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
#ifndef _XPADPIXELDETECTOR_H
#define _XPADPIXELDETECTOR_H

#include "tango.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include <XpadInterface.h>
#include <XpadCamera.h>
#include "Factory.h"

//- YAT/YAT4TANGO
#include <yat4tango/PropertyHelper.h>
// #include <yat4tango/InnerAppender.h> Causing a bug during init

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

//	Add your own constant definitions here.
//-----------------------------------------------

using namespace std;

namespace XpadPixelDetector_ns
{

    /**
     * Class Description:
     * This is the Xpad 3.2 (PCIe) Pixel Detector device, which uses Lima
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::RUNNING :
*  Tango::FAULT :
*  Tango::DISABLE :  Xpad is calibrating
 */


    class XpadPixelDetector : public Tango::Device_4Impl
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
		Tango::DevString	attr_acquisitionType_write;
		Tango::DevBoolean	*attr_enableGeometricalCorrection_read;
		Tango::DevBoolean	attr_enableGeometricalCorrection_write;
		Tango::DevBoolean	*attr_enableDoublePixelCorrection_read;
		Tango::DevBoolean	attr_enableDoublePixelCorrection_write;
		Tango::DevDouble	*attr_normalizationFactor_read;
		Tango::DevDouble	attr_normalizationFactor_write;
		Tango::DevULong	attr_init_write;
		Tango::DevULong	attr_shutter_write;
		Tango::DevULong	attr_ovf_write;
		Tango::DevULong	attr_n_write;
		Tango::DevULong	attr_p_write;
		Tango::DevULong	attr_busyOut_write;
		Tango::DevULong	attr_gp1_write;
		Tango::DevULong	attr_gp2_write;
		Tango::DevULong	attr_gp3_write;
		Tango::DevULong	attr_gp4_write;
		Tango::DevULong	*attr_dacl_read;
		Tango::DevULong	*attr_ithl_read;
//@}

        /**
         * @name Device properties
         * Device properties member data.
         */
        //@{
/**
 *	Define the model of the XPAD (architecture)<BR>
 *	Availables models :<BR>
 *	- BACKPLANE<BR>
 *	- IMXPAD_S70<BR>
 *	- IMXPAD_S140<BR>
 *	- IMXPAD_S340<BR>
 *	- IMXPAD_S540<BR>
 */
	string	xpadModel;
/**
 *	Path where the calibration files will be saved, and from where the calibrations will be uploaded via an UploadCalibration command
 */
	string	calibrationPath;
/**
 *	Number of Adjusting iteration for the Calibration
 */
	Tango::DevULong	calibrationAdjustingNumber;
/**
 *	Flag used to enable Xpix library debug
 */
	Tango::DevBoolean	xpixDebug;
/**
 *	Minimum LatencyTime (aka deadtime) in ms.
 */
	Tango::DevDouble	minLatencyTimeMs;
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
        XpadPixelDetector(Tango::DeviceClass *cl, string &s);
        /**
         * Constructs a newly allocated Command object.
         *
         *	@param cl	Class.
         *	@param s 	Device Name
         */
        XpadPixelDetector(Tango::DeviceClass *cl, const char *s);
        /**
         * Constructs a newly allocated Command object.
         *
         *	@param cl	Class.
         *	@param s 	Device name
         *	@param d	Device description.
         */
        XpadPixelDetector(Tango::DeviceClass *cl, const char *s, const char *d);
        //@}

        /**@name Destructor
         * Only one destructor is defined for this class */
        //@{

                /**
         * The object destructor.
         */
        ~XpadPixelDetector()
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
 * @name XpadPixelDetector methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for acquisitionType acquisition result.
 */
	virtual void read_acquisitionType(Tango::Attribute &attr);
/**
 *	Write acquisitionType attribute values to hardware.
 */
	virtual void write_acquisitionType(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for enableGeometricalCorrection acquisition result.
 */
	virtual void read_enableGeometricalCorrection(Tango::Attribute &attr);
/**
 *	Write enableGeometricalCorrection attribute values to hardware.
 */
	virtual void write_enableGeometricalCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for enableDoublePixelCorrection acquisition result.
 */
	virtual void read_enableDoublePixelCorrection(Tango::Attribute &attr);
/**
 *	Write enableDoublePixelCorrection attribute values to hardware.
 */
	virtual void write_enableDoublePixelCorrection(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for normalizationFactor acquisition result.
 */
	virtual void read_normalizationFactor(Tango::Attribute &attr);
/**
 *	Write normalizationFactor attribute values to hardware.
 */
	virtual void write_normalizationFactor(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for init acquisition result.
 */
	virtual void read_init(Tango::Attribute &attr);
/**
 *	Write init attribute values to hardware.
 */
	virtual void write_init(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for shutter acquisition result.
 */
	virtual void read_shutter(Tango::Attribute &attr);
/**
 *	Write shutter attribute values to hardware.
 */
	virtual void write_shutter(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for ovf acquisition result.
 */
	virtual void read_ovf(Tango::Attribute &attr);
/**
 *	Write ovf attribute values to hardware.
 */
	virtual void write_ovf(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for n acquisition result.
 */
	virtual void read_n(Tango::Attribute &attr);
/**
 *	Write n attribute values to hardware.
 */
	virtual void write_n(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for p acquisition result.
 */
	virtual void read_p(Tango::Attribute &attr);
/**
 *	Write p attribute values to hardware.
 */
	virtual void write_p(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for busyOut acquisition result.
 */
	virtual void read_busyOut(Tango::Attribute &attr);
/**
 *	Write busyOut attribute values to hardware.
 */
	virtual void write_busyOut(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gp1 acquisition result.
 */
	virtual void read_gp1(Tango::Attribute &attr);
/**
 *	Write gp1 attribute values to hardware.
 */
	virtual void write_gp1(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gp2 acquisition result.
 */
	virtual void read_gp2(Tango::Attribute &attr);
/**
 *	Write gp2 attribute values to hardware.
 */
	virtual void write_gp2(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gp3 acquisition result.
 */
	virtual void read_gp3(Tango::Attribute &attr);
/**
 *	Write gp3 attribute values to hardware.
 */
	virtual void write_gp3(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for gp4 acquisition result.
 */
	virtual void read_gp4(Tango::Attribute &attr);
/**
 *	Write gp4 attribute values to hardware.
 */
	virtual void write_gp4(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for dacl acquisition result.
 */
	virtual void read_dacl(Tango::Attribute &attr);
/**
 *	Extract real attribute values for ithl acquisition result.
 */
	virtual void read_ithl(Tango::Attribute &attr);
/**
 *	Read/Write allowed for acquisitionType attribute.
 */
	virtual bool is_acquisitionType_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for enableGeometricalCorrection attribute.
 */
	virtual bool is_enableGeometricalCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for enableDoublePixelCorrection attribute.
 */
	virtual bool is_enableDoublePixelCorrection_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for normalizationFactor attribute.
 */
	virtual bool is_normalizationFactor_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for init attribute.
 */
	virtual bool is_init_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for shutter attribute.
 */
	virtual bool is_shutter_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for ovf attribute.
 */
	virtual bool is_ovf_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for n attribute.
 */
	virtual bool is_n_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for p attribute.
 */
	virtual bool is_p_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for busyOut attribute.
 */
	virtual bool is_busyOut_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gp1 attribute.
 */
	virtual bool is_gp1_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gp2 attribute.
 */
	virtual bool is_gp2_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gp3 attribute.
 */
	virtual bool is_gp3_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for gp4 attribute.
 */
	virtual bool is_gp4_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for dacl attribute.
 */
	virtual bool is_dacl_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for ithl attribute.
 */
	virtual bool is_ithl_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for LoadFlatConfig command.
 */
	virtual bool is_LoadFlatConfig_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for LoadAllConfigG command.
 */
	virtual bool is_LoadAllConfigG_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SaveConfigL command.
 */
	virtual bool is_SaveConfigL_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for SaveConfigG command.
 */
	virtual bool is_SaveConfigG_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for LoadConfig command.
 */
	virtual bool is_LoadConfig_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for LoadConfigG command.
 */
	virtual bool is_LoadConfigG_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for Reset command.
 */
	virtual bool is_Reset_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for GetDacl command.
 */
	virtual bool is_GetDacl_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for GetIthl command.
 */
	virtual bool is_GetIthl_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for CalibrateOTNSlow command.
 */
	virtual bool is_CalibrateOTNSlow_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for CalibrateOTNMedium command.
 */
	virtual bool is_CalibrateOTNMedium_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for CalibrateOTNFast command.
 */
	virtual bool is_CalibrateOTNFast_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for CalibrateBEAM command.
 */
	virtual bool is_CalibrateBEAM_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for CalibrateOTN command.
 */
	virtual bool is_CalibrateOTN_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for UploadCalibration command.
 */
	virtual bool is_UploadCalibration_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for UploadWaitTimes command.
 */
	virtual bool is_UploadWaitTimes_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for IncrementITHL command.
 */
	virtual bool is_IncrementITHL_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for DecrementITHL command.
 */
	virtual bool is_DecrementITHL_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * Load a Flat value to all pixels
 *	@param	argin	Flat value to be loaded
 *	@exception DevFailed
 */
	void	load_flat_config(Tango::DevULong);
/**
 * Load the config G(lobal) to a module and a chip
 *	@param	argin	modNum(1..8), chipId(0..6), config_values (11 values)
 *	@exception DevFailed
 */
	void	load_all_config_g(const Tango::DevVarULongArray *);
/**
 * ?
 *	@param	argin	modNum(1..8), calibId(0..6), chipId(0..7), curRow (0..119), values (80 values)
 *	@exception DevFailed
 */
	void	save_config_l(const Tango::DevVarULongArray *);
/**
 * ?
 *	@param	argin	modNum(1..8), calibId(0..6), reg, values (7 values)
 *	@exception DevFailed
 */
	void	save_config_g(const Tango::DevVarULongArray *);
/**
 * ?
 *	@param	argin	modNum(1..8), calibId(0..6)
 *	@exception DevFailed
 */
	void	load_config(const Tango::DevVarULongArray *);
/**
 * Load a value of a wanted config G register.
 *	register IDs are:
 *	CMOS_DSBL_V32  0x01
 *	AMP_TP_V32     0x1F
 *	ITHH_V32       0x33
 *	VADJ_V32       0x35
 *	VREF_V32       0x36
 *	IMFP_V32       0x3b
 *	IOTA_V32       0x3c
 *	IPRE_V32       0x3d
 *	ITHL_V32       0x3e
 *	TUNE_V32      0x3f
 *	IBUFFER_V32    0x40
 *	@param	argin	modNum(1..8), chipId(0..6), register ID, register value
 *	@exception DevFailed
 */
	void	load_config_g(const Tango::DevVarULongArray *);
/**
 * Reset the Xpad
 *	@exception DevFailed
 */
	void	reset();
/**
 * 
 *	@return	array of DACL data
 *	@exception DevFailed
 */
	Tango::DevVarUShortArray	*get_dacl();
/**
 * 
 *	@return	array of ITHL data
 *	@exception DevFailed
 */
	Tango::DevVarUShortArray	*get_ithl();
/**
 * Start the Over The Noise Slow calibration
 *	@exception DevFailed
 */
	void	calibrate_otnslow();
/**
 * Start the Over The Noise Medium calibration
 *	@exception DevFailed
 */
	void	calibrate_otnmedium();
/**
 * Start the Over The Noise Fast calibration
 *	@exception DevFailed
 */
	void	calibrate_otnfast();
/**
 * Start the BEAM calibration
 *	@param	argin	Texp, ithl_max, itune, imfp
 *	@exception DevFailed
 */
	void	calibrate_beam(const Tango::DevVarULongArray *);
/**
 * Start the Over The Noise calibration
 *	@param	argin	itune, imfp
 *	@exception DevFailed
 */
	void	calibrate_otn(const Tango::DevVarULongArray *);
/**
 * Upload a calibration from a directory defined in the property CalibrationPath
 *	@exception DevFailed
 */
	void	upload_calibration();
/**
 * Upload a tralectory of wait times, instead of having always the same value
 *	@param	argin	the wait times
 *	@exception DevFailed
 */
	void	upload_wait_times(const Tango::DevVarULongArray *);
/**
 * Increment the ITHL of 1 unit
 *	@exception DevFailed
 */
	void	increment_ithl();
/**
 * Decrement the ITHL of 1 unit
 *	@exception DevFailed
 */
	void	decrement_ithl();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

        //	Here is the end of the automatic code generation part
        //-------------------------------------------------------------	 
		// return true if the device is correctly initialized in init_device (used by StateMachine.cpp)
		bool is_device_initialized(){return m_is_device_initialized;};

    protected:
        //	Add your own data members here
        //-----------------------------------------

        bool m_is_device_initialized,m_from_init_device;
        stringstream m_status_message;
        void set_general_purpose_params();
		std::string m_xpad_model;
		std::string m_acquisitionType;

        //lima OBJECTS
        Xpad::Interface* m_hw;
        Xpad::Camera* m_camera;
        CtControl* m_ct;
    };

} // namespace_ns

#endif	// _XPADPIXELDETECTOR_H
