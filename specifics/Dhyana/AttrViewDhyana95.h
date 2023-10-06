#ifndef AttrViewDhyana95_H
#define AttrViewDhyana95_H

#include "AttrView.h"

namespace Dhyana_ns
{

enum GlobalGain
{
    HDR = 0,
    HIGH = 1,
    LOW = 2
};

enum TriggeroutModeDhyana95
{
    kEXPOSURESTART = 0,
    kGLOBAL = 1,
    kREADOUT = 2
};

enum TriggeroutEdgeDhyana95
{
    kRISING = 0,
    kFAILING = 1,
};

class AttrViewDhyana95 : public AttrView
{

public:
    AttrViewDhyana95(Tango::DeviceImpl* dev);
    ~AttrViewDhyana95();

    void init();

    void read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    void read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

private:
    StringUserData* m_dyn_model;
    StringUserData* m_dyn_version;
    DoubleUserData* m_dyn_sensor_temperature;
    DoubleUserData* m_dyn_sensor_temperature_target;
    ULongUserData*  m_dyn_fan_speed;
    EnumUserData*   m_dyn_global_gain;
    DoubleUserData* m_dyn_frame_rate;    
    EnumUserData*   m_dyn_trig_output_kind[3];
    DoubleUserData* m_dyn_trig_output_width[3];
    DoubleUserData* m_dyn_trig_output_delay[3];
    EnumUserData*   m_dyn_trig_output_edge[3];
};

} //namespace

#endif
