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

    virtual void read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    virtual void write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    virtual void read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    virtual void write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    virtual void read_dynamic_tec_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    virtual void write_dynamic_tec_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

    yat4tango::DynamicInterfaceManager* get_dim();

protected:

    void init_common_attributes();

    //! \brief m_dim: Dynamic attributes objects        
    yat4tango::DynamicInterfaceManager m_dim;

    //! \brief m_device: Owner Device server object    
    Tango::DeviceImpl* m_device;


    StringUserData* m_dyn_model;
    StringUserData* m_dyn_version;
    DoubleUserData* m_dyn_sensor_temperature;
    DoubleUserData* m_dyn_sensor_temperature_target;
    ULongUserData*  m_dyn_fan_speed;
    EnumUserData*   m_dyn_global_gain;
    DoubleUserData* m_dyn_frame_rate; 
    DoubleUserData* m_dyn_frame_rate_hw;       
    EnumUserData*   m_dyn_trig_output_kind[3];
    DoubleUserData* m_dyn_trig_output_width[3];
    DoubleUserData* m_dyn_trig_output_delay[3];
    EnumUserData*   m_dyn_trig_output_edge[3];

};

} // namespace

#endif