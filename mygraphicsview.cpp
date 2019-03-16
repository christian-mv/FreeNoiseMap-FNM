#include "mygraphicsview.h"
#include <QDebug>
#include <QPointF>
#include <QScrollBar>
#include <QGraphicsItem>
#include <cmath>

MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);

//    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);


//    setAlignment(Qt::AlignLeft | Qt::AlignTop );

    totalScaleFactor = 1;

}

void MyGraphicsView::setCursor(const QCursor &newCursor)
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


    QGraphicsView::setCursor(newCursor);
}





void MyGraphicsView::wheelEvent(QWheelEvent *e)
{

    double zoomFactor = 1.25;

    if ( e->delta() == 0 )
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
bool MyGraphicsView::viewportEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:

        {
            setDragMode(ScrollHandDrag);
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
            if (touchPoints.count() == 2) {
                // determine scale factor
                const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
                const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
                qreal currentScaleFactor =
                        QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                        / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
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
    return QGraphicsView::viewportEvent(event);
}




//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//    if (m_pressed){
//        QPoint diff = m_lastMousePos - event->pos();
//        if (QScrollBar *hbar = horizontalScrollBar())
//            hbar->setValue(hbar->value() + diff.x());
//        if (QScrollBar *vbar = verticalScrollBar())
//            vbar->setValue(vbar->value() + diff.y());
//        m_lastMousePos = event->pos();
//    }

//    QGraphicsView::mouseMoveEvent(event);
//}

//void MyGraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    if (Qt::LeftButton == event->button()) {
//        m_pressed = true;
//        m_lastMousePos = event->pos();
//    }

//    QGraphicsView::mousePressEvent(event);
//}

//void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (Qt::LeftButton == event->button()){
//        m_pressed = false;
//    }

//    QGraphicsView::mouseReleaseEvent(event);
//}


