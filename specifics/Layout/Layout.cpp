static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         Layout.cpp
//
// description :  C++ source for the Layout and its commands.
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                Layout are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name     |  Method name
//	----------------------------------------
//  State            |  dev_state()
//  Status           |  dev_status()
//  AddOperation     |  add_operation()
//  RemoveOperation  |  remove_operation()
//
//===================================================================
#ifdef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

#include <Layout.h>
#include <LayoutClass.h>

#ifndef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

using namespace std;

namespace Layout_ns
{
//+----------------------------------------------------------------------------
//
// method :         Layout::Layout(string &s)
//
// description :     constructor for simulated Layout
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------

Layout::Layout(Tango::DeviceClass *cl, string &s)
: Tango::Device_4Impl(cl, s.c_str())
{
    init_device();
}

Layout::Layout(Tango::DeviceClass *cl, const char *s)
: Tango::Device_4Impl(cl, s)
{
    init_device();
}

Layout::Layout(Tango::DeviceClass *cl, const char *s, const char *d)
: Tango::Device_4Impl(cl, s, d)
{
    init_device();
}
//+----------------------------------------------------------------------------
//
// method :         Layout::delete_device()
//
// description :     will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------

void Layout::delete_device()
{
    INFO_STREAM << "Layout::delete_device() delete device " << device_name << endl;    
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());		
    //    Delete device allocated objects
	DELETE_DEVSTRING_ATTRIBUTE(attr_version_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_operationType_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_operationValue_read);
	

		
    //remove user layout tasks associated to externalOperation
	INFO_STREAM << "- remove all user layout tasks ..."<<endl;
	if(!m_layout_tasks.empty())
	{	
		for (int i = 0; i < m_layout_tasks.size(); i++)
		{
			delete m_layout_tasks.at(i);
		}
		m_layout_tasks.clear();
	}
	
	// No Inner Appender		
}

//+----------------------------------------------------------------------------
//
// method :         Layout::init_device()
//
// description :     will be called at device initialization.
//
//-----------------------------------------------------------------------------

void Layout::init_device()
{
    INFO_STREAM << "Layout::init_device() create device " << device_name << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    // Initialise variables to default values
    //--------------------------------------------
    get_device_property();
	
	CREATE_DEVSTRING_ATTRIBUTE(attr_version_read, 256);
    CREATE_DEVSTRING_ATTRIBUTE(attr_operationType_read, 255);
    CREATE_DEVSTRING_ATTRIBUTE(attr_operationValue_read, 255);

    //By default INIT, need to ensure that all objets are OK before set the device to STANDBY
    set_state(Tango::INIT);
    m_is_device_initialized = false;
    m_status_message.str("");
//	m_mapOperations.clear();
    m_layout_tasks.clear();
    m_ct = 0;
	
	//- instanciate the appender in order to manage logs
	// No Inner Appender	
	
    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object!
        m_ct = ControlFactory::instance().get_control("Layout");
		
		//remove external operations
		INFO_STREAM << "- remove all external operations ..."<<endl;
		if(!m_mapOperations.empty())
		{			
			std::map<long, operationParams >::iterator it;
			for(it = m_mapOperations.begin() ; it!= m_mapOperations.end() ; ++it)
			{
				delete_external_operation(it->first);
			}    

			m_mapOperations.clear();
		}		
    }
    catch (Exception& e)
    {
        INFO_STREAM << "Initialization Failed 1: " << e.getErrMsg() << endl;
        m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
    catch (...)
    {
        INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
        m_status_message << "Initialization Failed : UNKNOWN" << endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }

    m_is_device_initialized = true;

    //write at init, only if device is correctly initialized
    if (m_is_device_initialized)
    {
        try
        {
            for (int i = 0; i < memorizedOperationTypes.size(); i++)
            {
                INFO_STREAM << "Write tango hardware at Init - operationType." << endl;
                Tango::WAttribute &operationType = dev_attr->get_w_attr_by_name("operationType");
                m_operationType = memorizedOperationTypes.at(i);
                strcpy(*attr_operationType_read, m_operationType.c_str());
                operationType.set_write_value(m_operationType);
                write_operationType(operationType);

                // write operationValue At Init 
                INFO_STREAM << "Write tango hardware at Init - operationValue." << endl;
                Tango::WAttribute &operationValue = dev_attr->get_w_attr_by_name("operationValue");
                m_operationValue = memorizedOperationValues.at(i);
                strcpy(*attr_operationValue_read, m_operationValue.c_str());
                operationValue.set_write_value(m_operationValue);
                write_operationValue(operationValue);

                // AddOp()
                INFO_STREAM << "Write tango hardware at Init - Add Operations to the processLib." << endl;
                add_external_operation(memorizedOperationLevels.at(i));               
            }
        }
		catch(ProcessException& p)
		{
            INFO_STREAM << "Initialization Failed : " << p.getErrMsg() << endl;
            m_status_message << "Initialization Failed : " << p.getErrMsg( ) << endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
		}		
        catch (Exception& e)
        {
            INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
            m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
        }
        catch (Tango::DevFailed& df)
        {
            ERROR_STREAM << df << endl;
            INFO_STREAM << "Initialization Failed : " << std::string(df.errors[0].desc) << endl;
            m_status_message << "Initialization Failed : " << std::string(df.errors[0].desc) << endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
        }
    }

    set_state(Tango::STANDBY);
    dev_state();
}


