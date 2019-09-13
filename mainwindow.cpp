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
#include "my_qgraphics_multiline_source_item.h"
#include "my_qgraphics_acoustic_barrier_item.h"
#include "fnm_multiLine_graphics_Item.h"

#define VERSION_OF_APP "beta"
#define MY_APP_NAME "Free Noise Map"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
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


    auto polyLineCursorPixmap = QPixmap(":/images/icons/polyline_cursor.png").scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    myCursors["barrierCursor"] = QCursor( polyLineCursorPixmap.copy() );
    myCursors["polyLineCursor"] = QCursor( polyLineCursorPixmap.copy() );
    myCursors["lineSourceMode"] = QCursor( polyLineCursorPixmap.copy() );

    myCursors["arrowMode"] = QCursor(Qt::ArrowCursor);
    myCursors["editMode"] = QCursor(Qt::PointingHandCursor);
    myCursors["gridMode"] = QCursor(Qt::CrossCursor);
    myCursors["dragMode"] = QCursor(Qt::OpenHandCursor);

    myCursors["pointSource"] = QCursor(
                QPixmap(":/images/icons/target.png").scaled(20,20,Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

void MainWindow::makeMenuMutualExclusive()
{
    auto actionsList = ui->toolBar->actions();
    static QActionGroup alignmentGroup(this);
    qDebug()<<"action";
    for(auto action: actionsList){
        action->setCheckable(true);
        alignmentGroup.addAction(action);
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
    qreal side2 = qMax(qApp->desktop()->width(), qApp->desktop()->height());

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
            if( (moving_item->type() == FNM_TypeId::MultiLineSourceItemType
                 || moving_item->type() == FNM_TypeId::AcousticBarrierItemType
                 || moving_item->type() == FNM_TypeId::PolyLineItemType)
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
        shaded_line = new MyGraphicsShadedLineItem;
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
        double temp = NoiseEngine::distanceBetweenPoints(p1.x(),p1.y(),0, p2.x(),p2.y(), 0);

        if(temp>0.1){
            item_released->setPos(sceneEvent->scenePos()); // this correct the position to be more acurate
        }
    }

}

bool MainWindow::isThereNoiseSources() const
{
    for(auto item: scene.items()){
        if(item->type()== FNM_TypeId::PointSourceItemType ||
                item->type()== FNM_TypeId::MultiLineSourceItemType)
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

        PointSourcePixmapItem *currentPixmapItemPointSource;
        MyQGraphicsMultiLineSource *currentLineSource;
        auto barriersSegments = barrierSegmentsToStdVector();
//        MinimalAcousticBarrier* barrierSegment;

        for(auto currentReceiver : receivers.matrix.at(i)){           
            for(auto currentItem : scene.items()){
                // noise from point sources
                if(currentItem->type() == FNM_TypeId::PointSourceItemType){
                    currentPixmapItemPointSource = (static_cast<PointSourcePixmapItem *>(currentItem));

                    NoiseEngine::P2P(currentPixmapItemPointSource->getPointSource(),
                                                             currentReceiver, barriersSegments);


                }
                // noise from line sources
                if(currentItem->type() == FNM_TypeId::MultiLineSourceItemType){
                    currentLineSource = (static_cast<MyQGraphicsMultiLineSource *>(currentItem));
                    // Here we iterate a multi line source to obtain a list of
                    // segmets, then each segment is split in point sources
                    for(FnmLineSegmentSource *segment: currentLineSource->getSegments()){
                        for(MinimalPointSource subPointSource: NoiseEngine::fromLineToPointSources(segment,22.0)){
                            NoiseEngine::P2P(&subPointSource, currentReceiver, barriersSegments);
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

QList<MyQGraphicsAcousticBarrierItem *> MainWindow::barrierList() const
{
    QList<MyQGraphicsAcousticBarrierItem *> barriers;
    for(auto item: scene.items()){
        if(item->type() == FNM_TypeId::AcousticBarrierItemType){
            barriers.append(static_cast<MyQGraphicsAcousticBarrierItem *>(item));
        }
    }
    return barriers;
}

std::vector<FnmAcousticBarrierSegment *> MainWindow::barrierSegmentsToStdVector() const
{
    std::vector<FnmAcousticBarrierSegment *> segments;
    QVector<FnmAcousticBarrierSegment*> temp;

    for(auto item: scene.items()){
        if(item->type() == FNM_TypeId::AcousticBarrierItemType){
            temp = (static_cast<MyQGraphicsAcousticBarrierItem *>(item)->getBarrierSegments());
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

            MinimalPointSource *myPointSource = new MinimalPointSource(
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

            PointSourcePixmapItem * myPixmapPointSourceItem = new PointSourcePixmapItem();

            myPixmapPointSourceItem->setPixmap(myPixmap);
            myPixmapPointSourceItem->setPointSource(myPointSource);


            scene.addItem(myPixmapPointSourceItem);
            deleteShadedLinesItem();

          }

        // drag point source
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
                case FNM_TypeId::MultiLineSourceItemType:
                    break;
                case FNM_TypeId::AcousticBarrierItemType:
                    break;
                case FNM_TypeId::PolyLineItemType:
                    break;
                default:
                    createShadedLinesItem(sceneEvent->scenePos());
                    break;
                }
            }
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
                            polyLine = new FnmPolyLineGraphicsItem();
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

                            Fnm3DSegment *newSegment = new Fnm3DSegment();
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
                    multiLineSource = new MyQGraphicsMultiLineSource();
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
                    FnmLineSegmentSource *newSourceSegment = new FnmLineSegmentSource();
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
                    acousticBarrier = new MyQGraphicsAcousticBarrierItem();
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
                    acousticBarrier->addBarrierSegment(*singleLine, 10);
                    singleLine = new QLineF(singleLine->x2(),
                                            singleLine->y2(),
                                            singleLine->x2(),
                                            singleLine->y2());
                }
            }
        }

        // release polyLine or line source or acoustic barrier edition
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
