#include "receivers_grid.h"
#include "noise_engine.h"
#include <QtDebug>
#include <tuple>
#include <QtWidgets>
using namespace std;

ReceiversGrid::ReceiversGrid()
{
    // Defining default gradien.
    gradientColor.addStep(0.0/255.0,      255.0/255.0,      0.0/255.0,      20.0);
    gradientColor.addStep(0.0/255.0,      255.0/255.0,      0.0/255.0,      35.0);
    gradientColor.addStep(85.0/255.0,     170.0/255.0,      0.0/255.0,      40.0);
    gradientColor.addStep(255.0/255.0,    255.0/255.0,      0.0/255.0,      45.0);
    gradientColor.addStep(197.0/255.0,    131.0/255.0,      0.0/255.0,      50.0);
    gradientColor.addStep(255.0/255.0,    92.0/255.0,       11.0/255.0,     55.0);
    gradientColor.addStep(255.0/255.0,    0.0/255.0,         0.0/255.0,     60.0);
    gradientColor.addStep(156.0/255.0,    0.0/255.0,        0.0/255.0,      65.0);
    gradientColor.addStep(85.0/255.0,     0/255.0,          127.0/255.0,    70.0);
    gradientColor.addStep(0.0/255.0,      0/255.0,          150.0/255.0,    75.0);
    gradientColor.addStep(0.0/255.0,      0.0/255.0,        113.0/255.0,    80.0);
    gradientColor.addStep(0.0/255.0,      0.0/255.0,        113.0/255.0,    120.0);


    gradientColor.sortStepsAscending();

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

void ReceiversGrid::setGradient(const GradientColor gradientColor)
{
    this->gradientColor = gradientColor;
    this->gradientColor.sortStepsAscending();
}

void ReceiversGrid::setMatrixOfReceivers(unsigned int n, unsigned int m)
{
    matrix.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i){
        matrix[i].resize(n);
    }
}

void ReceiversGrid::paintGrid(QImage &image, const GridSettings &myGrid)
{

    NoiseEngine::interpolateGrid(this);


    QPainter painter(&image);

    painter.translate(myGrid.getRect().bottomLeft());

    painter.translate(-myGrid.getRect().left() /*+ myGrid.getDeltaX()/2*/,
                      myGrid.getRect().top() /*- myGrid.getDeltaY()/2*/);




    painter.scale(1, -1);


    painter.save();

//    // set logical coordinates according to gridSettings area
    painter.setWindow(gridSettings.getRect().toRect());



    // set paint properties
//    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::NoPen);
    painter.setPen(pen);


    // calculate single rectangles
    QColor decibelColor;
    QBrush brush;
    SingleReceiver interpolatedReceiver;
    SingleReceiver *r;


    QProgressDialog progress;
    progress.setWindowModality(Qt::WindowModal);
//    progress.setWindowTitle(QObject::tr("Pdf converter"));
    progress.setLabelText(QObject::tr("Painting grid..."));
    progress.setMinimum(0);
    progress.setMaximum(matrix.size()- 1);
    progress.show();



    for(int i = 0; i<matrix.size(); i++){
        for(int j = 0; j<matrix.at(i).size(); j++){

            r = matrix.at(i).at(j);

            setNoiseColor(r->get_Leq(), &decibelColor);
            painter.setBrush(QBrush(decibelColor));
            painter.drawRect(receiverRect(r));



//             if(!r->isInterpolated()){
//                 painter.drawEllipse(r->get_x(), r->get_y(), 1,1); // central points on rectangles
//             }



//             // next block draws text on each rectangle (optional)
//                        painter.save();
//                        painter.scale(1, -1);

//                        QPen pen(Qt::SolidLine);

//                        painter.setFont(QFont("Times", 4));
//                        painter.setPen(pen);

//             painter.drawText(static_cast<int>(receiverRect(r).x()),
//                               static_cast<int>(-receiverRect(r).center().y()),
//                               "(x:" + QString::number(r->get_x())+" , y:" +
//                               QString::number(r->get_y()) + ") ");
//                        painter.restore();
        }

        progress.setValue(i);
    }


    progress.setValue( progress.maximum() );

    painter.restore();

}

void ReceiversGrid::setNoiseColor(const double Leq, QColor * colorDecibell)
{
    tuple<double, double, double> colorTuple;

    colorTuple = gradientColor.colorAt(Leq);
    colorDecibell->setRgb(static_cast<int>( 255*std::get<0>(colorTuple) ),
                          static_cast<int>( 255*std::get<1>(colorTuple) ),
                          static_cast<int>( 255*std::get<2>(colorTuple) ),
                          255);


/*    if(Leq <= 35){ // dB units
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
        colorDecibell->setRgb(0, 0, 150, 255);
    }
    else if(75<Leq && Leq<=80){
        colorDecibell->setRgb(0, 0, 113, 255);
    }
    else if(80<Leq){
        colorDecibell->setRgb(0, 0, 0, 255);
    }
*/
}





QRectF  ReceiversGrid::receiverRect(SingleReceiver * receiver)
{

    return receiverRect(receiver->get_x(), receiver->get_y());
}


QRectF ReceiversGrid::receiverRect(const double x, const double y)
{
    unsigned int n = gridSettings.getInterpolatorFactor();
    double dx = gridSettings.getDeltaX();
    double dy = gridSettings.getDeltaY();

    return QRectF(x - (dx/n)/2,
                      y - (dy/n)/2,
                      dx/n,
                      dy/n
                  );
}