//+----------------------------------------------------------------------------
//
// method : 		Layout::get_device_property()
//
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------

void Layout::get_device_property()
{
    //	Initialize your default values here (if not done with  POGO).
    //------------------------------------------------------------------

    //	Read device properties from database.(Automatic code generation)
    //------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("MemorizedOperationTypes"));
	dev_prop.push_back(Tango::DbDatum("MemorizedOperationValues"));
	dev_prop.push_back(Tango::DbDatum("MemorizedOperationLevels"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	LayoutClass	*ds_class =
		(static_cast<LayoutClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize MemorizedOperationTypes from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedOperationTypes;
	else {
		//	Try to initialize MemorizedOperationTypes from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedOperationTypes;
	}
	//	And try to extract MemorizedOperationTypes value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedOperationTypes;

	//	Try to initialize MemorizedOperationValues from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedOperationValues;
	else {
		//	Try to initialize MemorizedOperationValues from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedOperationValues;
	}
	//	And try to extract MemorizedOperationValues value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedOperationValues;

	//	Try to initialize MemorizedOperationLevels from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedOperationLevels;
	else {
		//	Try to initialize MemorizedOperationLevels from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedOperationLevels;
	}
	//	And try to extract MemorizedOperationLevels value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedOperationLevels;



    //	End of Automatic code generation
    //------------------------------------------------------------------
    std::vector<std::string> myVector;
    myVector.push_back("NONE");
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, myVector, "MemorizedOperationTypes");
    myVector.clear();
    myVector.push_back("0");
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, myVector, "MemorizedOperationValues");
    myVector.clear();
    myVector.push_back("0");
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, myVector, "MemorizedOperationLevels");
}
//+----------------------------------------------------------------------------
//
// method :         Layout::always_executed_hook()
//
// description :     method always executed before any command is executed
//
//-----------------------------------------------------------------------------

