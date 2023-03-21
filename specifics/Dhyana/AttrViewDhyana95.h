#ifndef AttrViewDhyana95_H
#define AttrViewDhyana95_H

#include "AttrView.h"

namespace Dhyana_ns
{

class AttrViewDhyana95 : public AttrView
{

public:
    AttrViewDhyana95(Tango::DeviceImpl* dev);
    ~AttrViewDhyana95();

    void init();

    void read_dynamique_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamique_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

private:
    StringUserData* m_dyn_model;
    StringUserData* m_dyn_version;
    DoubleUserData* m_dyn_sensor_temperature;
    DoubleUserData* m_dyn_sensor_temperature_target;
    ULongUserData*  m_dyn_fan_speed;
    EnumUserData*   m_dyn_global_gain;
    DoubleUserData* m_dyn_frame_rate;    
    EnumUserData*   m_dyn_trigOutputKind;
    DoubleUserData* m_dyn_trigOutputWidth;
    DoubleUserData* m_dyn_trigOutputDelay;
    EnumUserData*   m_dyn_trigOutputEdge;
};

} //namespace

#endif
