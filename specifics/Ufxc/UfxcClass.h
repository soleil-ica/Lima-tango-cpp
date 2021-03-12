//=============================================================================
//
// file :         UfxcClass.h
//
// description :  Include for the UfxcClass root class.
//                This class is the singleton class for
//                the Ufxc device class.
//                It contains all properties and methods which the 
//                Ufxc requires only once e.g. the commands.
//			
// project :      TANGO Device Server
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
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#ifndef _UFXCCLASS_H
#define _UFXCCLASS_H

#ifdef WIN32
#include "tango.h"
#endif
#include <Ufxc.h>

#ifndef WIN32
#include "tango.h"
#endif

namespace Ufxc_ns
{//=====================================
//	Define classes for attributes
//=====================================
class countingModeAttrib: public Tango::Attr
{
public:
	countingModeAttrib():Attr("countingMode", Tango::DEV_STRING, Tango::READ_WRITE) {};
	~countingModeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_countingMode(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Ufxc *>(dev))->write_countingMode(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_countingMode_allowed(ty);}
};

class geometricalCorrectionAttrib: public Tango::Attr
{
public:
	geometricalCorrectionAttrib():Attr("geometricalCorrection", Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~geometricalCorrectionAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_geometricalCorrection(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Ufxc *>(dev))->write_geometricalCorrection(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_geometricalCorrection_allowed(ty);}
};

class triggerAcquisitionFrequencyAttrib: public Tango::Attr
{
public:
	triggerAcquisitionFrequencyAttrib():Attr("triggerAcquisitionFrequency", Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~triggerAcquisitionFrequencyAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_triggerAcquisitionFrequency(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Ufxc *>(dev))->write_triggerAcquisitionFrequency(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_triggerAcquisitionFrequency_allowed(ty);}
};

class thresholdHigh2Attrib: public Tango::Attr
{
public:
	thresholdHigh2Attrib():Attr("thresholdHigh2", Tango::DEV_ULONG, Tango::READ) {};
	~thresholdHigh2Attrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdHigh2(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdHigh2_allowed(ty);}
};

class thresholdLow2Attrib: public Tango::Attr
{
public:
	thresholdLow2Attrib():Attr("thresholdLow2", Tango::DEV_ULONG, Tango::READ) {};
	~thresholdLow2Attrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdLow2(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdLow2_allowed(ty);}
};

class thresholdHigh1Attrib: public Tango::Attr
{
public:
	thresholdHigh1Attrib():Attr("thresholdHigh1", Tango::DEV_ULONG, Tango::READ) {};
	~thresholdHigh1Attrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdHigh1(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdHigh1_allowed(ty);}
};

class thresholdLow1Attrib: public Tango::Attr
{
public:
	thresholdLow1Attrib():Attr("thresholdLow1", Tango::DEV_ULONG, Tango::READ) {};
	~thresholdLow1Attrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdLow1(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdLow1_allowed(ty);}
};

class thresholdHighAttrib: public Tango::Attr
{
public:
	thresholdHighAttrib():Attr("thresholdHigh", Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~thresholdHighAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdHigh(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Ufxc *>(dev))->write_thresholdHigh(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdHigh_allowed(ty);}
};

class thresholdLowAttrib: public Tango::Attr
{
public:
	thresholdLowAttrib():Attr("thresholdLow", Tango::DEV_FLOAT, Tango::READ_WRITE) {};
	~thresholdLowAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_thresholdLow(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Ufxc *>(dev))->write_thresholdLow(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_thresholdLow_allowed(ty);}
};

class detectorTemperatureAttrib: public Tango::Attr
{
public:
	detectorTemperatureAttrib():Attr("detectorTemperature", Tango::DEV_ULONG, Tango::READ) {};
	~detectorTemperatureAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_detectorTemperature(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_detectorTemperature_allowed(ty);}
};

class currentConfigFileAttrib: public Tango::Attr
{
public:
	currentConfigFileAttrib():Attr("currentConfigFile", Tango::DEV_STRING, Tango::READ) {};
	~currentConfigFileAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_currentConfigFile(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_currentConfigFile_allowed(ty);}
};

class currentAliasAttrib: public Tango::Attr
{
public:
	currentAliasAttrib():Attr("currentAlias", Tango::DEV_STRING, Tango::READ) {};
	~currentAliasAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_currentAlias(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_currentAlias_allowed(ty);}
};

class firmwareVersionAttrib: public Tango::Attr
{
public:
	firmwareVersionAttrib():Attr("firmwareVersion", Tango::DEV_STRING, Tango::READ) {};
	~firmwareVersionAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_firmwareVersion(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_firmwareVersion_allowed(ty);}
};

class libVersionAttrib: public Tango::Attr
{
public:
	libVersionAttrib():Attr("libVersion", Tango::DEV_STRING, Tango::READ) {};
	~libVersionAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Ufxc *>(dev))->read_libVersion(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Ufxc *>(dev))->is_libVersion_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
class LoadConfigFileClass : public Tango::Command
{
public:
	LoadConfigFileClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	LoadConfigFileClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~LoadConfigFileClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Ufxc *>(dev))->is_LoadConfigFile_allowed(any);}
};



//
// The UfxcClass singleton definition
//

class
#ifdef _TG_WINDOWS_
	__declspec(dllexport)
#endif
	UfxcClass : public Tango::DeviceClass
{
public:
//	properties member data

//	add your own data members here
//------------------------------------

public:
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static UfxcClass *init(const char *);
	static UfxcClass *instance();
	~UfxcClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	UfxcClass(string &);
	static UfxcClass *_instance;
	void command_factory();
	void get_class_property();
	void attribute_factory(vector<Tango::Attr *> &);
	void write_class_property();
	void set_default_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace Ufxc_ns

#endif // _UFXCCLASS_H
