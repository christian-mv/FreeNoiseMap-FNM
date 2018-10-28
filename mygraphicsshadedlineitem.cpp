#include "mygraphicsshadedlineitem.h"
#include <QPainter>
#include <QDebug>
#include <QLineF>
#include <cmath>
#include <QColor>
#include <QStaticText>


MyGraphicsShadedLineItem::MyGraphicsShadedLineItem()
{

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
    painter->drawRect(QGraphicsLineItem::boundingRect());




//    QFontMetrics fm = painter->fontMetrics();
//    QRectF rectText(boundingRect().center().x(),boundingRect().center().y(),fm.width("999.9999"), fm.height());



    QFont font = painter->font();



    // reduce size
    while(font.pointSize()>1){
        if(line().length()/2 < painter->fontMetrics().width("999.9999")
                || qAbs(line().dy()) < painter->fontMetrics().height()){

            font.setPointSize(font.pointSize()-1);
            painter->setFont(font);

        }
        else{
            break;
        }
    }

    // increase size



    qDebug()<<"fontMetrics().height(): "<<painter->fontMetrics().height();


    if(line().length()>1.5*painter->fontMetrics().width("999.9999m")
            && qAbs(line().dy())>1.5*painter->fontMetrics().height()
            && qAbs(line().dx())>painter->fontMetrics().width("999.9999m") ){

        painter->translate(line().center().x(), line().center().y()+painter->fontMetrics().height());
        painter->scale(1.0, -1.0);
        painter->rotate(-theta);

        QStaticText staticText(QString::number(line().length())+QString("m"));


        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->drawStaticText(-painter->fontMetrics().width("999.9999"),0, staticText);

    }


    //    painter->drawLine(line2);
    //    painter->drawLine(boundingRect().topLeft(), boundingRect().topRight());



    //    QGraphicsLineItem::paint(painter, option, widget);
}


