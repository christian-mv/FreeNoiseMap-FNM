#include "fnm_view.h"
#include <QDebug>
#include <QPointF>
#include <QScrollBar>
#include <QGraphicsItem>
#include <cmath>

namespace fnm_ui {

FnmView::FnmView(QWidget *parent):
    ::QGraphicsView(parent),
    totalScaleFactor(1)
{
    setTransformationAnchor(::QGraphicsView::AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);

//    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);


//    setAlignment(Qt::AlignLeft | Qt::AlignTop );

}

void FnmView::setCursor(const QCursor &newCursor)
{

//    QList<QGraphicsItem *> sceneItems = items();
    if(newCursor == Qt::OpenHandCursor){        
        setDragMode(ScrollHandDrag);        

    }else{
        setDragMode(NoDrag);
//        for(auto item: sceneItems){
//            if(item->type() != 65536){ // 65536 represents our MyRasterPixmapItemArea
//                item->setFlag(QGraphicsItem::ItemIsMovable, true);
//            }
//        }

    }

//    if(newCursor != Qt::ArrowCursor){
//        this->setMouseTracking(false);
//        for(auto item: sceneItems){
//            if(item->type() != 65536){ // 65536 represents our MyRasterPixmapItemArea
//                item->setAcceptHoverEvents(false);
//            }
//        }
//    }else if(newCursor == Qt::ArrowCursor){
//        this->setMouseTracking(true);
//        for(auto item: sceneItems){
//            if(item->type() != 65536){ // 65536 represents our MyRasterPixmapItemArea
//                item->setAcceptHoverEvents(true);
//            }
//        }
//    }


    ::QGraphicsView::setCursor(newCursor);
}

void FnmView::resetTotalScaleFactor()
{
    totalScaleFactor = 1;
}





void FnmView::wheelEvent(QWheelEvent *e)
{

    double zoomFactor = 1.25;

    if ( e->angleDelta().y() == 0 )
    {
      e->accept();
      return;
    }


    // "Normal" mouse have an angle delta of 120, precision mouses provide data faster, in smaller steps
    zoomFactor = 1.0 + ( zoomFactor - 1.0 ) / 120.0 * std::fabs( e->angleDelta().y() );

    if ( e->modifiers() & Qt::ControlModifier )
    {
      //holding ctrl while wheel zooming results in a finer zoom
      zoomFactor = 1.0 + ( zoomFactor - 1.0 ) / 20.0;
    }

    qreal signedWheelFactor = e->angleDelta().y() > 0 ?  zoomFactor : 1 / zoomFactor;

    // zoom map to mouse cursor by scaling

    scale(signedWheelFactor, signedWheelFactor);
//    centerOn(mapToScene(e->pos()));
    e->accept();
}


// this method provides support for zooming in touch screens
// reference: http://doc.qt.io/archives/qt-4.8/qt-touch-pinchzoom-example.html
bool FnmView::viewportEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:

        {
            setDragMode(ScrollHandDrag);
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            QList<QEventPoint> touchPoints = touchEvent->points();
            if (touchPoints.count() == 2) {
                // determine scale factor
                const QEventPoint &touchPoint0 = touchPoints.first();
                const QEventPoint &touchPoint1 = touchPoints.last();
                qreal currentScaleFactor =
                        QLineF(touchPoint0.position(), touchPoint1.position()).length()
                        / QLineF(touchPoint0.pressPosition(), touchPoint1.pressPosition()).length();
                if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
                    // if one of the fingers is released, remember the current scale
                    // factor so that adding another finger later will continue zooming
                    // by adding new scale factor to the existing remembered value.
                    totalScaleFactor *= currentScaleFactor;
                    currentScaleFactor = 1;
                }

                setTransform(QTransform().scale(totalScaleFactor * currentScaleFactor,
                                                -totalScaleFactor * currentScaleFactor));

            }
        }
        break;
    default:
        break;
    }
    return ::QGraphicsView::viewportEvent(event);
}

}
