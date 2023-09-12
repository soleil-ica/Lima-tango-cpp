#ifndef AttrViewDhyana6060_H
#define AttrViewDhyana6060_H

#include "AttrView.h"
#include "UserData.h"

namespace Dhyana6060_ns
{

class AttrViewDhyana6060 : public AttrView
{

public:
    AttrViewDhyana6060(Tango::DeviceImpl* dev);
    ~AttrViewDhyana6060();

    void init();

    void read_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_cooling_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    void read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    void read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

private:
    DoubleUserData* m_dyn_sensor_temperature;
    DoubleUserData* m_dyn_camera_temperature;
    DoubleUserData* m_dyn_sensor_temperature_target;
    EnumUserData* m_dyn_sensor_cooling_type;
    ULongUserData* m_dyn_fan_speed;
    EnumUserData* m_dyn_fan_type;
    EnumUserData* m_dyn_global_gain;
};

} //namespace

#endif
