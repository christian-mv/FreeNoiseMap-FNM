#include "mygraphicsview.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPointF>

MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{

}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<event;
}
