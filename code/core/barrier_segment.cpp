#include "barrier_segment.h"

namespace fnm_core {

BarrierSegment::BarrierSegment() :
    Segment(), height(10)
{
}

double BarrierSegment::get_height() const
{
    return height;
}

void BarrierSegment::set_height(double value)
{
    this->height = value;
}

}
