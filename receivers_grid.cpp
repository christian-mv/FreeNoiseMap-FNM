#include "receivers_grid.h"
#include <QtDebug>

using namespace std;

ReceiversGrid::ReceiversGrid()
{

}

ReceiversGrid::ReceiversGrid(const GridSettings &settings)
{    
    setGrid(settings);
}

void ReceiversGrid::setGrid(const GridSettings &gridSettings)
{
    this->gridSettings = gridSettings;
    unsigned int nRows = this->gridSettings.countRows();
    unsigned int nColumns = this->gridSettings.countColumns();


    setMatrixOfReceivers(nRows, nColumns); // set this->matrix memeber
//    qDebug()<<matrix.size();
    for(unsigned int i = 0; i < nRows; i++){
        for(unsigned int j = 0; j < nColumns; j++){
//            qDebug()<<i<<" , "<<j;
            matrix.at(j).at(i) = new SingleReceiver(gridSettings.getLeft()
                                                    + i*gridSettings.getDeltaX()
                                                    , gridSettings.getTop()
                                                    +j*gridSettings.getDeltaY()); //matrix.[i][j];
            qDebug()<<matrix.at(j).at(i)->get_x()<<" , " <<matrix.at(j).at(i)->get_y();
        }
    }


}

void ReceiversGrid::setMatrixOfReceivers(unsigned int n, unsigned int m)
{
    matrix.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i){
        matrix[i].resize(n);
    }
}

void ReceiversGrid::paintGrid(QPainter *painter)
{

    painter->save();

////    // translate the painter
//    painter->translate(this->gridSettings.getRect().center());
//    painter->scale(1, -1);

//    // set logical coordinates according to gridSettings area
    qDebug()<<gridSettings.getRect().toRect();
    painter->setWindow(gridSettings.getRect().toRect());
//    painter->setViewport(gridSettings.getRect().toRect());



    // set paint properties
    painter->setRenderHint(QPainter::Antialiasing, true);
//    QPen pen(Qt::NoPen);
//    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(Qt::green)));

    // calculate single rectangles
    for(auto row: matrix){
        for(auto data: row){

            painter->drawRect(receiverRect(data));
            painter->drawText(receiverRect(data),
                              "( x: " + QString::number(data->get_x())+" , y: " +
                              QString::number(data->get_y()) + " ) ");
        }
    }

    painter->restore();
}

QRectF  ReceiversGrid::receiverRect(SingleReceiver * receiver)
{
    return QRectF(receiver->get_x() /*- gridSettings.getDeltaX()/2.0*/,
                      receiver->get_y() /*- gridSettings.getDeltaY()/2.0*/,
                      gridSettings.getDeltaX(),
                      gridSettings.getDeltaY()
                      );
}





