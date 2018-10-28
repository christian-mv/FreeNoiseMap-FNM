#include "mygraphicsshadedlineitem.h"
#include <QPainter>
#include <QDebug>
#include <QLineF>
#include <cmath>
#include <QColor>
#include <QStaticText>


MyGraphicsShadedLineItem::MyGraphicsShadedLineItem()
{
    font.setPointSize(10);
    QFontMetrics fm(font);
    widthOfText = fm.width("999.999m");
}

QRectF MyGraphicsShadedLineItem::boundingRect() const
{
    return QGraphicsLineItem::boundingRect().adjusted(-widthOfText,-widthOfText,widthOfText,widthOfText);
}


void MyGraphicsShadedLineItem::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(QColor(0,0,0,125));
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setCosmetic(true); // line doesn't change when zoomming
    painter->setPen(pen);
    painter->setFont(font);





    double x = mapToScene(line().p2()).x() - mapToScene(line().p1()).x();
    double y = mapToScene(line().p2()).y() - mapToScene(line().p1()).y();
    double theta = atan(y/x)* 180 / 3.14159265;


    QLineF line1, line2;
    if(x>0 && y>0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(),line1.p1());
    }else if(x<0 && y>0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(),line1.p1());
    }else if(x<0 && y<0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(), line1.p1());
    }else if(x>0 && y<0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(), line1.p1());
    }




    // diagonal line

    painter->drawLine(line());



    painter->drawLine(line1);  // horizontal line
    painter->drawLine(line2); // vertical line
//    painter->drawRect(boundingRect());



    QString text(QString::number(line().length())+QString("m"));
    QRectF text_rect = painter->fontMetrics().boundingRect(text);
    text_rect.translate(line().center());

    QStaticText staticText(text);


    if(boundingRect().contains(text_rect)){

        painter->translate(line().center().x(), line().center().y()+painter->fontMetrics().height());
        painter->scale(1.0, -1.0);
        painter->rotate(-theta);

        pen.setColor(Qt::black);
        painter->setPen(pen);


        painter->drawStaticText(-widthOfText,0, staticText);

    }


    //    painter->drawLine(line2);
    //    painter->drawLine(boundingRect().topLeft(), boundingRect().topRight());



    //    QGraphicsLineItem::paint(painter, option, widget);
}


