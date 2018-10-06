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
    void paintGrid(QImage &image, const GridSettings &myGrid,  QProgressDialog &progress);
#include <QObject>
    void setNoiseColor(const double Leq, QColor * colorDecibell);
    std::vector< std::vector<SingleReceiver *> > matrix;
    GridSettings getGridSettings()const {return this->gridSettings;}
    void resetNoiseReceiver();



private:

    GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(SingleReceiver * receiver);
    QRectF receiverRect(const double x, const double y);
    GradientColor gradientColor;




};


#endif // RECEIVERSGRID_H
