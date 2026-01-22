#ifndef FNM_RECEIVERS_GRID_H
#define FNM_RECEIVERS_GRID_H


#include <vector>
#include <QPainter>
#include <QObject>
#include "noise_grid.h"
#include "gradient_color.h"

class  QProgressDialog;


using namespace std;

namespace fnm_ui {

class ReceiversGrid
{
public:
    ReceiversGrid();
    
    void setNoiseGrid(fnm_core::NoiseGrid* grid);
    void setGradient(const fnm_core::GradientColor gradientColor);
    bool paintGrid(QImage &image, QProgressDialog &progress);

private:
    fnm_core::NoiseGrid* noiseGrid = nullptr;
    
    void setNoiseColor(const double Leq, QColor * colorDecibel);
    QRectF receiverRect(const fnm_core::PointReceiver &receiver);
    QRectF receiverRect(const double x, const double y);
    fnm_core::GradientColor gradientColor;

};

}
#endif // RECEIVERSGRID_H
