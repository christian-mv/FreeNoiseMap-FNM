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
//    painter->setBrush(QBrush(QColor(Qt::darkGreen)));

    // calculate single rectangles
    QColor decibelColor;
    for(auto row: matrix){
        for(auto data: row){
            setNoiseColor(data, &decibelColor);
            painter->setBrush(QBrush(decibelColor));
            painter->drawRect(receiverRect(data));

            // next block draws text on each rectangle (optional)
            painter->save();
            painter->scale(1, -1);

            painter->drawText(static_cast<int>(receiverRect(data).x()),
                              static_cast<int>(-receiverRect(data).center().y()),
                              "(x:" + QString::number(data->get_x())+" , y:" +
                              QString::number(data->get_y()) + ") ");
            painter->restore();
        }
    }

    painter->restore();
}

void ReceiversGrid::setNoiseColor(const SingleReceiver *receiver,
                                  QColor *colorDecibell)
{
    if(receiver->get_Leq() <= 30){ // dB units
        colorDecibell->setRgb(0, 153, 0, 255);
    }
}



QRectF  ReceiversGrid::receiverRect(SingleReceiver * receiver)
{
    return QRectF(receiver->get_x() /*- gridSettings.getDeltaX()/2.0*/,
                      receiver->get_y() /*- gridSettings.getDeltaY()/2.0*/,
                      gridSettings.getDeltaX(),
                      gridSettings.getDeltaY()
                      );
}





