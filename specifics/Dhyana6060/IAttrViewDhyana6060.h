#ifndef AttrView6060_H
#define AttrView6060_H

#include <tango.h>

#include <yat/any/Any.h>
#include <yat/utils/Callback.h>
#include <yat4tango/DynamicInterfaceManager.h>


namespace Dhyana6060_ns
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
    virtual void read_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd) = 0;
    virtual void write_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd) = 0;

    yat4tango::DynamicInterfaceManager* get_dim();

protected:

    //! \brief m_device: Owner Device server object    
    Tango::DeviceImpl* m_device;
    //! \brief m_dim: Dynamic attributes objects        
    yat4tango::DynamicInterfaceManager m_dim;

};

} // namespace

#endif