#include "line_source_segment.h"

namespace fnm_core {

LineSourceSegment::LineSourceSegment() :
    Segment(), Lw_total(0)
{
}

void LineSourceSegment::set_Lw_total(const double &Lw_total)
{
    this->Lw_total = Lw_total;
}

double LineSourceSegment::get_Lw_total() const
{
    return Lw_total;
}

}
