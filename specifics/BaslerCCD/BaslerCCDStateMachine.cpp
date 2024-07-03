static const char *RcsId = "$Id $";
//+=============================================================================
//
// file :         BaslerCCDStateMachine.cpp
//
// description :  C++ source for the BaslerCCD and its alowed 
//                methods for commands and attributes
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
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifdef WIN32
#include "tango.h"
#endif

#include <BaslerCCD.h>
#include <BaslerCCDClass.h>

#ifndef WIN32
#include "tango.h"
#endif

/*====================================================================
 *	This file contains the methods to allow commands and attributes
 * read or write execution.
 *
 * If you wand to add your own code, add it between 
 * the "End/Re-Start of Generated Code" comments.
 *
 * If you want, you can also add your own methods.
 *====================================================================
 */

namespace BaslerCCD_ns
{

//=================================================
//		Attributes Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_frameRate_allowed
// 
// description : 	Read/Write allowed for frameRate attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_frameRate_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}


//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_temperature_allowed
// 
// description : 	Read/Write allowed for temperature attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_temperature_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_statisticsFailedBufferCount_allowed
// 
// description : 	Read/Write allowed for statisticsFailedBufferCount attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_statisticsFailedBufferCount_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_dataRate_allowed
// 
// description : 	Read/Write allowed for dataRate attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_dataRate_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_interPacketDelay_allowed
// 
// description : 	Read/Write allowed for interPacketDelay attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_interPacketDelay_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_bandwidthAssigned_allowed
// 
// description : 	Read/Write allowed for bandwidthAssigned attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_bandwidthAssigned_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_maxThroughput_allowed
// 
// description : 	Read/Write allowed for maxThroughput attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_maxThroughput_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_currentThroughput_allowed
// 
// description : 	Read/Write allowed for currentThroughput attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_currentThroughput_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_packetSize_allowed
// 
// description : 	Read/Write allowed for packetSize attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_packetSize_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}	
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_autoGain_allowed
// 
// description : 	Read/Write allowed for autoGain attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_autoGain_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
        if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
        {
           return true;
        }

        if ( get_state()==Tango::FAULT && is_device_initialized() )
        {
           return true;
        }
        //	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_gain_allowed
// 
// description : 	Read/Write allowed for gain attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_gain_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
        if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
        {
           return true;
        }

        if ( get_state()==Tango::FAULT && is_device_initialized() )
        {
           return true;
        }
        //	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		BaslerCCD::is_exposureMode_allowed
// 
// description : 	Read/Write allowed for exposureMode attribute.
//
//-----------------------------------------------------------------------------
bool BaslerCCD::is_exposureMode_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
        if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
        {
           return true;
        }

        if ( get_state()==Tango::FAULT && is_device_initialized() )
        {
           return true;
        }
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//=================================================
//		Commands Allowed Methods
//=================================================


}	// namespace BaslerCCD_ns
