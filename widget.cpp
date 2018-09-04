#include "widget.h"
#include <QPainter>
#include <QVector>

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


    this->drawMargin();


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);


    QRectF rectangle = QRectF(50, 50, 100, 100);
    drawNoiseCell(&painter, Qt::green, rectangle);
//    QRectF myMargin = rect().adjusted(10, 10, -10, -10);
//    QRectF r2 = QRectF(50, 50, 100, 100);
//    QVector<QRectF> v;
//    v<<myMargin<<r2;
//    painter.drawRects(v);
}

void Widget::drawNoiseCell(QPainter *painter, QColor color, QRectF rect)
{
    painter->setBrush(color);
    painter->drawRect(rect);
}


void Widget::drawMargin(int dx1, int dy1, int dx2, int dy2)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    QRectF myMargin = rect().adjusted(dx1, dy1, -dx2, -dy2);
    painter.drawRect(myMargin);
}



