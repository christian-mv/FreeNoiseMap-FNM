#ifndef FNM_CORE_LINE_SOURCE_SEGMENT_H
#define FNM_CORE_LINE_SOURCE_SEGMENT_H
#include "segment.h"

namespace fnm_core {

class LineSourceSegment : public Segment
{
public:
    explicit LineSourceSegment();

    void set_Lw_total(const double &Lw_total);

    double get_Lw_total() const;   

private:   
    double Lw_total; // total sound power level in dB(A) units
};

}
#endif
