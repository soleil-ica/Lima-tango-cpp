#ifndef AttrView_H
#define AttrView_H

#include <tango.h>

#include <yat/any/Any.h>
#include <yat/utils/Callback.h>
#include <yat4tango/DynamicInterfaceManager.h>

#include "UserData.h"


namespace Dhyana_ns
{

class AttrView : public Tango::LogAdapter
{

public:
    AttrView(Tango::DeviceImpl *dev);
    ~AttrView();

    /// callback methods for tango dyn attributes - NULL
    void read_callback_null(yat4tango::DynamicAttributeReadCallbackData& cbd){/*nop*/}
	
    /// callback methods for tango dyn attributes - NULL
    void write_callback_null(yat4tango::DynamicAttributeWriteCallbackData& cbd){/*nop*/}

protected:

    //! \brief m_dim: Dynamic attributes objects        
    yat4tango::DynamicInterfaceManager m_dim;

    //! \brief m_device: Owner Device server object    
    Tango::DeviceImpl* m_device;

};

} // namespace

#endif