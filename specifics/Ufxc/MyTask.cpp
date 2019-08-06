// ============================================================================
//
// = CONTEXT
//        DeviceTask attached to the Main device,
//
// = File
//        MyTask.cpp
//
// = AUTHOR
//        Arafat NOUREDDINE - SOLEIL (MEDIANE SYSTEME)
//
// ============================================================================
#include <MyTask.h>


namespace Ufxc_ns
{
// ============================================================================
// ctor
// ============================================================================    
MyTask::MyTask(Tango::DeviceImpl* dev):
yat4tango::DeviceTask(dev)
{
	INFO_STREAM << "MyTask::MyTask" << endl;

	enable_timeout_msg(false);
	set_periodic_msg_period(kTASK_PERIODIC_TIMEOUT_MS);
	enable_periodic_msg(false);
	m_device = dev;
}

// ============================================================================
// dtor
// ============================================================================    
MyTask::~MyTask()
{
	INFO_STREAM << "MyTask::~MyTask" << endl;

}

// ============================================================================
// 
// ============================================================================   
void MyTask::load_config_file(lima::Ufxc::Camera* cam, const std::string& file_name)
{
	m_camera = cam;
	m_config_file = file_name;
	yat::Message* msg = yat::Message::allocate(DEVICE_LOAD_CONFIG_FILE_MSG, DEFAULT_MSG_PRIORITY,true);
	wait_msg_handled(msg, 50000);	
	//post(msg);
}

// ============================================================================
// Process the message queue of the Task
// ============================================================================    
void MyTask::process_message(yat::Message& msg) throw(Tango::DevFailed)
{
	try
	{
		switch(msg.type())
		{
				//-----------------------------------------------------------------------------------------------
			case yat::TASK_INIT:
			{
				INFO_STREAM << "-> yat::TASK_INIT" << endl;

			}
				break;

				//-----------------------------------------------------------------------------------------------
			case yat::TASK_EXIT:
			{
				INFO_STREAM << "-> yat::TASK_EXIT" << endl;

			}
				break;

				//-----------------------------------------------------------------------------------------------            

			case DEVICE_LOAD_CONFIG_FILE_MSG:
			{
				INFO_STREAM << "-> yat::DEVICE_LOAD_CONFIG_FILE_MSG" << endl;
				try
				{
					//yat::AutoMutex<> _lock(ControlFactory::instance().get_global_mutex());					
					INFO_STREAM<<"Load the detector config file in progress ..."<<std::endl;
					m_camera->set_detector_config_file(m_config_file);
					INFO_STREAM<<"Load the detector config file Done."<<std::endl;
				}
				catch(Tango::DevFailed &df)
				{
					ERROR_STREAM << df << endl;
				}
				catch(Exception& e)
				{
					ERROR_STREAM << e.getErrMsg() << endl;
				}
			}
				break;


				//-----------------------------------------------------------------------------------------------
		}
	}
	catch(yat::Exception& ex)
	{
		//- TODO Error Handling
		ex.dump();

		//- rethrow exception
		stringstream ssError;
		for(unsigned i = 0;i < ex.errors.size();i++)
		{
			ssError << ex.errors[i].desc << endl;
			Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										   ssError.str().c_str(),
										   "MyTask::process_message");
		}
		throw;
	}
}




}
