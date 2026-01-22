#ifndef FNM_CORE_BARRIER_SEGMENT_H
#define FNM_CORE_BARRIER_SEGMENT_H
#include "segment.h"

/*
 * This acoustic barrier is essentially defined as a line
 * with a height
*/
namespace fnm_core {

class BarrierSegment : public Segment
{
public:
    explicit BarrierSegment();
    double get_height() const;
    void set_height(double value);

private:
    double height; // in meters
};

}
#endif // MINIMAL_ACOUSTIC_BARRIER_H
