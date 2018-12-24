#include <QDebug>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QProgressDialog>
#include <QMessageBox>
#include <QScrollBar>

#include "mainwindow.h"
#include "fnm_types.h"
#include "minimal_point_source.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include "pointsourcepixmapitem.h"
#include "mygraphicsshadedlineitem.h"
#include "qgraphics_polyline_source_item.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    singleLine(nullptr), polyLineSource(nullptr)

{

    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
    setWindowIcon(QIcon(":/images/icons/app_icon.png"));
    setWindowTitle(QString(MY_APP_NAME)+" - v"+QString(VERSION_OF_APP));

    loadCursors();


    loadDefaultGrid();

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setMouseTracking(true); // enabling mouse track on a scene when not pressing mouse
    qApp->installEventFilter(this);



    ui->graphicsView->centerOn(QPointF(0,0));
    ui->graphicsView->scale(1,-1); // invert Y axes





#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
            QSize iconsSize(80,80);
            ui->toolBar->setIconSize(iconsSize);
#endif



    ui->graphicsView->show();




}

MainWindow::~MainWindow()
{
    delete ui;
}

// this method is necessary to compasate the reflection of Y axes
QImage MainWindow::invertImageOnYAxes(const QImage &image)
{
    QPoint center = image.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.scale(1,-1);
    return image.transformed(matrix);
}

void MainWindow::loadCursors()
{

    myCursors["arrowMode"] = QCursor(Qt::ArrowCursor);
    myCursors["backUpCursor"] = myCursors["arrowMode"];

    myCursors["pointSource"] = QCursor(
                QPixmap(":/images/icons/point_source.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));


    myCursors["editMode"] = QCursor(Qt::PointingHandCursor);

    myCursors["gridMode"] = QCursor(Qt::CrossCursor);

    myCursors["dragMode"] = QCursor(Qt::OpenHandCursor);

    myCursors["lineSourceMode"] = QCursor(
                QPixmap(":/images/icons/target.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));




}

void MainWindow::loadDefaultGrid()
{
    myGrid.setRect(QRectF(0, 0, 1000, 600));
    myGrid.setDeltaX(2);
    myGrid.setDeltaY(2);
    myGrid.setInterpolationFactor(1);
    receivers.setGrid(myGrid);
    scene.setSceneRect(myGrid.getRect()); // neccesary for consistency when scrolling

    resetPixmapArea();

    scene.setBackgroundBrush(Qt::darkGray);
    scene.addItem(&pixmapItem);
    pixmapItem.setPos(myGrid.get_x(), myGrid.get_y());


}

void MainWindow::resetPixmapArea(){

    qreal side = qMin(myGrid.getRect().width(), myGrid.getRect().height());
    qreal side2 = qMax(qApp->desktop()->width(), qApp->desktop()->height());

    image = new QImage(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);
    image->fill(Qt::white);


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));

    pixmapItem.setScale(side/side2); // to represent the real size in the scene

}

void MainWindow::movingItemsOnTheScene(QPointF Pos)
{
    if (ui->graphicsView->cursor()==myCursors["arrowMode"] && scene.getShadedItemFlag()){


        QGraphicsItem *moving_item= scene.mouseGrabberItem();

        // the next conditional detects if no items or the rasterAreaItem were clicked, in
        // in the contrary case, the proceed witht he calcularion of the line


        if(moving_item!=nullptr && moving_item != &pixmapItem)
        {
            shaded_line->setLine(p1_shaded_line.x(),
                                 p1_shaded_line.y(),
                                 Pos.x(),
                                 Pos.y());

            moving_item->setPos(Pos); // this correct the position of the item to be more acurate
        }
    }
}

void MainWindow::draggingPointSourceItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent, QGraphicsItem *pressed_item)
{


    // the next conditional detects if an intem different from rasterArea was clicked
    if(pressed_item!=nullptr && pressed_item != &pixmapItem)
    {

        // if the shaded_line already exists in the scene, it isn't neccesary
        // create a new one.
        if(scene.getShadedItemFlag()){
           return;
        }

        shaded_line = new MyGraphicsShadedLineItem;
        p1_shaded_line = sceneEvent->scenePos();

        // init line with 0 lenth (necessary to avoid flip)
        shaded_line->setLine(p1_shaded_line.x(),
                             p1_shaded_line.y(),
                             p1_shaded_line.x(),
                             p1_shaded_line.y());

        scene.addItem(shaded_line);
        scene.setShadedItemFlag(true);


    }
}

void MainWindow::droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent)
{
    QGraphicsItem *item_released= scene.mouseGrabberItem();

    // the next conditional when a item(s) that is moving is released in its new position
    if(item_released!=nullptr && item_released != &pixmapItem && scene.getShadedItemFlag())
    {        
        // we update the position of the point source just for
        // movements greater than 0.1
        QPointF p1 = shaded_line->line().p1();
        QPointF p2 = sceneEvent->scenePos();
        double temp = NoiseEngine::distanceBetweenPoints(p1.x(),p1.y(),0, p2.x(),p2.y(), 0);

        if(temp>0.1){
            item_released->setPos(sceneEvent->scenePos()); // this correct the position to be more acurate
        }
        delete shaded_line;
    }
    scene.setShadedItemFlag(false);
}

