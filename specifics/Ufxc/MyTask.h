// ============================================================================
//
// = CONTEXT
//        DeviceTask attached to the Main device,
//
// = File
//        MyTask.h
//
// = AUTHOR
//        Arafat NOUREDDINE - SOLEIL
//
// ============================================================================
#ifndef _MY_TASK_H_
#define _MY_TASK_H_

// ============================================================================
// DEPENDENCIES
// ============================================================================
#ifdef WIN32
#include <tango.h>
#include <yat/threading/Mutex.h>
#include <yat4tango/DeviceTask.h>
#include <TangoExceptionsHelper.h>
#endif

//- LIMA
#include "Factory.h"
#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include "UfxcInterface.h"
#include "UfxcCamera.h"

#ifndef WIN32
#include <tango.h>
#include <yat/threading/Mutex.h>
#include <yat4tango/DeviceTask.h>
#include <TangoExceptionsHelper.h>
#endif

using namespace lima;
using namespace std;

// ============================================================================
// DEVICE TASK ACTIVITY PERIOD IN MILLISECS
// ============================================================================
//- the following timeout set the frequency at which the task generates its data
#define kTASK_PERIODIC_TIMEOUT_MS 1000

// ============================================================================
// SOME USER DEFINED MESSAGES
// ============================================================================
const size_t DEVICE_LOAD_CONFIG_FILE_MSG                 = yat::FIRST_USER_MSG + 200;


//--
namespace Ufxc_ns
{

    //- Scan Acquisition Task 
    class MyTask : public yat4tango::DeviceTask
    {
    
    public:
        //- [ctor]
        MyTask( Tango::DeviceImpl* dev );
        
        //- [dtor]
        virtual ~MyTask();
        void load_config_file(lima::Ufxc::Camera* cam, const std::string& file_name);
        
        
    protected://- [yat4tango::DeviceTask implementation]
        virtual void process_message( yat::Message& msg ) throw (Tango::DevFailed);
        
    private:

        //owner device server
        Tango::DeviceImpl*     	m_device;
        lima::Ufxc::Camera*     m_camera;
        std::string             m_config_file;
    
    };
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct TaskExiter
    {
        void operator()(yat4tango::DeviceTask * t)
        {
            try
            {
                //- U may never delete manually a DeviceTask !!!
                std::cout << "TaskExiter()" << std::endl;
                t->exit();
            }
            catch(...)
            {
            }
        }
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       

}




#endif //_ACQUISITION_TASK_H_

