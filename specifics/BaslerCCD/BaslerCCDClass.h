//=============================================================================
//
// file :         BaslerCCDClass.h
//
// description :  Include for the BaslerCCDClass root class.
//                This class is the singleton class for
//                the BaslerCCD device class.
//                It contains all properties and methods which the 
//                BaslerCCD requires only once e.g. the commands.
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
#ifdef WIN32
#include "tango.h"
#endif

#ifndef _BASLERCCDCLASS_H
#define _BASLERCCDCLASS_H

#include <BaslerCCD.h>

#ifndef WIN32
#include "tango.h"
#endif

namespace BaslerCCD_ns
{//=====================================
//	Define classes for attributes
//=====================================
class statisticsFailedBufferCountAttrib: public Tango::Attr
{
public:
	statisticsFailedBufferCountAttrib():Attr("statisticsFailedBufferCount", Tango::DEV_LONG, Tango::READ) {};
	~statisticsFailedBufferCountAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_statisticsFailedBufferCount(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_statisticsFailedBufferCount_allowed(ty);}
};

class currentThroughputAttrib: public Tango::Attr
{
public:
	currentThroughputAttrib():Attr("currentThroughput", Tango::DEV_LONG, Tango::READ) {};
	~currentThroughputAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_currentThroughput(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_currentThroughput_allowed(ty);}
};

class maxThroughputAttrib: public Tango::Attr
{
public:
	maxThroughputAttrib():Attr("maxThroughput", Tango::DEV_LONG, Tango::READ) {};
	~maxThroughputAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_maxThroughput(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_maxThroughput_allowed(ty);}
};

class bandwidthAssignedAttrib: public Tango::Attr
{
public:
	bandwidthAssignedAttrib():Attr("bandwidthAssigned", Tango::DEV_LONG, Tango::READ) {};
	~bandwidthAssignedAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_bandwidthAssigned(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_bandwidthAssigned_allowed(ty);}
};

class interPacketDelayAttrib: public Tango::Attr
{
public:
	interPacketDelayAttrib():Attr("interPacketDelay", Tango::DEV_LONG, Tango::READ_WRITE) {};
	~interPacketDelayAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_interPacketDelay(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_interPacketDelay(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_interPacketDelay_allowed(ty);}
};

class packetSizeAttrib: public Tango::Attr
{
public:
	packetSizeAttrib():Attr("packetSize", Tango::DEV_LONG, Tango::READ) {};
	~packetSizeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_packetSize(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_packetSize_allowed(ty);}
};

class triggerDelayAttrib: public Tango::Attr
{
public:
	triggerDelayAttrib():Attr("triggerDelay", Tango::DEV_ULONG, Tango::READ_WRITE) {};
	~triggerDelayAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_triggerDelay(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_triggerDelay(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_triggerDelay_allowed(ty);}
};

class gainAttrib: public Tango::Attr
{
public:
	gainAttrib():Attr("gain", Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~gainAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_gain(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_gain(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_gain_allowed(ty);}
};

class autoGainAttrib: public Tango::Attr
{
public:
	autoGainAttrib():Attr("autoGain", Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~autoGainAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_autoGain(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_autoGain(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_autoGain_allowed(ty);}
};

class temperatureAttrib: public Tango::Attr
{
public:
	temperatureAttrib():Attr("temperature", Tango::DEV_DOUBLE, Tango::READ) {};
	~temperatureAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_temperature(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_temperature_allowed(ty);}
};

class dataRateAttrib: public Tango::Attr
{
public:
	dataRateAttrib():Attr("dataRate", Tango::DEV_DOUBLE, Tango::READ) {};
	~dataRateAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_dataRate(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_dataRate_allowed(ty);}
};

class frameRateAttrib: public Tango::Attr
{
public:
	frameRateAttrib():Attr("frameRate", Tango::DEV_DOUBLE, Tango::READ) {};
	~frameRateAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_frameRate(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_frameRate_allowed(ty);}
};

class exposureModeAttrib: public Tango::Attr
{
public:
	exposureModeAttrib():Attr("exposureMode", Tango::DEV_STRING, Tango::READ_WRITE) {};
	~exposureModeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_exposureMode(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<BaslerCCD *>(dev))->write_exposureMode(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_exposureMode_allowed(ty);}
};

class userIDAttrib: public Tango::Attr
{
public:
	userIDAttrib():Attr("userID", Tango::DEV_STRING, Tango::READ) {};
	~userIDAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<BaslerCCD *>(dev))->read_userID(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<BaslerCCD *>(dev))->is_userID_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
//
// The BaslerCCDClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	BaslerCCDClass : public Tango::DeviceClass
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
	static BaslerCCDClass *init(const char *);
	static BaslerCCDClass *instance();
	~BaslerCCDClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	BaslerCCDClass(string &);
	static BaslerCCDClass *_instance;
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


}	//	namespace BaslerCCD_ns

#endif // _BASLERCCDCLASS_H
