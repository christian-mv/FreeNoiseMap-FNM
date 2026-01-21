#ifndef FNM_CORE_LINE_SOURCE_SEGMENT_H
#define FNM_CORE_LINE_SOURCE_SEGMENT_H
#include "segment.h"

namespace fnm_core {

class LineSourceSegment : public Segment
{
public:
    explicit LineSourceSegment() : Segment(), Lw_total(0){}

    void set_Lw_total(const double &Lw_total){this->Lw_total = Lw_total;}

    double get_Lw_total() const {return Lw_total;}   

private:   
    double Lw_total; // total sound power level in dB(A) units
};

}
#endif
