#ifndef RECEIVERS_GRID_H
#define RECEIVERS_GRID_H

#include "grid_settings.h"
#include "single_receiver.h"
#include <vector>
#include <QPainter>
#include <QRegion>




using namespace std;

class ReceiversGrid
{
public:
    ReceiversGrid();
    ReceiversGrid(const GridSettings &gridSettings);
    void setGrid(const GridSettings &gridSettings);
    void paintGrid(QPainter *painter);
    void setNoiseColor(const SingleReceiver* receiver, QColor * colorDecibell);
    std::vector< std::vector<SingleReceiver *> > matrix;


private:


    GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(SingleReceiver * receiver);

};


#endif // RECEIVERSGRID_H
