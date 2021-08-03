#include "fnm_ui_receivers_grid.h"
#include "fnm_core_noise_engine.h"
#include <QtDebug>
#include <tuple>
#include <QtWidgets>
using namespace std;

FnmReceiversGrid::FnmReceiversGrid()
{
    // Defining default gradien.
    gradientColor.addStep(0.0/255.0,      255.0/255.0,      0.0/255.0,      -88.0);
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

FnmReceiversGrid::FnmReceiversGrid(const FnmCoreGridSettings &settings)
{    
    setGrid(settings);

}

void FnmReceiversGrid::setGrid(const FnmCoreGridSettings &gridSettings)
{
    this->gridSettings = gridSettings;
    unsigned int nRows = this->gridSettings.countRows();
    unsigned int nColumns = this->gridSettings.countColumns();


    setMatrixOfReceivers(nRows, nColumns); // set this->matrix memeber
//    qDebug()<<matrix.size();
    for(unsigned int i = 0; i < nRows; i++){
        for(unsigned int j = 0; j < nColumns; j++){
//            qDebug()<<i<<" , "<<j;
            matrix.at(j).at(i) = new FnmCorePointReceiver(gridSettings.getLeft()
                                                    + i*gridSettings.getDeltaX(),
                                                    gridSettings.getTop()+j*gridSettings.getDeltaY(),
                                                    false); //matrix.[i][j];
//            qDebug()<<matrix.at(j).at(i)->get_x()<<" , " <<matrix.at(j).at(i)->get_y();
        }
    }


}

void FnmReceiversGrid::setGradient(const FnmCoreGradientColor gradientColor)
{
    this->gradientColor = gradientColor;
    this->gradientColor.sortStepsAscending();
}

void FnmReceiversGrid::setMatrixOfReceivers(unsigned int n, unsigned int m)
{
    matrix.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i){
        matrix[i].resize(n);
    }
}

bool FnmReceiversGrid::paintGrid(QImage &image, const FnmCoreGridSettings &myGrid, QProgressDialog &progress)
{



    // it is necessary redefine the maximum steps of the progress dialog since interpolation
    // could change the size of matriz
    progress.setMaximum(static_cast<int>(matrix.size())+1);

    QPainter painter(&image);

    painter.translate(myGrid.getRect().bottomLeft());

    painter.translate(-myGrid.getRect().left() /*+ myGrid.getDeltaX()/2*/,
                      myGrid.getRect().top() /*- myGrid.getDeltaY()/2*/);

    painter.scale(1, -1);



//    // set logical coordinates according to gridSettings area
    painter.setWindow(gridSettings.getRect().toRect());


    // set paint properties
//    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::NoPen);
    painter.setPen(pen);


    // calculate single rectangles
    QColor decibelColor;
    QBrush brush;
    FnmCorePointReceiver interpolatedReceiver;
    FnmCorePointReceiver *r;


    for(unsigned int i = 0; i<matrix.size(); i++){

        if(progress.wasCanceled()){
            progress.close();
            return false;
        }

        for(unsigned int j = 0; j<matrix.at(i).size(); j++){

            r = matrix.at(i).at(j);

            setNoiseColor(r->get_Leq(), &decibelColor);            
            painter.setBrush(QBrush(decibelColor));
            painter.drawRect(receiverRect(r));
        }

        qApp->processEvents();
        progress.setValue( static_cast<int>(i) );
    }
    progress.close();
    return true;
}

void FnmReceiversGrid::setNoiseColor(const double Leq, QColor * colorDecibel)
{
    tuple<double, double, double> colorTuple;

    colorTuple = gradientColor.colorAt(Leq);
    colorDecibel->setRgb(static_cast<int>( 255*std::get<0>(colorTuple) ),
                          static_cast<int>( 255*std::get<1>(colorTuple) ),
                          static_cast<int>( 255*std::get<2>(colorTuple) ),
                          255);


//    if(Leq <= 35){ // dB units
//        colorDecibel->setRgb(0, 255, 0, 255);
//    }
//    else if(35<Leq && Leq<=40){
//        colorDecibel->setRgb(85, 170, 0, 255);
//    }
//    else if(40<Leq && Leq<=45){
//        colorDecibel->setRgb(255, 255, 0, 255);
//    }
//    else if(45<Leq && Leq<=50){
//        colorDecibel->setRgb(197, 131, 0, 255);
//    }
//    else if(50<Leq && Leq<=55){
//        colorDecibel->setRgb(255, 92, 11, 255);
//    }
//    else if(55<Leq && Leq<=60){
//        colorDecibel->setRgb(255, 0, 0, 255);
//    }
//    else if(60<Leq && Leq<=65){
//        colorDecibel->setRgb(156, 0, 0, 255);
//    }
//    else if(65<Leq && Leq<=70){
//        colorDecibel->setRgb(85, 0, 127, 255);
//    }
//    else if(70<Leq && Leq<=75){
//        colorDecibel->setRgb(0, 0, 150, 255);
//    }
//    else if(75<Leq && Leq<=80){
//        colorDecibel->setRgb(0, 0, 113, 255);
//    }
//    else if(80<Leq){
//        colorDecibel->setRgb(0, 0, 0, 255);
//    }

}

