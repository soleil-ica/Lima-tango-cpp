#include "AttrView.h"

namespace Dhyana_ns
{

AttrView::AttrView(Tango::DeviceImpl *dev)
: Tango::LogAdapter(dev),
m_device(dev)
{
    m_dim = new yat4tango::DynamicInterfaceManager(dev);
}

AttrView::~AttrView()
{
	delete m_dim;
}

yat4tango::DynamicInterfaceManager* AttrView::get_dim()
{
    return m_dim;
}

} // namespace