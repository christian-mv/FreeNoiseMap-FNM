#include "single_line_source.h"
#include "noise_engine.h"
#include <QDebug>

//SingleLineSource::SingleLineSource(double in_x1, double in_y1, double in_z1,
//                       double in_x2, double in_y2, double in_z2,
//                       double in_Lw_total) :
//    x1(in_x1), y1(in_y1), z1(in_z1),
//    x2(in_x2), y2(in_y2), z2(in_z2),
//    Lw_total(in_Lw_total)
//{

//}


//// when user doesn't specify two vertices, the second vertice is consider the same as the first one
//SingleLineSource::SingleLineSource(double x1,
//                                   double y1,
//                                   double z1,
//                                   double in_Lw_total)
//{
//    SingleLineSource(x1, y1, z1, x1, y1, z1, in_Lw_total);
//}

SingleLineSource::SingleLineSource()
{
    qDebug()<<"init SingleLineSource";
}

void SingleLineSource::set_p1(const double &x, const double &y, const double &z)
{
    x1 = x;
    y1 = y;
    z1 = z;
}

void SingleLineSource::set_p2(const double &x, const double &y, const double &z)
{
    x2 = x;
    y2 = y;
    z2 = z;
}

double SingleLineSource::distance() const
{

    return NoiseEngine::distanceBetweenPoints(x1, y1, z1, x2, y2, z2);
}
