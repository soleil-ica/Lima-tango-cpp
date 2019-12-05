// ============================================================================
//
// = CONTEXT
//        DeviceTask attached to the Main device,
//
// = File
//        AcquisitionTask.h
//
// = AUTHOR
//        Arafat NOUREDDINE - SOLEIL (MEDIANE SYSTEME)
//
// ============================================================================
#ifndef _ACQUISITION_TASK_H_
#define _ACQUISITION_TASK_H_

// ============================================================================
// DEPENDENCIES
// ============================================================================
#ifdef WIN32
#include <tango.h>
#include <yat/threading/Mutex.h>
#include <yat4tango/DeviceTask.h>
//#include <TangoExceptionsHelper.h>
#endif

//- LIMA
#include "Factory.h"
#include "lima/CtControl.h"
#include "lima/CtVideo.h"

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
const size_t DEVICE_STOP_MSG                        = yat::FIRST_USER_MSG + 200;
const size_t DEVICE_SNAP_MSG                        = yat::FIRST_USER_MSG + 201;
const size_t DEVICE_START_MSG                       = yat::FIRST_USER_MSG + 202;
const size_t DEVICE_PREPARE_MSG                     = yat::FIRST_USER_MSG + 203;


//--
namespace LimaDetector_ns
{

    //- Scan Acquisition Task 
    class AcquisitionTask : public yat4tango::DeviceTask
    {
    
    public:
        //- [ctor]
        AcquisitionTask( Tango::DeviceImpl* dev );
        
        //- [dtor]
        virtual ~AcquisitionTask();
        
        //- returns the last state of the task
        Tango::DevState get_state(void) ;
        
        //- returns the last status of the task
        std::string get_status(void) ; 
        
        //- Struct containing the Task configuration, configuration is set by the main Device
        struct AcqConfig
        {
            lima::CtControl*    ct;                          // lima control objet used in owner device (singleton)
            bool            	use_prepare_cmd;        // status when abort is call
            string            	abort_status_message;        // status when abort is call
        };

    protected://- [yat4tango::DeviceTask implementation]
        virtual void process_message( yat::Message& msg ) throw (Tango::DevFailed);
        
    private:
        //fix the state in a scoped_lock
        void set_state(Tango::DevState state);
        
        //fix the state in a scoped_lock
        void set_status (const std::string& status);
        
        //set state to Tango::FAULT and fix a standard status
        void on_abort(Tango::DevFailed df);
        
        //set state to Tango::FAULT    and fix a standard status
        void on_abort(const std::string& st);
        
        //- Struct containing the Task configuration
        AcqConfig             	m_acq_conf;
        
        //- Mutex
        yat::Mutex             	m_status_lock;
        
        //- state&status stuf
        stringstream           	m_status;
        stringstream           	m_footer_status;
        Tango::DevState     	m_state;

        //owner device server
        Tango::DeviceImpl*     	m_device;
    
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

