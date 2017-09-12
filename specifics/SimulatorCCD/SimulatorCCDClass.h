//=============================================================================
//
// file :         SimulatorCCDClass.h
//
// description :  Include for the SimulatorCCDClass root class.
//                This class is the singleton class for
//                the SimulatorCCD device class.
//                It contains all properties and methods which the 
//                SimulatorCCD requires only once e.g. the commands.
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

#ifndef _SIMULATORCCDCLASS_H
#define _SIMULATORCCDCLASS_H

#ifdef WIN32
#include <tango.h>
#endif

#include <SimulatorCCD.h>

#ifndef WIN32
#include <tango.h>
#endif

namespace SimulatorCCD_ns
{//=====================================
//	Define classes for attributes
//=====================================
class yOffsetAttrib: public Tango::Attr
{
public:
	yOffsetAttrib():Attr("yOffset", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~yOffsetAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<SimulatorCCD *>(dev))->read_yOffset(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<SimulatorCCD *>(dev))->write_yOffset(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<SimulatorCCD *>(dev))->is_yOffset_allowed(ty);}
};

class xOffsetAttrib: public Tango::Attr
{
public:
	xOffsetAttrib():Attr("xOffset", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~xOffsetAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<SimulatorCCD *>(dev))->read_xOffset(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<SimulatorCCD *>(dev))->write_xOffset(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<SimulatorCCD *>(dev))->is_xOffset_allowed(ty);}
};

class fillTypeAttrib: public Tango::Attr
{
public:
	fillTypeAttrib():Attr("fillType", Tango::DEV_STRING, Tango::READ_WRITE) {};
	~fillTypeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<SimulatorCCD *>(dev))->read_fillType(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<SimulatorCCD *>(dev))->write_fillType(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<SimulatorCCD *>(dev))->is_fillType_allowed(ty);}
};

class growFactorAttrib: public Tango::Attr
{
public:
	growFactorAttrib():Attr("growFactor", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~growFactorAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<SimulatorCCD *>(dev))->read_growFactor(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<SimulatorCCD *>(dev))->write_growFactor(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<SimulatorCCD *>(dev))->is_growFactor_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
//
// The SimulatorCCDClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	SimulatorCCDClass : public Tango::DeviceClass
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
	static SimulatorCCDClass *init(const char *);
	static SimulatorCCDClass *instance();
	~SimulatorCCDClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	SimulatorCCDClass(string &);
	static SimulatorCCDClass *_instance;
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


}	//	namespace SimulatorCCD_ns

#endif // _SIMULATORCCDCLASS_H
