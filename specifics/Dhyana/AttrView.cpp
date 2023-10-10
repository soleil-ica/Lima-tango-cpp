#include "AttrView.h"

namespace Dhyana_ns
{

//-----------------------------------------------------
//AttrView::AttrView()
//-----------------------------------------------------
AttrView::AttrView(Tango::DeviceImpl *dev)
: Tango::LogAdapter(dev),
m_device(dev)
{
    m_dim = new yat4tango::DynamicInterfaceManager(dev);
}

//-----------------------------------------------------
//AttrView::~AttrView()
//-----------------------------------------------------
AttrView::~AttrView()
{
	delete m_dim;
}

//-----------------------------------------------------
//AttrView::get_dim()
//-----------------------------------------------------
yat4tango::DynamicInterfaceManager* AttrView::get_dim()
{
    return m_dim;
}

} // namespace