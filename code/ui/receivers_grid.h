#ifndef FNM_RECEIVERS_GRID_H
#define FNM_RECEIVERS_GRID_H


#include <vector>
#include <QPainter>
#include <QObject>
#include "grid_settings.h"
#include "point_receiver.h"
#include "gradient_color.h"

class  QProgressDialog;


using namespace std;

namespace fnm_ui {

class ReceiversGrid
{
public:
    ReceiversGrid();
    ReceiversGrid(const fnm_core::GridSettings &gridSettings);
    void setGrid(const fnm_core::GridSettings &gridSettings);
    void setGradient(const fnm_core::GradientColor gradientColor);
    bool paintGrid(QImage &image, const fnm_core::GridSettings &myGrid,  QProgressDialog &progress);
    void setNoiseColor(const double Leq, QColor * colorDecibel);
    std::vector< std::vector<fnm_core::PointReceiver> > matrix;
    fnm_core::GridSettings getGridSettings()const {return this->gridSettings;}
    void resetNoiseReceiver();
//    string gridStatistics(); // this doesn't work on android NDK
    void interpolateGrid();
    void clearInterpolatedReceivers();

private:
    fnm_core::GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(const fnm_core::PointReceiver &receiver);
    QRectF receiverRect(const double x, const double y);
    fnm_core::GradientColor gradientColor;

};

}
#endif // RECEIVERSGRID_H
