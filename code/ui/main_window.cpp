#include <QDebug>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QGraphicsSceneMouseEvent>
#include <QProgressDialog>
#include <QMessageBox>
#include <QScrollBar>
#include "main_window.h"
#include "types_namespace.h"
#include "point_source.h"
#include "point_receiver.h"
#include "ui_mainwindow.h"
#include "noise_engine.h"
#include "qgraphics_items/point_source.h"
#include "qgraphics_items/point_receiver.h"
#include "qgraphics_items/shaded_line.h"
#include "qgraphics_items/multiline_source.h"
#include "qgraphics_items/barrier.h"
#include "qgraphics_items/polyline.h"

#define VERSION_OF_APP "alpha"
#define MY_APP_NAME "Free Noise Map"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    menuActionsGroup(new QActionGroup(this)),
    singleLine(nullptr), 
    polyLine(nullptr), 
    multiLineSource(nullptr), 
    acousticBarrier(nullptr)

{

    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
    setWindowIcon(QIcon(":/images/icons/app_icon.png"));
    setWindowTitle(QString(MY_APP_NAME)+" - version "+QString(VERSION_OF_APP));

    loadCursors();
    makeMenuMutualExclusive();


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

#include <QTransform>

// this method is necessary to compasate the reflection of Y axes
QImage MainWindow::invertImageOnYAxes(const QImage &image)
{
    QPoint center = image.rect().center();
    QTransform matrix;
    matrix.translate(center.x(), center.y());
    matrix.scale(1,-1);
    return image.transformed(matrix);
}

void MainWindow::loadCursors()
{

    auto polyLineObjectPixmap = QPixmap(":/images/icons/polyline_cursor.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    myCursors["barrierCursor"] = QCursor( polyLineObjectPixmap.copy() );
    myCursors["polyLineCursor"] = QCursor( polyLineObjectPixmap.copy() );
    myCursors["lineSourceMode"] = QCursor( polyLineObjectPixmap.copy() );

    myCursors["arrowMode"] = QCursor(Qt::ArrowCursor);
    myCursors["editMode"] = QCursor(Qt::PointingHandCursor);
    myCursors["gridMode"] = QCursor(Qt::CrossCursor);
    myCursors["dragMode"] = QCursor(Qt::OpenHandCursor);

    auto pointObjectPixmap = QPixmap(":/images/icons/target.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    myCursors["pointSource"] = QCursor(pointObjectPixmap.copy());

    myCursors["receiver"] = QCursor(pointObjectPixmap.copy());

}

void MainWindow::makeMenuMutualExclusive()
{
    auto actionsList = ui->toolBar->actions();
    for(auto action: actionsList){
        action->setCheckable(true);
        menuActionsGroup->addAction(action);
    }
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
    qreal side2 = qMax(QGuiApplication::primaryScreen()->size().width(), QGuiApplication::primaryScreen()->size().height());

    image = new QImage(static_cast<int>( side2*myGrid.getRect().width()/side ),
                 static_cast<int>( side2*myGrid.getRect().height()/side ),
                 QImage::Format_ARGB32);
    image->fill(Qt::white);


    pixmapItem.setPixmap(QPixmap::fromImage( invertImageOnYAxes(*image) ));

    pixmapItem.setScale(side/side2); // to represent the real size in the scene

}

void MainWindow::movingItemsOnTheScene(const QGraphicsSceneMouseEvent *sceneMouseEvent)
{
    if (ui->graphicsView->cursor()==myCursors["arrowMode"] ){


        QGraphicsItem *moving_item= scene.mouseGrabberItem();


        if(shaded_line != nullptr){
            shaded_line->setLine(p1_shaded_line.x(),
                                 p1_shaded_line.y(),
                                 sceneMouseEvent->scenePos().x(),
                                 sceneMouseEvent->scenePos().y());
        }

        if(moving_item!=nullptr && moving_item != &pixmapItem)
        {
            //  while shade_line exist we shouldn't change the position of Line source since
            // it doesn't work well
            if( (moving_item->type() == fnm_core::TypeId::MultiLineSourceItemType
                 || moving_item->type() == fnm_core::TypeId::AcousticBarrierItemType
                 || moving_item->type() == fnm_core::TypeId::PolyLineItemType)
                    && shaded_line == nullptr){
                moving_item->moveBy(-sceneMouseEvent->lastScenePos().x()+sceneMouseEvent->scenePos().x(),
                                    -sceneMouseEvent->lastScenePos().y()+sceneMouseEvent->scenePos().y());
            }
        }
    }
}

void MainWindow::updateShadedLinesItem(QPointF pos)
{

    if(shaded_line != nullptr){

        shaded_line->setLine(p1_shaded_line.x(),
                             p1_shaded_line.y(),
                             pos.x(),
                             pos.y());
    }
}


void MainWindow::createShadedLinesItem(QPointF pos)
{
    if(shaded_line == nullptr){
        shaded_line = new fnm_ui::ShadedLine;
        p1_shaded_line = pos;

        // init line with 0 lenth (it is necessary to avoid flip)
        shaded_line->setLine(p1_shaded_line.x(),
                             p1_shaded_line.y(),
                             p1_shaded_line.x(),
                             p1_shaded_line.y());

        scene.addItem(shaded_line);
    }
}

void MainWindow::deleteShadedLinesItem()
{
    if(shaded_line != nullptr){
        delete shaded_line;
        shaded_line = nullptr;
    }
}

void MainWindow::droppingItemsOnTheScene(QGraphicsSceneMouseEvent *sceneEvent)
{
    QGraphicsItem *item_released= scene.mouseGrabberItem();

    // the next conditional when a item(s) that is moving is released in its new position
    if(item_released!=nullptr && item_released != &pixmapItem && shaded_line !=nullptr)
    {
        // we update the position of the item just for
        // movements greater than 0.1

        QPointF p1 = shaded_line->line().p1();
        QPointF p2 = sceneEvent->scenePos();
        double temp = fnm_core::NoiseEngine::distanceBetweenPoints(p1.x(),p1.y(),0, p2.x(),p2.y(), 0);

        if(temp>0.1){
            item_released->setPos(sceneEvent->scenePos()); // this correct the position to be more acurate
        }
    }

}

bool MainWindow::isThereNoiseSources() const
{
    for(auto item: scene.items()){
        if(item->type()== fnm_core::TypeId::PointSourceItemType ||
                item->type()== fnm_core::TypeId::MultiLineSourceItemType)
            return true;
    }
    return false;
}

void MainWindow::releaseLineItemEdition()
{    
    singleLine = nullptr;
    polyLine = nullptr;
    multiLineSource = nullptr;
    acousticBarrier = nullptr;
}



bool MainWindow::calculateNoiseFromSources(QProgressDialog &progress)
{    
    for(unsigned long i = 0; i<receivers.matrix.size(); i++){
        if(progress.wasCanceled()){
            return false;
        }

        fnm_ui::PointSource *currentPixmapItemPointSource;
        fnm_ui::MultiLineSource *currentLineSource;
        auto barriersSegments = barrierSegmentsToStdVector();
//        MinimalAcousticBarrier* barrierSegment;

        for(auto currentReceiver : receivers.matrix.at(i)){           
            for(auto currentItem : scene.items()){
                // noise from point sources
                if(currentItem->type() == fnm_core::TypeId::PointSourceItemType){
                    currentPixmapItemPointSource = (static_cast<fnm_ui::PointSource *>(currentItem));

                    fnm_core::NoiseEngine::P2P(currentPixmapItemPointSource->getPointSource(),
                                                             currentReceiver, barriersSegments);


                }
                // noise from line sources
                if(currentItem->type() == fnm_core::TypeId::MultiLineSourceItemType){
                    currentLineSource = (static_cast<fnm_ui::MultiLineSource *>(currentItem));
                    // Here we iterate a multi line source to obtain a list of
                    // segmets, then each segment is split in point sources
                    for(fnm_core::LineSourceSegment *segment: currentLineSource->getSegments()){
                        for(fnm_core::CorePointSource subPointSource: fnm_core::NoiseEngine::fromLineToPointSources(segment,22.0)){
                            fnm_core::NoiseEngine::P2P(&subPointSource, currentReceiver, barriersSegments);
                        }
                    }
                }
            }
        }
        progress.setValue(static_cast<int>(i));
        qApp->processEvents();
    }
    return true;
}

QList<fnm_ui::Barrier *> MainWindow::barrierList() const
{
    QList<fnm_ui::Barrier *> barriers;
    for(auto item: scene.items()){
        if(item->type() == fnm_core::TypeId::AcousticBarrierItemType){
            barriers.append(static_cast<fnm_ui::Barrier *>(item));
        }
    }
    return barriers;
}

std::vector<fnm_core::CoreBarrierSegment *> MainWindow::barrierSegmentsToStdVector() const
{
    std::vector<fnm_core::CoreBarrierSegment *> segments;
    QVector<fnm_core::CoreBarrierSegment*> temp;

    for(auto item: scene.items()){
        if(item->type() == fnm_core::TypeId::AcousticBarrierItemType){
            temp = (static_cast<fnm_ui::Barrier *>(item)->getSegments());
            for(auto singleSegment: temp){
                segments.push_back(singleSegment);
            }
        }
    }
    return segments;
}



bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(target == &scene){
        QGraphicsSceneMouseEvent *sceneEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

        // update status bar with coordinates
        if (sceneEvent->type() == QEvent::GraphicsSceneMouseMove)
          {
            QString str = QString("x: %1 m, y: %2 m")
                                    .arg(sceneEvent->scenePos().x())
                                    .arg(sceneEvent->scenePos().y());

            statusBar()->showMessage(str);

            updateShadedLinesItem(sceneEvent->scenePos());
            movingItemsOnTheScene(sceneEvent);

            auto itemUnderCursor = scene.itemAt(sceneEvent->scenePos(), ui->graphicsView->transform());
            if(itemUnderCursor != &pixmapItem
                    && itemUnderCursor != nullptr ){
                if(ui->graphicsView->cursor()==myCursors["arrowMode"]){
                    itemUnderCursor->setAcceptHoverEvents(true);
                }
                else{
                    itemUnderCursor->setAcceptHoverEvents(false);
                    itemUnderCursor->setCursor(ui->graphicsView->cursor());
                }
            }
          }

        // add point source
        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["pointSource"])
          {

            fnm_core::CorePointSource *myPointSource = new fnm_core::CorePointSource(
                        sceneEvent->scenePos().x(),
                        sceneEvent->scenePos().y(),
                        1.2,100);

            // create pixmapItem for the noise source

            QPixmap myPixmap(":/images/icons/point_source.png");

            // add pixmapItems in a size that depends on the platform

            #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
                        myPixmap = myPixmap.scaled(36,36,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #else
                        myPixmap = myPixmap.scaled(18,18,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #endif

            fnm_ui::PointSource * myPixmapPointSourceItem = new fnm_ui::PointSource();

            myPixmapPointSourceItem->setPixmap(myPixmap);
            myPixmapPointSourceItem->setPointSource(myPointSource);


            scene.addItem(myPixmapPointSourceItem);
            deleteShadedLinesItem();

          }

        // draggin polyline tipe elements
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){

            QGraphicsItem *pressed_item = scene.itemAt(sceneEvent->scenePos(),ui->graphicsView->transform());
            /*
             * Note : scene.mouseGrabberItem() doesn't
             * work well on GraphicsSceneMousePress event but it works well on
             * GraphicsSceneMouseRelease event, on the other hand, scene.itemAt()
             * doesn't work well on GraphicsSceneMouseRelease because it takes the topmost
             * object, but it works well on GraphicsSceneMousePress.
                */

            if(pressed_item != nullptr){
                 /* this switch controls which item require shaded lines
                  * this is important since shaded lines don't work well with all items, for some extrange reason
                  * it doesn't work with polylines */
                switch (pressed_item->type()) {
                // do not create shadedlines for line source or acoustic barrier (NOT WORKING)
                case fnm_core::TypeId::MultiLineSourceItemType:
                    break;
                case fnm_core::TypeId::AcousticBarrierItemType:
                    break;
                case fnm_core::TypeId::PolyLineItemType:
                    break;
                default:
                    createShadedLinesItem(sceneEvent->scenePos());
                    break;
                }
            }
        }
                
        
        // add receiver
        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["receiver"])
          {
            qDebug()<<"HERE";
            fnm_core::CorePointReceiver *myReceiver = new fnm_core::CorePointReceiver(
                        sceneEvent->scenePos().x(),
                        sceneEvent->scenePos().y(),
                        1.2,0);

            // create pixmapItem for the receiver

            QPixmap myPixmap(":/images/icons/receiver.png");

            // add pixmapItems in a size that depends on the platform

            #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
                        myPixmap = myPixmap.scaled(36,36,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #else
                        myPixmap = myPixmap.scaled(18,18,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            #endif

            fnm_ui::PointReceiver * myPixmapReceiver = new fnm_ui::PointReceiver();

            myPixmapReceiver->setPixmap(myPixmap);
            myPixmapReceiver->setPointReceiver(myReceiver);


            scene.addItem(myPixmapReceiver);
            deleteShadedLinesItem();

          }



        // add polyLine
                else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                         && sceneEvent->button() == Qt::LeftButton
                         && ui->graphicsView->cursor()==myCursors["polyLineCursor"])
                {

                    // there aren't any declared vertice in the line
                    if(singleLine == nullptr){
                        createShadedLinesItem(sceneEvent->scenePos());
                        singleLine = new QLineF();
                        if(polyLine == nullptr){
                            polyLine = new fnm_ui::PolyLine();
                            scene.addItem(polyLine);
                            singleLine->setLine(sceneEvent->scenePos().x(), sceneEvent->scenePos().y(),
                                                   sceneEvent->scenePos().x(), sceneEvent->scenePos().y());
                        }

                    }
                    // there is at least one declared vertice in the line
                    else if(singleLine != nullptr){
                        if(polyLine->childItems().isEmpty()){
                            singleLine->setP1(QPointF(singleLine->x2(),
                                                      singleLine->y2()));

                        deleteShadedLinesItem();
                        }else{

                            // this lines take the first vertice of the current line as exactly the second vertice of the previous line

                            singleLine->setP1( singleLine->p2() );
                            deleteShadedLinesItem();
                        }

                        singleLine->setP2(QPointF(
                                                  sceneEvent->scenePos().x(),
                                                  sceneEvent->scenePos().y()
                                                  )
                                          );

                        createShadedLinesItem(sceneEvent->scenePos());
                        if(singleLine->p1() != singleLine->p2()){ // it is not necessary to add lines of 0 distance
        //                    polyLineSource->addLine(new MyQGraphicsLineItem(*singleLine));

                            fnm_core::Core3DSegment *newSegment = new fnm_core::Core3DSegment();
                            newSegment->set_p1(singleLine->x1(), singleLine->y1(), 0);
                            newSegment->set_p2(singleLine->x2(), singleLine->y2(), 0);
                            polyLine->addSegment(newSegment);
                            singleLine = new QLineF(singleLine->x2(),
                                                    singleLine->y2(),
                                                    singleLine->x2(),
                                                    singleLine->y2());
                        }
                    }

                }

        

        // add line source
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["lineSourceMode"])
        {

            // there aren't any declared vertice in the line
            if(singleLine == nullptr){
                createShadedLinesItem(sceneEvent->scenePos());
                singleLine = new QLineF();
                if(multiLineSource == nullptr){
                    multiLineSource = new fnm_ui::MultiLineSource();
                    scene.addItem(multiLineSource);
                    singleLine->setLine(sceneEvent->scenePos().x(), sceneEvent->scenePos().y(),
                                           sceneEvent->scenePos().x(), sceneEvent->scenePos().y());
                }

            }
            // there is at least one declared vertice in the line
            else if(singleLine != nullptr){
                if(multiLineSource->childItems().isEmpty()){
                    singleLine->setP1(QPointF(singleLine->x2(),
                                              singleLine->y2()));

                deleteShadedLinesItem();
                }else{

                    // this lines take the first vertice of the current line as exactly the second vertice of the previous line

                    singleLine->setP1( singleLine->p2() );                    
                    deleteShadedLinesItem();
                }

                singleLine->setP2(QPointF(
                                          sceneEvent->scenePos().x(),
                                          sceneEvent->scenePos().y()
                                          )
                                  );

                createShadedLinesItem(sceneEvent->scenePos());
                if(singleLine->p1() != singleLine->p2()){ // it is not necessary to add lines of 0 distance
//                    polyLineSource->addLine(new MyQGraphicsLineItem(*singleLine));
                    fnm_core::LineSourceSegment *newSourceSegment = new fnm_core::LineSourceSegment();
                    newSourceSegment->set_p1(singleLine->x1(), singleLine->y1(), 0);
                    newSourceSegment->set_p2(singleLine->x2(), singleLine->y2(), 0);
                    newSourceSegment->set_Lw_total(90);
                    multiLineSource->addSegment(newSourceSegment);
                    singleLine = new QLineF(singleLine->x2(),
                                            singleLine->y2(),
                                            singleLine->x2(),
                                            singleLine->y2());
                }
            }
        }


        // add acoustic barrier
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["barrierCursor"]){
            // there aren't any declared vertice in the line
            if(singleLine == nullptr){
                createShadedLinesItem(sceneEvent->scenePos());
                singleLine = new QLineF();
                if(acousticBarrier == nullptr){
                    acousticBarrier = new fnm_ui::Barrier();
                    scene.addItem(acousticBarrier);
                    singleLine->setLine(sceneEvent->scenePos().x(), sceneEvent->scenePos().y(),
                                           sceneEvent->scenePos().x(), sceneEvent->scenePos().y());
                }

            }
            // there is at least one declared vertice in the line
            else if(singleLine != nullptr){
                if(acousticBarrier->childItems().isEmpty()){
                    singleLine->setP1(QPointF(singleLine->x2(),
                                              singleLine->y2()));

                deleteShadedLinesItem();
                }else{

                    // this lines take the first vertice of the current line as exactly the second vertice of the previous line

                    singleLine->setP1( singleLine->p2() );
                    deleteShadedLinesItem();
                }

                singleLine->setP2(QPointF(
                                          sceneEvent->scenePos().x(),
                                          sceneEvent->scenePos().y()
                                          )
                                  );

                createShadedLinesItem(sceneEvent->scenePos());
                if(singleLine->p1() != singleLine->p2()){ // it is not necessary to add lines of 0 distance
                    fnm_core::CoreBarrierSegment *newSourceSegment = new fnm_core::CoreBarrierSegment();
                    newSourceSegment->set_p1(singleLine->x1(), singleLine->y1(), 0);
                    newSourceSegment->set_p2(singleLine->x2(), singleLine->y2(), 0);
                    newSourceSegment->set_height(10);
                    acousticBarrier->addSegment(newSourceSegment);
                    singleLine = new QLineF(singleLine->x2(),
                                            singleLine->y2(),
                                            singleLine->x2(),
                                            singleLine->y2());
                }
            }
        }

        // release polyLine-type opbjects
        else if (sceneEvent->type() == QEvent::GraphicsSceneMousePress
                 && sceneEvent->button() == Qt::RightButton
                 && (ui->graphicsView->cursor()==myCursors["lineSourceMode"]
                     || ui->graphicsView->cursor()==myCursors["barrierCursor"]
                     || ui->graphicsView->cursor()==myCursors["polyLineCursor"])

                 )
        {
            deleteShadedLinesItem();
            releaseLineItemEdition();

        }

        // dropping items
        else if (sceneEvent->type() == QEvent::GraphicsSceneMouseRelease
                 && sceneEvent->button() == Qt::LeftButton
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){
            droppingItemsOnTheScene(sceneEvent);
            deleteShadedLinesItem();
        }
        else if (sceneEvent->type() == QEvent::TouchUpdate
                 && ui->graphicsView->cursor()==myCursors["arrowMode"]){
            // next conditional guarantees that the user dropp any object that
            // currently is dragging before proccessing TouchUpdate event
            deleteShadedLinesItem();
        }

     return QMainWindow::eventFilter(target, event);
    }

    return false;
}



