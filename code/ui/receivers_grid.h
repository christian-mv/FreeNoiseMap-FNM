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
    ReceiversGrid(const fnm::CoreGridSettings &gridSettings);
    void setGrid(const fnm::CoreGridSettings &gridSettings);
    void setGradient(const fnm::CoreGradientColor gradientColor);
    bool paintGrid(QImage &image, const fnm::CoreGridSettings &myGrid,  QProgressDialog &progress);
    void setNoiseColor(const double Leq, QColor * colorDecibel);
    std::vector< std::vector<fnm::CorePointReceiver *> > matrix;
    fnm::CoreGridSettings getGridSettings()const {return this->gridSettings;}
    void resetNoiseReceiver();
//    string gridStatistics(); // this doesn't work on android NDK
    void interpolateGrid();
    void clearInterpolatedReceivers();

private:
    fnm::CoreGridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(fnm::CorePointReceiver * receiver);
    QRectF receiverRect(const double x, const double y);
    fnm::CoreGradientColor gradientColor;

};

}
#endif // RECEIVERSGRID_H