void FnmReceiversGrid::resetNoiseReceiver()
{
    for(auto row: matrix){
        for(auto receiver: row){
            receiver->set_Leq(-88);
        }
    }
}



//string ReceiversGrid::gridStatistics()
//{
//    unsigned int countInterpolated = 0;
//    unsigned int countNoInterpolated = 0;
//    for(auto row: matrix){
//        for(auto receiver: row)
//            if(receiver->isInterpolated()){
//                countInterpolated++;
//            }
//            else
//            {
//                countNoInterpolated++;
//            }
//    }

//    string result;

//    // to_string() is not supported for android NDK
//    result = "interpolated receivers: " + countInterpolated
//            +" no interpolated receivers: " + countInterpolated ;

//    return result;
//}

void FnmReceiversGrid::interpolateGrid()
{
    unsigned int factor = getGridSettings().getInterpolatorFactor();
    if(factor<=1){return;}

    FnmCorePointReceiver interpolatedReceiver;
    FnmCorePointReceiver *r;
    vector<FnmCorePointReceiver *> temprow;
    vector<vector<FnmCorePointReceiver *>> tempMatrix; // esto es una matriz intermedia de receptores

    double dx = getGridSettings().getDeltaX()/factor;
    double dy = getGridSettings().getDeltaY()/factor;
    double Leqx_temp; // here store interpolated Leq on x axes.
    double Leqy_temp; // here store interpolated Leq on y axes.

    //  interpolated rectangles on x axes
    for(unsigned int i = 0; i<matrix.size(); i++){
        for(unsigned int j = 0; j<matrix.at(i).size(); j=j+factor){

            r = matrix.at(i).at(j);
            if(j<matrix.at(i).size()-1){
                for(unsigned int k=1; k<factor; k++){

                    FnmCoreNoiseEngine::interpolationValueAt(r->get_x(),
                                                      r->get_Leq(),
                                                      r->get_x()+k*dx,
                                                      Leqx_temp,
                                                      matrix.at(i).at(j+1)->get_x(),
                                                      matrix.at(i).at(j+1)->get_Leq());


                    matrix.at(i).insert(matrix.at(i).begin()+j+1,
                                                   new FnmCorePointReceiver(r->get_x()+k*dx,
                                                                      r->get_y(),
                                                                      r->get_z(),
                                                                      Leqx_temp,true));
                } // for k
            }// if
        } // for j
    } // for i




    // interpolated rectangles on y axes

    std::vector<FnmCorePointReceiver *> centinel = matrix.back();

    for(unsigned int i = 0; ; i=i+factor){

        if(matrix.at(i) == centinel) // beak when the last row is reached
        {
            break;
        }
        for(unsigned int k=1; k<factor; k++){
            for(unsigned int j = 0; j<matrix.at(i).size(); j++){

                r = matrix.at(i).at(j);

                FnmCoreNoiseEngine::interpolationValueAt(r->get_y(),
                                                  r->get_Leq(),
                                                  r->get_y()+k*dy,
                                                  Leqy_temp,
                                                  matrix.at(i+1).at(j)->get_y(),
                                                  matrix.at(i+1).at(j)->get_Leq());


                temprow.push_back(new FnmCorePointReceiver(r->get_x(),
                                                     r->get_y()+k*dy,
                                                     r->get_z(),
                                                     Leqy_temp,true));

            } // for: k

            tempMatrix.push_back(temprow);
            temprow.clear();

        }//
        matrix.insert(matrix.begin()+i,tempMatrix.begin(), tempMatrix.end());
        tempMatrix.clear();
    } //
}

void FnmReceiversGrid::clearInterpolatedReceivers()
{
    // delete full interpolated rows
    unsigned int i = 0;
    std::vector<FnmCorePointReceiver *> row = matrix.at(i);
    while(row != matrix.back()){
        // delete rows of full interpolated receivers
        if(row.at(0)->isInterpolated()){
            matrix.erase(matrix.begin() + i);
            row = matrix.at(i);
            continue;
        }
        ++i;
        row = matrix.at(i);
    }

    // delete interpolated receivers located in between of no-interpolated receivers
    for(unsigned int i=0; i<matrix.size(); i++){
        unsigned int j = 0;
        auto tempReceiver = matrix.at(i).at(j);
        while(tempReceiver != matrix.at(i).back()){
            if(tempReceiver->isInterpolated()){
                matrix.at(i).erase(matrix.at(i).begin() + j);
                tempReceiver = matrix.at(i).at(j);
                continue;
            }
            j++;
            tempReceiver = matrix.at(i).at(j);
        }
    }

}


QRectF  FnmReceiversGrid::receiverRect(FnmCorePointReceiver * receiver)
{

    return receiverRect(receiver->get_x(), receiver->get_y());
}


QRectF FnmReceiversGrid::receiverRect(const double x, const double y)
{
    unsigned int n = gridSettings.getInterpolatorFactor();
    double dx = gridSettings.getDeltaX();
    double dy = gridSettings.getDeltaY();
    double width = dx/n;
    double height = dy/n;

    return QRectF(x - width/2,
                      y - height/2,
                      width,
                      height
                  );
}

