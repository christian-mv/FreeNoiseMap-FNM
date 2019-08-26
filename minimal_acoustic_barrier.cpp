#include "minimal_acoustic_barrier.h"
#include "noise_engine.h"
#include <QDebug>



MinimalAcousticBarrier::MinimalAcousticBarrier():
    x1(0), y1(0), height(0)
{
}

MinimalAcousticBarrier::~MinimalAcousticBarrier()
{
    qDebug()<<"KILLING BARRIER SEGMENT";
}

void MinimalAcousticBarrier::set_p1(const double &x, const double &y)
{
    x1 = x;
    y1 = y;
}

void MinimalAcousticBarrier::set_p2(const double &x, const double &y)
{
    x2 = x;
    y2 = y;
}



double MinimalAcousticBarrier::distance() const
{

    return NoiseEngine::distanceBetweenPoints(x1, y1, height, x2, y2, height);
}

void MinimalAcousticBarrier::moveBy(const double &dx, const double &dy)
{
    x1+=dx;
    y1+=dy;

    x2+=dx;
    y2+=dy;
}
