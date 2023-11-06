#ifndef AttrViewDhyana4040_H
#define AttrViewDhyana4040_H

#include "AttrView.h"

namespace Dhyana_ns
{


class AttrViewDhyana4040 : public AttrView
{

public:
    AttrViewDhyana4040(Tango::DeviceImpl* dev);
    ~AttrViewDhyana4040();

    void init();

    void read_dynamic_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
    void read_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
    void write_dynamic_trigger_attribute_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);

private:
    EnumUserData*   m_dyn_tec_mode;
};

} //namespace

#endif