bool MainWindow::isThereNoiseSources() const
{
    for(auto item: scene.items()){
        if(item->type()== FNM_TypeId::PointSourceItemType ||
                item->type()== FNM_TypeId::LineSourceItemType)
            return true;
    }
    return false;
}

void MainWindow::releaseLineSourceEdition()
{
    singleLine = nullptr;
    polyLineSource = nullptr;
}





bool MainWindow::calculateNoiseFromSources(QProgressDialog &progress)
{    
    for(int i = 0; i<receivers.matrix.size(); i++){
        if(progress.wasCanceled()){
            return false;
        }

        PointSourcePixmapItem *currentPixmapItemPointSource;

        for(auto currentReceiver : receivers.matrix.at(i)){

            // noise from pointSources
            for(auto currentItem : scene.items()){
                if(currentItem->type() == FNM_TypeId::PointSourceItemType){
                    currentPixmapItemPointSource = (static_cast<PointSourcePixmapItem *>(currentItem));
                    NoiseEngine::P2P(currentPixmapItemPointSource->getPointSource(), currentReceiver);
                }
            }
        }
        progress.setValue(i);
        qApp->processEvents();
    }
    return true;
}



bool MainWindow::eventFilter(QObject *target, QEvent *event)
{

    if(target == &scene){
        QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (sceneEvent->type() == QEvent::GraphicsSceneMouseMove)
          {
            QString str = QString("x: %1 m, y: %2 m")
                                    .arg(sceneEvent->scenePos().x())
                                    .arg(sceneEvent->scenePos().y());

            statusBar()->showMessage(str);

            movingItemsOnTheScene(sceneEvent->scenePos());

            auto itemUnderCursor = scene.itemAt(sceneEvent->scenePos(), ui->graphicsView->transform());
            if(itemUnderCursor != &pixmapItem
                    && itemUnderCursor != nullptr ){

                if(ui->graphicsView->cursor()==myCursors["arrowMode"]){
                    itemUnderCursor->setAcceptHoverEvents(true);
                }else{
                    itemUnderCursor->setAcceptHoverEvents(false);
                    itemUnderCursor->setCursor(ui->graphicsView->cursor());
                }
            }
          }


        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){


            /*  Note: scene.mouseGrabberItem() doesn't
                work weel on GraphicsSceneMousePress event but it works well on
                GraphicsSceneMouseRelease event, on the other hand, scene.itemAt()
                doesn't work well on GraphicsSceneMouseRelease because it takes the topmost
                object, but it works well on GraphicsSceneMousePress.
                */
            QGraphicsItem *pressed_item = scene.itemAt(sceneEvent->scenePos(),ui->graphicsView->transform());

            if(pressed_item != nullptr){
                switch (pressed_item->type()) {
                    case FNM_TypeId::PointSourceItemType:
                        draggingPointSourceItemsOnTheScene(sceneEvent, pressed_item);
                    break;

                }
            }

        }

        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["pointSource"])
          {

            MinimalPointSource *myPointSource = new MinimalPointSource(
                        sceneEvent->scenePos().x(),
                        sceneEvent->scenePos().y(),
                        1.2,90);

            // create pixmapItem for the noise source

            QPixmap myPixmap(":/images/icons/point_source.png");

            // add pixmapItems in a size that depends on the platform

            #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
                        myPixmap = myPixmap.scaled(36,36,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #else
                        myPixmap = myPixmap.scaled(18,18,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #endif

            PointSourcePixmapItem * myPixmapPointSourceItem = new PointSourcePixmapItem();

            myPixmapPointSourceItem->setPixmap(myPixmap);
            myPixmapPointSourceItem->setPointSource(myPointSource);


            scene.addItem(myPixmapPointSourceItem);

          }


        // add line source
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["lineSourceMode"])
        {




            // there aren't any declared vertice in the line
            if(singleLine == nullptr){
                singleLine = new QLineF();
                if(polyLineSource == nullptr){
                    polyLineSource = new QGraphicsPolyLineSourceItem();

                    scene.addItem(polyLineSource->getLinesGroup());
                    singleLine->setLine(sceneEvent->scenePos().x(), sceneEvent->scenePos().y(),
                                           sceneEvent->scenePos().x(), sceneEvent->scenePos().y());
                }

            }
            // there is at least one declared vertice in the line
            else if(singleLine != nullptr){

                if(polyLineSource->getLinesGroup()->childItems().isEmpty()){
                    singleLine->setP1(QPointF(singleLine->x2(),
                                              singleLine->y2()));


                }else{

                    // this lines take the first vertice of the current line as exactly the second vertice of the previous line

                    singleLine->setP1( singleLine->p2() );

                }

                singleLine->setP2(QPointF(
                                          sceneEvent->scenePos().x(),
                                          sceneEvent->scenePos().y()
                                          )
                                  );


                if(singleLine->p1() != singleLine->p2()){ // it is not necessary to add lines of 0 distance
                    polyLineSource->addLine(new QGraphicsLineItem(*singleLine));
                    singleLine = new QLineF(singleLine->x2(),
                                            singleLine->y2(),
                                            singleLine->x2(),
                                            singleLine->y2());
                }
            }

        }

        // release line source
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::RightButton
                 && ui->graphicsView->cursor()==myCursors["lineSourceMode"])
        {
            releaseLineSourceEdition();
        }



        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){

            droppingItemsOnTheScene(sceneEvent);

        }

        else if (sceneEvent->type() == QEvent::TouchUpdate
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){
            // next conditional guarantees that the user dropp any object that
            // currently is dragging before proccessing TouchUpdate event
            if(scene.getShadedItemFlag()){
                delete shaded_line;
                scene.setShadedItemFlag(false);
            }

        }

     return QMainWindow::eventFilter(target, event);
    }


    return false;
}



