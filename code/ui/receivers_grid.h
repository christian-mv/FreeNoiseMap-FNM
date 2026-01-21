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

class FnmReceiversGrid
{
public:
    FnmReceiversGrid();
    FnmReceiversGrid(const FnmCoreGridSettings &gridSettings);
    void setGrid(const FnmCoreGridSettings &gridSettings);
    void setGradient(const FnmCoreGradientColor gradientColor);
    bool paintGrid(QImage &image, const FnmCoreGridSettings &myGrid,  QProgressDialog &progress);
    void setNoiseColor(const double Leq, QColor * colorDecibel);
    std::vector< std::vector<FnmCorePointReceiver *> > matrix;
    FnmCoreGridSettings getGridSettings()const {return this->gridSettings;}
    void resetNoiseReceiver();
//    string gridStatistics(); // this doesn't work on android NDK
    void interpolateGrid();
    void clearInterpolatedReceivers();

private:
    FnmCoreGridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(FnmCorePointReceiver * receiver);
    QRectF receiverRect(const double x, const double y);
    FnmCoreGradientColor gradientColor;

};


#endif // RECEIVERSGRID_H