void Layout::always_executed_hook()
{
    yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {        
        if(!m_is_device_initialized)//nothing to do ! device need init
            return;

        //- get the singleton control objet used to pilot the lima framework
        m_ct = ControlFactory::instance().get_control("Layout");

        dev_state();
    }
    catch (Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        INFO_STREAM << "Initialization Failed : " << std::string(df.errors[0].desc) << endl;
        m_status_message << "Initialization Failed : " << std::string(df.errors[0].desc) << endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
}
//+----------------------------------------------------------------------------
//
// method : 		Layout::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------

void Layout::read_attr_hardware(vector<long> &attr_list)
{

    DEBUG_STREAM << "Layout::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
    //	Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		Layout::read_version
// 
// description : 	Extract real attribute values for version acquisition result.
//
//-----------------------------------------------------------------------------
void Layout::read_version(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Layout::read_version(Tango::Attribute &attr) entering... "<< endl;
	try
	{
		strcpy(*attr_version_read, CURRENT_VERSION);
		attr.set_value(attr_version_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										string(df.errors[0].desc).c_str(),
										"Layout::read_version()");
	}	
}

//+----------------------------------------------------------------------------
//
// method : 		Layout::read_operationsList
// 
// description : 	Extract real attribute values for operationsList acquisition result.
//
//-----------------------------------------------------------------------------

void Layout::read_operationsList(Tango::Attribute &attr)
{
    DEBUG_STREAM << "Layout::read_operationsList(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    Tango::DevString *ptr = new Tango::DevString[ 1024 ];

    int item_idx = 0;
	ptr[item_idx] = CORBA::string_dup("");
    for (std::map<long, operationParams >::iterator itMap = m_mapOperations.begin(); itMap != m_mapOperations.end(); ++itMap)
    {
		if(itMap->second.operationType != "NONE")
		{
			std::stringstream item("");
			item << "runLevel = " << itMap->first
			<< " : "
			<< "Operation = " << itMap->second.operationType
			<< " ( "<< itMap->second.operationValue<<" )";
			ptr[item_idx] = CORBA::string_dup((item.str()).c_str());
			item_idx++;
		}
    }
	
    attr.set_value(ptr, item_idx, 0, true);
}


//+----------------------------------------------------------------------------
//
// method : 		Layout::read_operationType
// 
// description : 	Extract real attribute values for operationType acquisition result.
//
//-----------------------------------------------------------------------------

void Layout::read_operationType(Tango::Attribute &attr)
{
    DEBUG_STREAM << "Layout::read_operationType(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {
        attr.set_value(attr_operationType_read);
    }
    catch (Tango::DevFailed& df)
    {

        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          std::string(df.errors[0].desc).c_str(),
                                          "Layout::read_operationType");
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Layout::write_operationType
// 
// description : 	Write operationType attribute values to hardware.
//
//-----------------------------------------------------------------------------

void Layout::write_operationType(Tango::WAttribute &attr)
{
    DEBUG_STREAM << "Layout::write_operationType(Tango::WAttribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {
        m_operationType = *attr_operationType_read; //memorize previous valid value
        attr.get_write_value(attr_operationType_write);
        std::string current = attr_operationType_write;
        transform(current.begin(), current.end(), current.begin(), ::toupper);
        if ((current != "+") &&
            (current != "-") &&
            (current != "*") &&
            (current != "/") &&
            (current != ">>") &&
            (current != "<<") &&
            (current != "FLIP") &&
			(current != "ROTATION") &&
            (current != "NONE")
            )
        {
            attr_operationType_write = const_cast<Tango::DevString>(m_operationType.c_str());
            Tango::Except::throw_exception("CONFIGURATION_ERROR",
                                           "Possible operationType values are:"
                                           "\n+"
                                           "\n-"
                                           "\n*"
                                           "\n/"
                                           "\n>>"
                                           "\n<<"
                                           "\nFLIP"
										   "\nROTATION"
                                           "\nNONE",
                                           "Layout::write_operationType");
        }

        //- THIS IS AN AVAILABLE operationType     
        m_operationType = current;
        strcpy(*attr_operationType_read, current.c_str());
    }
    catch (Tango::DevFailed& df)
    {

        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          std::string(df.errors[0].desc).c_str(),
                                          "Layout::write_operationType");
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Layout::read_operationValue
// 
// description : 	Extract real attribute values for operationValue acquisition result.
//
//-----------------------------------------------------------------------------

void Layout::read_operationValue(Tango::Attribute &attr)
{
    DEBUG_STREAM << "Layout::read_operationValue(Tango::Attribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {
        attr.set_value(attr_operationValue_read);
    }
    catch (Tango::DevFailed& df)
    {

        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          std::string(df.errors[0].desc).c_str(),
                                          "Layout::read_operationValue");
    }
}

//+----------------------------------------------------------------------------
//
// method : 		Layout::write_operationValue
// 
// description : 	Write operationValue attribute values to hardware.
//
//-----------------------------------------------------------------------------

void Layout::write_operationValue(Tango::WAttribute &attr)
{
    DEBUG_STREAM << "Layout::write_operationValue(Tango::WAttribute &attr) entering... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {
        attr.get_write_value(attr_operationValue_write);
        m_operationValue = attr_operationValue_write;
        transform(m_operationValue.begin(), m_operationValue.end(), m_operationValue.begin(), ::toupper);
        strcpy(*attr_operationValue_read, m_operationValue.c_str());
    }
    catch (Tango::DevFailed& df)
    {

        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          std::string(df.errors[0].desc).c_str(),
                                          "Layout::write_operationValue");
    }
}

//+------------------------------------------------------------------
/**
 *    method:    Layout::delete_external_operation
 *
 */
//+------------------------------------------------------------------

