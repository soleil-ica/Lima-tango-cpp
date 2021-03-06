static const char *RcsId = "$Id $";
//+=============================================================================
//
// file :         RoiCountersStateMachine.cpp
//
// description :  C++ source for the RoiCounters and its alowed 
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
#include <tango.h>
#endif

#include <RoiCounters.h>
#include <RoiCountersClass.h>

#ifndef WIN32
#include <tango.h>
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

namespace RoiCounters_ns
{

//=================================================
//		Attributes Allowed Methods
//=================================================
//+----------------------------------------------------------------------------
//
// method : 		RoiCounters::is_version_allowed
// 
// description : 	Read/Write allowed for version attribute.
//
//-----------------------------------------------------------------------------
bool RoiCounters::is_version_allowed(Tango::AttReqType type)
{
		//	End of Generated Code

		//	Re-Start of Generated Code
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		RoiCounters::is_runLevel_allowed
// 
// description : 	Read/Write allowed for runLevel attribute.
//
//-----------------------------------------------------------------------------
bool RoiCounters::is_runLevel_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code

		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		RoiCounters::is_operationsList_allowed
// 
// description : 	Read/Write allowed for operationsList attribute.
//
//-----------------------------------------------------------------------------
bool RoiCounters::is_operationsList_allowed(Tango::AttReqType type)
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


}	// namespace RoiCounters_ns
