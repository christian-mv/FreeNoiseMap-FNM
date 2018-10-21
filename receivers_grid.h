#ifndef RECEIVERS_GRID_H
#define RECEIVERS_GRID_H


#include <vector>
#include <QPainter>
#include <QObject>
#include "grid_settings.h"
#include "single_receiver.h"
#include "gradientcolor.h"

class  QProgressDialog;


using namespace std;

class ReceiversGrid
{
public:
    ReceiversGrid();
    ReceiversGrid(const GridSettings &gridSettings);
    void setGrid(const GridSettings &gridSettings);
    void setGradient(const GradientColor gradientColor);
    bool paintGrid(QImage &image, const GridSettings &myGrid,  QProgressDialog &progress);
    void setNoiseColor(const double Leq, QColor * colorDecibell);
    std::vector< std::vector<SingleReceiver *> > matrix;
    GridSettings getGridSettings()const {return this->gridSettings;}
    void resetNoiseReceiver();
//    string gridStatistics(); // this doesn't work on android NDK
    void interpolateGrid();
    void clearInterpolatedReceivers();

private:
    GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(SingleReceiver * receiver);
    QRectF receiverRect(const double x, const double y);
    GradientColor gradientColor;

};


#endif // RECEIVERSGRID_H