void MainWindow::on_actionAdd_point_source_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["pointSource"]);
    releaseLineSourceEdition();

}


void MainWindow::on_actioneditMode_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["arrowMode"]);
    releaseLineSourceEdition();

}

void MainWindow::on_actiongrid_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["gridMode"]);
    releaseLineSourceEdition();
}

void MainWindow::on_actioncalculateGrid_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["arrowMode"]);
    resetPixmapArea();
    receivers.resetNoiseReceiver();
    releaseLineSourceEdition();


    if( !isThereNoiseSources() ){
        QMessageBox::warning(this, tr("My Application"),
                                       tr("No sources available\n"
                                          "Please enter noise sources"),QMessageBox::Ok);
        return;
    }

    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle(this->windowTitle());
    progress.setLabelText(QObject::tr("Calculating..."));
    progress.setMinimum(0);
    progress.setMaximum(receivers.matrix.size());
    progress.show();

    if(!calculateNoiseFromSources(progress)){
        return;
    }

    progress.setLabelText(QObject::tr("Painting Grid..."));

    receivers.interpolateGrid(); // calculate interpolated receivers
    receivers.paintGrid(*image, myGrid, progress);
    receivers.clearInterpolatedReceivers(); // clean memory

    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));



//    image->save("../test.png", "PNG");
}

void MainWindow::on_actiondrag_mode_triggered()
{
    ui->graphicsView->setCursor(myCursors["dragMode"]);
    releaseLineSourceEdition();

}

void MainWindow::on_actionzoom_full_triggered()
{
    qreal ofsset = 10;

    QRectF rectF = QRectF(myGrid.getRect().x()-ofsset,
                          myGrid.getRect().y()+ofsset,
                          myGrid.getRect().width()+ofsset,
                          myGrid.getRect().height()+ofsset);

    ui->graphicsView->fitInView(rectF,Qt::KeepAspectRatio);


}

void MainWindow::on_action_add_line_source_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["lineSourceMode"]);
    releaseLineSourceEdition();
}
