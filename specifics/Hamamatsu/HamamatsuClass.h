//=============================================================================
//
// file :         HamamatsuClass.h
//
// description :  Include for the HamamatsuClass root class.
//                This class is the singleton class for
//                the Hamamatsu device class.
//                It contains all properties and methods which the 
//                Hamamatsu requires only once e.g. the commands.
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

#ifndef _HAMAMATSUCLASS_H
#define _HAMAMATSUCLASS_H

#include <tango.h>
#include <Hamamatsu.h>


namespace Hamamatsu_ns
{//=====================================
//	Define classes for attributes
//=====================================
class channel3KindAttrib: public Tango::Attr
{
public:
	channel3KindAttrib():Attr("channel3Kind", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel3KindAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel3Kind(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel3Kind(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel3Kind_allowed(ty);}
};

class channel2KindAttrib: public Tango::Attr
{
public:
	channel2KindAttrib():Attr("channel2Kind", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel2KindAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel2Kind(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel2Kind(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel2Kind_allowed(ty);}
};

class channel1KindAttrib: public Tango::Attr
{
public:
	channel1KindAttrib():Attr("channel1Kind", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel1KindAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel1Kind(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel1Kind(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel1Kind_allowed(ty);}
};

class channel3PolarityAttrib: public Tango::Attr
{
public:
	channel3PolarityAttrib():Attr("channel3Polarity", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel3PolarityAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel3Polarity(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel3Polarity(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel3Polarity_allowed(ty);}
};

class channel2PolarityAttrib: public Tango::Attr
{
public:
	channel2PolarityAttrib():Attr("channel2Polarity", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel2PolarityAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel2Polarity(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel2Polarity(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel2Polarity_allowed(ty);}
};

class channel1PolarityAttrib: public Tango::Attr
{
public:
	channel1PolarityAttrib():Attr("channel1Polarity", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~channel1PolarityAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_channel1Polarity(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_channel1Polarity(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_channel1Polarity_allowed(ty);}
};

class bottomViewExposureTimeAttrib: public Tango::Attr
{
public:
	bottomViewExposureTimeAttrib():Attr("bottomViewExposureTime", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~bottomViewExposureTimeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_bottomViewExposureTime(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_bottomViewExposureTime(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_bottomViewExposureTime_allowed(ty);}
};

class topViewExposureTimeAttrib: public Tango::Attr
{
public:
	topViewExposureTimeAttrib():Attr("topViewExposureTime", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~topViewExposureTimeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_topViewExposureTime(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_topViewExposureTime(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_topViewExposureTime_allowed(ty);}
};

class wViewEnabledAttrib: public Tango::Attr
{
public:
	wViewEnabledAttrib():Attr("wViewEnabled", Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~wViewEnabledAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_wViewEnabled(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<Hamamatsu *>(dev))->write_wViewEnabled(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_wViewEnabled_allowed(ty);}
};

class fpsAttrib: public Tango::Attr
{
public:
	fpsAttrib():Attr("fps", Tango::DEV_DOUBLE, Tango::READ) {};
	~fpsAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_fps(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_fps_allowed(ty);}
};

class lostFramesAttrib: public Tango::Attr
{
public:
	lostFramesAttrib():Attr("lostFrames", Tango::DEV_LONG, Tango::READ) {};
	~lostFramesAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<Hamamatsu *>(dev))->read_lostFrames(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<Hamamatsu *>(dev))->is_lostFrames_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
//
// The HamamatsuClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	HamamatsuClass : public Tango::DeviceClass
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
	static HamamatsuClass *init(const char *);
	static HamamatsuClass *instance();
	~HamamatsuClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	HamamatsuClass(string &);
	static HamamatsuClass *_instance;
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


}	//	namespace Hamamatsu_ns

#endif // _HAMAMATSUCLASS_H