void Layout::delete_external_operation(long level)
{
    DEBUG_STREAM << "Layout::delete_external_operation() entering ... " << endl;
    //free old operation
    yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    if (m_ct != 0)
    {
        try
        {			
			std::stringstream opId("");
			opId << m_mapOperations[level].opId;
			INFO_STREAM << "\t- delOp [" << opId.str() << "]"<<endl;
			m_ct->externalOperation()->delOp(opId.str());
			m_mapOperations.erase(level);
        }
        catch (Exception& e)
        {

            ERROR_STREAM << e.getErrMsg() << endl;
            //- throw exception
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                           e.getErrMsg().c_str(),
                                           "Layout::delete_external_operation");
        }
    }
}

//+------------------------------------------------------------------
/**
 *    method:    Layout::add_external_operation
 *
 */
//+------------------------------------------------------------------

void Layout::add_external_operation(long level)
{
    DEBUG_STREAM << "Layout::add_external_operation() entering ... " << endl;
    //add a new operation
    yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    if (m_ct != 0)
    {
        try
        {			
            bool flipX = false;
            bool flipY = false;			
            if (m_operationType == "FLIP")
            {
                if (m_operationValue == "X")
                {
                    flipX = true;
                }
                else if (m_operationValue == "Y")
                {
                    flipY = true;
                }
                else if (m_operationValue == "XY")
                {
                    flipX = true;
                    flipY = true;
                }
                else
                {
                    Tango::Except::throw_exception("CONFIGURATION_ERROR",
                                                   "Available Flip Modes are:"
                                                   "\n- X"
                                                   "\n- Y"
                                                   "\n- XY",
                                                   "Layout::add_external_operation");
                }
				
                //create new operation
                std::stringstream opId("");
                SoftOpInstance op;
                opId << level<<":FLIP ("<<m_operationValue<<")";
				INFO_STREAM << "\t- addOp [" << opId.str() << "]"<<endl;
				operationParams params = {opId.str(), attr_operationType_write, attr_operationValue_write};
				m_mapOperations[level] = params;				
                m_ct->externalOperation()->addOp(FLIP, opId.str(), level, op);				
                (reinterpret_cast<SoftOpFlip*> (op.m_opt))->setFlip(flipX, flipY);
                return;
            }

            if (m_operationType == "ROTATION")
            {                
				SoftOpRotation::Type type;
                if (m_operationValue == "90")
                {
                    type = SoftOpRotation::R_90;
                }
                else if (m_operationValue == "180")
                {
                    type = SoftOpRotation::R_180;
                }
                else if (m_operationValue == "270")
                {
					type = SoftOpRotation::R_270;
                }
                else
                {
                    Tango::Except::throw_exception("CONFIGURATION_ERROR",
                                                   "Available Rotation Modes are:"
                                                   "\n- 90"
                                                   "\n- 180"
                                                   "\n- 270",
                                                   "Layout::add_external_operation");
                }
				//create new operation
                std::stringstream opId("");
                SoftOpInstance op;
                opId << level<<":ROTATION ("<<m_operationValue<<")";
				INFO_STREAM << "\t- addOp [" << opId.str() << "]"<<endl;
				operationParams params = {opId.str(), attr_operationType_write, attr_operationValue_write};
				m_mapOperations[level] = params;						
                m_ct->externalOperation()->addOp(ROTATION, opId.str(), level, op);				
                (reinterpret_cast<SoftOpRotation*> (op.m_opt))->setType(type);
                return;
            }
			
            if (m_operationType == "+"	||
                m_operationType == "-"	||
                m_operationType == "*"	||
                m_operationType == "/"	||
                m_operationType == "<<"	||
                m_operationType == ">>" )
            {
                //create new operation
                std::stringstream opId("");
                SoftOpInstance op;
				opId << level<<":"<<m_operationType<<" ("<<m_operationValue<<")";
				INFO_STREAM << "\t- addOp [" << opId.str() << "]"<<endl;
				operationParams params = {opId.str(), attr_operationType_write, attr_operationValue_write};
				m_mapOperations[level] = params;				
                m_ct->externalOperation()->addOp(USER_LINK_TASK, opId.str(), level, op);

				//prepare l'externalOperation Task
				LayoutTask* task = new LayoutTask("NONE", 0);
                task->setOperationType(attr_operationType_write);
                task->setOperationValue(yat::XString<double>::to_num(m_operationValue));				 
				m_layout_tasks.push_back(task);
                (reinterpret_cast<SoftUserLinkTask*> (op.m_opt))->setLinkTask(task);
                return;
            }

            //NOP : if(m_operationType == "NONE")
        }
        catch (Exception& e)
        {
            ERROR_STREAM << e.getErrMsg() << endl;
            //- throw exception
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                           e.getErrMsg().c_str(),
                                           "Layout::add_external_operation");
        }
        catch (yat::Exception& ex)
        {
            //throw_devfailed( ex );
            ex.dump();
            std::stringstream errMsg("");
            for (unsigned i = 0; i < ex.errors.size(); i++)
            {
                errMsg << ex.errors[i].desc << endl;
            }

            //- throw exception
            Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                           errMsg.str().c_str(),
                                           "Layout::add_external_operation");
        }
    }
}

