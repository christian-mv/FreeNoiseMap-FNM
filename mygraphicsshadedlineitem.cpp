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
    widthOfText = fm.width("x: 9999.999m");
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
    QPen pen(QColor(0,0,0,200));
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




    pen.setColor(Qt::black);
    painter->setPen(pen);
    QStaticText staticText;
    QString text;
    QRectF text_rect;

    // distance text
    text = QString("d: ")+QString::number(line().length())+QString("m");
    text_rect = painter->fontMetrics().boundingRect(text);
    text_rect.translate(line().center());
    int offset = painter->fontMetrics().width("x");

    staticText.setText(text);

    if(boundingRect().contains(text_rect) && 1.5*line().length() > text_rect.width()){
        painter->save();
//        painter->translate(line().center().x(), line().center().y()+painter->fontMetrics().height());
        painter->translate(line2.center().x(),line1.center().y());
        painter->scale(1.0, -1.0);
        painter->rotate(-theta);               
        painter->drawStaticText(0,0, staticText);
        painter->restore();
    }

    // dx text
    text = QString("x: ")+QString::number(line().dx(),'d',2)+QString("m");
    text_rect = painter->fontMetrics().boundingRect(text);
    text_rect.translate(line().center());

    staticText.setText(text);

    if(boundingRect().contains(text_rect) && qAbs(line().dx()) > text_rect.width()){
        painter->save();
        painter->translate(line2.center());
        painter->scale(1.0, -1.0);

        if(line().dy()>0){
            painter->drawStaticText(0,0, staticText);
        }else{
            painter->drawStaticText(0,-painter->fontMetrics().height(), staticText);
        }

        painter->restore();
    }

    // dy text
    text = QString("y: ")+QString::number(line().dy(),'d',2)+QString("m");
    text_rect = painter->fontMetrics().boundingRect(text);
    text_rect.translate(line().center());

    staticText.setText(text);

    if(boundingRect().contains(text_rect) && 2*qAbs(line().dy()) > text_rect.width()){
        painter->save();
        painter->translate(line1.center());
        painter->scale(1.0, -1.0);

        if(line().dx()>0){
            painter->drawStaticText(offset,0, staticText);
        }else{
            painter->drawStaticText(-painter->fontMetrics().width(text),0, staticText);
        }

        painter->restore();
    }

    // theta text
    text = QString::number(qAbs(theta),'d',1)+QString("°");
    text_rect = painter->fontMetrics().boundingRect(text);
    text_rect.adjust(-0.80*text_rect.width(),-0.80*text_rect.width(),
                     0.80*text_rect.width(),0.80*text_rect.width());

    text_rect.translate(line().p1());

    staticText.setText(text);

    if(boundingRect().contains(text_rect) && line().length() > text_rect.width()){

        painter->save();
        painter->translate(line().p1());

        painter->scale(1.0, -1.0);

        if(line().dx()>=0){
            painter->drawArc(-text_rect.width()/2,-text_rect.width()/2,
                             text_rect.width(),text_rect.width(),0,16*theta);
        }else if(line().dx()<0){
            painter->drawArc(-text_rect.width()/2,-text_rect.width()/2,
                             text_rect.width(),text_rect.width(),16*180,16*theta);
        }



        if(line().dx()>=0 && line().dy()<0){
            painter->drawStaticText(offset,0, staticText);
        }else if(line().dx()>=0 && line().dy()>0){
            painter->drawStaticText(offset,-painter->fontMetrics().height(), staticText);
        }else if(line().dx()<=0 && line().dy()>0){
            painter->drawStaticText(-painter->fontMetrics().width(text)-offset,-painter->fontMetrics().height(), staticText);
        }else if(line().dx()<=0 && line().dy()<0){
            painter->drawStaticText(-painter->fontMetrics().width(text)-offset,0, staticText);
        }


        painter->restore();
    }


}


