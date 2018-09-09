#ifndef RECEIVERS_GRID_H
#define RECEIVERS_GRID_H


#include <vector>
#include <QPainter>
#include "grid_settings.h"
#include "single_receiver.h"
#include "gradientcolor.h"



using namespace std;

class ReceiversGrid
{
public:
    ReceiversGrid();
    ReceiversGrid(const GridSettings &gridSettings);
    void setGrid(const GridSettings &gridSettings);
    void setGradient(const GradientColor gradientColor);
    void paintGrid(QPainter *painter);

    void setNoiseColor(const SingleReceiver* receiver, QColor * colorDecibell);
    std::vector< std::vector<SingleReceiver *> > matrix;


private:

    GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(SingleReceiver * receiver);
    GradientColor gradientColor;

};


#endif // RECEIVERSGRID_H
