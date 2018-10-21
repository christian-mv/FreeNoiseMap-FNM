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
                                                    + i*gridSettings.getDeltaX(),
                                                    gridSettings.getTop()+j*gridSettings.getDeltaY(),
                                                    false); //matrix.[i][j];
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

bool ReceiversGrid::paintGrid(QImage &image, const GridSettings &myGrid, QProgressDialog &progress)
{



    // it is necessary redefine the maximum steps of the progress dialog since interpolation
    // could change the size of matriz
    progress.setMaximum(matrix.size()+1);

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
    SingleReceiver interpolatedReceiver;
    SingleReceiver *r;

    for(int i = 0; i<matrix.size(); i++){

        if(progress.wasCanceled()){
            progress.close();
            return false;
        }

        for(int j = 0; j<matrix.at(i).size(); j++){

            r = matrix.at(i).at(j);

            setNoiseColor(r->get_Leq(), &decibelColor);
            painter.setBrush(QBrush(decibelColor));
            painter.drawRect(receiverRect(r));

        }

        qApp->processEvents();
        progress.setValue(i);
    }
    progress.close();
    return true;
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

void ReceiversGrid::resetNoiseReceiver()
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

void ReceiversGrid::interpolateGrid()
{
    unsigned int factor = getGridSettings().getInterpolatorFactor();
    if(factor<=1){return;}

    SingleReceiver interpolatedReceiver;
    SingleReceiver *r;
    vector<SingleReceiver *> temprow;
    vector<vector<SingleReceiver *>> tempMatrix; // esto es una matriz intermedia de receptores

    double dx = getGridSettings().getDeltaX()/factor;
    double dy = getGridSettings().getDeltaY()/factor;
    double Leqx_temp; // here store interpolated Leq on x axes.
    double Leqy_temp; // here store interpolated Leq on y axes.

    //  interpolated rectangles on x axes
    for(int i = 0; i<matrix.size(); i++){
        for(int j = 0; j<matrix.at(i).size(); j=j+factor){

            r = matrix.at(i).at(j);
            if(j<matrix.at(i).size()-1){
                for(int k=1; k<factor; k++){

                    NoiseEngine::interpolationValueAt(r->get_x(),
                                                      r->get_Leq(),
                                                      r->get_x()+k*dx,
                                                      Leqx_temp,
                                                      matrix.at(i).at(j+1)->get_x(),
                                                      matrix.at(i).at(j+1)->get_Leq());


                    matrix.at(i).insert(matrix.at(i).begin()+j+1,
                                                   new SingleReceiver(r->get_x()+k*dx,
                                                                      r->get_y(),
                                                                      r->get_z(),
                                                                      Leqx_temp,true));
                } // for k
            }// if
        } // for j
    } // for i




    // interpolated rectangles on y axes

    std::vector<SingleReceiver *> centinel = matrix.back();

    for(int i = 0; ; i=i+factor){

        if(matrix.at(i) == centinel) // beak when the last row is reached
        {
            break;
        }
        for(int k=1; k<factor; k++){
            for(int j = 0; j<matrix.at(i).size(); j++){

                r = matrix.at(i).at(j);

                NoiseEngine::interpolationValueAt(r->get_y(),
                                                  r->get_Leq(),
                                                  r->get_y()+k*dy,
                                                  Leqy_temp,
                                                  matrix.at(i+1).at(j)->get_y(),
                                                  matrix.at(i+1).at(j)->get_Leq());


                temprow.push_back(new SingleReceiver(r->get_x(),
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

void ReceiversGrid::clearInterpolatedReceivers()
{
    // delete full interpolated rows
    int i = 0;
    std::vector<SingleReceiver *> row = matrix.at(i);
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
    for(int i=0; i<matrix.size(); i++){
        int j = 0;
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

