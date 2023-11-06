#include "IAttrViewDhyana6060.h"

namespace Dhyana6060_ns
{

//---------------------------------------------------------------------------------------
// AttrView::AttrView
//---------------------------------------------------------------------------------------
AttrView::AttrView(Tango::DeviceImpl* dev)
    : Tango::LogAdapter(dev),
    m_device(dev),
    m_dim(dev)
{
}

//---------------------------------------------------------------------------------------
// AttrView::~AttrView
//---------------------------------------------------------------------------------------
AttrView::~AttrView()
{
}

//-----------------------------------------------------
//AttrView::get_dim()
//-----------------------------------------------------
yat4tango::DynamicInterfaceManager* AttrView::get_dim()
{
    return &m_dim;
}

} // namespace