//+------------------------------------------------------------------
/**
 *    method:    Layout::memorize_all_operations
 *
 */
//+------------------------------------------------------------------

void Layout::memorize_all_operations(void)
{
    DEBUG_STREAM << "Layout::memorize_all_operations() entering ... " << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    //Memorize operations

    std::vector<long> vecOpLevel;
    std::vector<std::string> vecOpType;
    std::vector<std::string> vecOpValue;
    for (std::map<long, operationParams >::iterator itMap = m_mapOperations.begin(); itMap != m_mapOperations.end(); ++itMap)
    {

        vecOpLevel.push_back(itMap->first);
        vecOpType.push_back(itMap->second.operationType);
        vecOpValue.push_back(itMap->second.operationValue);
    }

    yat4tango::PropertyHelper::set_property(this, "MemorizedOperationLevels", vecOpLevel);
    yat4tango::PropertyHelper::set_property(this, "MemorizedOperationTypes", vecOpType);
    yat4tango::PropertyHelper::set_property(this, "MemorizedOperationValues", vecOpValue);
}


//+------------------------------------------------------------------
/**
 *	method:	Layout::add_operation
 *
 *	description:	method to execute "AddOperation"
 *	Add Lima external operation in order to transform the image acquired from the detector.<br>
 *	User must first define the operationType, operationValue attributes<br>
 *	argin will define the level of operation.
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void Layout::add_operation(Tango::DevLong argin)
{
    DEBUG_STREAM << "Layout::add_operation(): entering... !" << endl;
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    //	Add your own code to control device here
    try
    {
        yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
        add_external_operation(argin);
        memorize_all_operations();
    }
    catch (Exception& e)
    {

        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Layout::add_operation");
    }

}


//+------------------------------------------------------------------
/**
 *	method:	Layout::remove_operation
 *
 *	description:	method to execute "RemoveOperation"
 *	Remove a Lima external operation previously defined at the the level = argin.<br>
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void Layout::remove_operation(Tango::DevLong argin)
{
    DEBUG_STREAM << "Layout::remove_operation(): entering... !" << endl;

    //	Add your own code to control device here
	yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    try
    {
        yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
		std::map<long, operationParams >::iterator it;			
		it = m_mapOperations.find (argin);	
		if (it != m_mapOperations.end())
		{		
			delete_external_operation(argin);
			memorize_all_operations();			
		}
    }
    catch (Exception& e)
    {

        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Layout::remove_operation");
    }
}

//+------------------------------------------------------------------
/**
 *    method:    Layout::dev_state
 *
 *    description:    method to execute "State"
 *    This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return    State Code
 *
 */
//+------------------------------------------------------------------

Tango::DevState Layout::dev_state()
{
    Tango::DevState argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "Layout::dev_state(): entering... !" << endl;
    //    Add your own code to control device here
    yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());
    stringstream DeviceStatus;
    DeviceStatus << "";
    Tango::DevState DeviceState = Tango::STANDBY;
    if (!m_is_device_initialized)
    {
        INFO_STREAM << "m_status_message = " << m_status_message.str() << endl;
        DeviceState = Tango::FAULT;
        DeviceStatus << m_status_message.str();
    }
    else
    {
        // state & status are retrieved from Factory, Factory is updated by Generic device
        DeviceState = ControlFactory::instance().get_state();
        DeviceStatus << ControlFactory::instance().get_status();
    }

    set_state(DeviceState);
    set_status(DeviceStatus.str());

    argout = DeviceState;
    return argout;
}






}	//	namespace
