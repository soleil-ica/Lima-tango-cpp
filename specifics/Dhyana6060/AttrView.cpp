#include "AttrView.h"

namespace Dhyana6060_ns
{

AttrView::AttrView(Tango::DeviceImpl* dev)
    : Tango::LogAdapter(dev),
    m_device(dev),
    m_dim(dev)
{
}

AttrView::~AttrView()
{
}


} // namespace