void MainWindow::on_actionAdd_point_source_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["pointSource"]);
    releaseLineItemEdition();

}


void MainWindow::on_actioneditMode_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["arrowMode"]);   
    releaseLineItemEdition();

}

void MainWindow::on_actiongrid_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["gridMode"]);
    releaseLineItemEdition();
}

void MainWindow::on_actioncalculateGrid_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["arrowMode"]);
    resetPixmapArea();
    receivers.resetNoiseReceiver();
    releaseLineItemEdition();


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
    progress.setMaximum(static_cast<int>( receivers.matrix.size()) );
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
    releaseLineItemEdition();

}

void MainWindow::on_actionzoom_full_triggered()
{
    qreal ofsset = 10;
    QRectF rectF = QRectF(myGrid.getRect().x()-ofsset,
                          myGrid.getRect().y()+ofsset,
                          myGrid.getRect().width()+ofsset,
                          myGrid.getRect().height()+ofsset);

    ui->graphicsView->fitInView(rectF,Qt::KeepAspectRatio);
    ui->graphicsView->resetTotalScaleFactor();
}

void MainWindow::on_action_add_line_source_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["lineSourceMode"]);
    releaseLineItemEdition();
}

void MainWindow::on_actionAcoustic_Barrier_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["barrierCursor"]);
    releaseLineItemEdition();
}

void MainWindow::on_actionadd_polyline_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["polyLineCursor"]);
    releaseLineItemEdition();
}

void MainWindow::on_actionAdd_Receiver_triggered()
{
    on_actiondrag_mode_triggered(); // for a weird reason, this is necessary
    ui->graphicsView->setCursor(myCursors["receiver"]);
    releaseLineItemEdition();

}
