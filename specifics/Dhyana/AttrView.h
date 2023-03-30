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

    virtual void read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd) = 0;
    virtual void write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd) = 0;
    virtual void read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd) = 0;
    virtual void write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd) = 0;

    yat4tango::DynamicInterfaceManager* get_dim();

protected:

    //! \brief m_dim: Dynamic attributes objects        
    yat4tango::DynamicInterfaceManager* m_dim;

    //! \brief m_device: Owner Device server object    
    Tango::DeviceImpl* m_device;

};

} // namespace

#endif