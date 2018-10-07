#include "mygraphicsview.h"
#include <QDebug>
#include <QPointF>

MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    setAlignment(Qt::AlignLeft | Qt::AlignTop );

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    const qreal factor = 1.1;
    qDebug()<<event->angleDelta().y();
    if (event->angleDelta().y() > 0)
        scale(factor, factor);
    else
        scale(1/factor, 1/factor);
}











