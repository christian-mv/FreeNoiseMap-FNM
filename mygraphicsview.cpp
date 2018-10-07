#include "mygraphicsview.h"
#include <QDebug>
#include <QPointF>
#include <QScrollBar>

MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    setDragMode(ScrollHandDrag);
//    setAlignment(Qt::AlignLeft | Qt::AlignTop );

}

void MyGraphicsView::setCursor(const QCursor &newCursor)
{
    if(newCursor == Qt::OpenHandCursor){
        setDragMode(ScrollHandDrag);

    }else{
        setDragMode(NoDrag);
    }

    QGraphicsView::setCursor(newCursor);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    const qreal factor = 1.1;
    if (event->angleDelta().y() > 0)
        scale(factor, factor);
    else
        scale(1/factor, 1/factor);
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











