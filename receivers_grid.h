#ifndef RECEIVERS_GRID_H
#define RECEIVERS_GRID_H

#include "grid_settings.h"
#include "single_receiver.h"
#include "my_personal_tools.h"
#include <vector>
#include <QPainter>




using namespace std;

class ReceiversGrid
{
public:
    ReceiversGrid();
    ReceiversGrid(const GridSettings &gridSettings);
    void setGrid(const GridSettings &gridSettings);
    void paintGrid(QPainter *painter);


private:

    std::vector< std::vector<SingleReceiver *> > matrix;
    GridSettings gridSettings;
    void setMatrixOfReceivers(unsigned int n, unsigned int m);
    QRectF receiverRect(SingleReceiver * receiver);


};







#endif // RECEIVERSGRID_H
