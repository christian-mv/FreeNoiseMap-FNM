#include "widget.h"
#include <QPainter>
#include <QRegion>
#include <QPaintEvent>
#include "noise_engine.h"
#include <QRectF>
#include <QtWidgets>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    this->drawMargin();

    QPainter painter(this);

    painter.drawImage(rect(),*image,image->rect());
}


