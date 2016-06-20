//=============================================================================
//
// file :         ImXpadClass.h
//
// description :  Include for the ImXpadClass root class.
//                This class is the singleton class for
//                the ImXpad device class.
//                It contains all properties and methods which the 
//                ImXpad requires only once e.g. the commands.
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

#ifndef _MAXIPIXCLASS_H
#define _MAXIPIXCLASS_H

#include <tango.h>
#include <ImXpad.h>


namespace ImXpad_ns
{//=====================================
//	Define classes for attributes
//=====================================
class deviceVersionAttrib: public Tango::Attr
{
public:
	deviceVersionAttrib():Attr("deviceVersion", Tango::DEV_STRING, Tango::READ) {};
	~deviceVersionAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<ImXpad *>(dev))->read_deviceVersion(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<ImXpad *>(dev))->is_deviceVersion_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
//
// The ImXpadClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	ImXpadClass : public Tango::DeviceClass
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
	static ImXpadClass *init(const char *);
	static ImXpadClass *instance();
	~ImXpadClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	ImXpadClass(string &);
	static ImXpadClass *_instance;
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


}	//	namespace ImXpad_ns

#endif // _IMXPADCLASS_H