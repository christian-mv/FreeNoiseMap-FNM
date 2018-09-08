#include "receivers_grid.h"
#include "my_personal_tools.h"
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
//            qDebug()<<matrix.at(j).at(i)->get_x()<<" , " <<matrix.at(j).at(i)->get_y();
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
//    qDebug()<<gridSettings.getRect().toRect();
    painter->setWindow(gridSettings.getRect().toRect());
//    painter->setViewport(gridSettings.getRect().toRect());



    // set paint properties
//    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::NoPen);
    painter->setPen(pen);


    // calculate single rectangles
    QColor decibelColor;
    for(auto row: matrix){
        for(auto receiver: row){

            setNoiseColor(receiver, &decibelColor);
            painter->setBrush(QBrush(decibelColor));                       

            painter->drawRect(receiverRect(receiver));

//            // next block draws text on each rectangle (optional)
//            painter->save();
//            painter->scale(1, -1);

//            painter->drawText(static_cast<int>(receiverRect(receiver).x()),
//                              static_cast<int>(-receiverRect(receiver).center().y()),
//                              "(x:" + QString::number(receiver->get_x())+" , y:" +
//                              QString::number(receiver->get_y()) + ") ");
//            painter->restore();
        }
    }

    painter->restore();
}

void ReceiversGrid::setNoiseColor(const SingleReceiver *receiver, QColor * colorDecibell)
{
    double Leq = receiver->get_Leq();
    if(Leq <= 35){ // dB units
        colorDecibell->setRgb(0, 255, 0, 255);
    }
    else if(35<Leq && Leq<=40){
        colorDecibell->setRgb(85, 170, 0, 255);
    }
    else if(40<Leq && Leq<=45){
        colorDecibell->setRgb(255, 255, 0, 255);
    }
    else if(45<Leq && Leq<=50){
        colorDecibell->setRgb(197, 131, 0, 255);
    }
    else if(50<Leq && Leq<=55){
        colorDecibell->setRgb(255, 92, 11, 255);
    }
    else if(55<Leq && Leq<=60){
        colorDecibell->setRgb(255, 0, 0, 255);
    }
    else if(60<Leq && Leq<=65){
        colorDecibell->setRgb(156, 0, 0, 255);
    }
    else if(65<Leq && Leq<=70){
        colorDecibell->setRgb(85, 0, 127, 255);
    }
    else if(70<Leq && Leq<=75){
        colorDecibell->setRgb(0, 0, 255, 255);
    }
    else if(80<Leq && Leq<=85){
        colorDecibell->setRgb(0, 0, 113, 255);
    }
    else if(90<Leq){
        colorDecibell->setRgb(0, 0, 0, 255);
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





