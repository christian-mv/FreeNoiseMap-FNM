#include "mygraphicsshadedlineitem.h"
#include <QPainter>
#include <QDebug>
#include <QLineF>
#include <cmath>
#include <QColor>
#include <QStaticText>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTransform>

MyGraphicsShadedLineItem::MyGraphicsShadedLineItem()
{
    myFont.setPointSize(10);
    QFontMetrics fm(myFont);
    widthOfText = fm.width("www");

    distanceText = new MyQGraphicsSimpleTextItem(this);
    horizontalText = new MyQGraphicsSimpleTextItem(this);
    verticalText = new MyQGraphicsSimpleTextItem(this);

//    distanceText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    horizontalText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    verticalText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);


}

QRectF MyGraphicsShadedLineItem::boundingRect() const
{
    return QGraphicsLineItem::boundingRect().adjusted(-widthOfText,-widthOfText,widthOfText,widthOfText);
}


void MyGraphicsShadedLineItem::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *widget)
{
    // set painter for lines
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(QColor(0,0,0,200));
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setCosmetic(true); // line doesn't change when zoomming
    painter->setPen(pen);
    painter->setFont(myFont);


    // draw lines
    updateShadedLines();
    drawLines(painter);


    // distance text.
    textContainer = QString("d:")+QString::number(line().length(),'d',1)+QString("m");
    distanceText->setText(textContainer);
    distanceText->setPos(line().center());


    // horizontal text
    textContainer = QString("dx:")+QString::number(line().dx(),'d',1)+QString("m");
    horizontalText->setText(textContainer);
    horizontalText->setPos(this->mapToItem(this, line2.center()));
    horizontalText->show();

    // vertical text
    textContainer = QString("dy:")+QString::number(line().dy(),'d',1)+QString("m");
    verticalText->setText(textContainer);
    verticalText->setPos(this->mapToItem(this, line1.center()));
    verticalText->show();



    // scale textsItems
    distanceText->setScale(1/scene()->views().first()->transform().m11());
    horizontalText->setScale(1/scene()->views().first()->transform().m11());
    verticalText->setScale(1/scene()->views().first()->transform().m11());



    // this corrects positions:


    if(distanceText->collidesWithItem(verticalText,Qt::IntersectsItemBoundingRect) && verticalText->collidesWithItem(horizontalText,Qt::IntersectsItemBoundingRect)){
        textContainer = QString("d:")+QString::number(line().length(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dx:")+QString::number(line().dx(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dy:")+QString::number(line().dy(),'d',1)+QString("m");
        verticalText->hide();
        horizontalText->hide();
        distanceText->setText(textContainer);
        distanceText->setPos(line().center());
    }

    if(verticalText->collidesWithItem(distanceText,Qt::IntersectsItemBoundingRect)){// vertical text and distance text

        verticalText->setPos(verticalText->x(),verticalText->y()-distanceText->sceneBoundingRect().height());

    }

    if(verticalText->collidesWithItem(horizontalText,Qt::IntersectsItemBoundingRect)){// vertical text and distance text

        verticalText->setPos(horizontalText->x(),horizontalText->y()-horizontalText->sceneBoundingRect().height());
    }


    if(horizontalText->collidesWithItem(distanceText,Qt::IntersectsItemBoundingRect)){ // horizontal text and distance text

        horizontalText->setPos(distanceText->x(),distanceText->y()-distanceText->sceneBoundingRect().height());
    }





//    // set painter fpainter->fontMetrics().height()or text
//    pen.setColor(Qt::black);
//    painter->setPen(pen);
//    QString text;
//    QRectF text_rect;


//    // text
//    text = QString("d:")+QString::number(line().length(),'d',1)+QString("m");


//    text_rect = painter->fontMetrics().boundingRect(text);

//    text_rect.translate(line().center());
//    int offset = painter->fontMetrics().width("x");





//    // distance text.
////    if(boundingRect().contains(text_rect) && line().length() > text_rect.width()){
//        painter->save();
//    //        painter->translate(line().center().x(), line().center().y()+painter->fontMetrics().height());
//        painter->translate(line2.center().x(),line1.center().y());
//        painter->scale(1.0, -1.0);
//        painter->rotate(-theta());
//        painter->drawText(0,0, text);
//        painter->restore();

////    }


//    // dx text
//    text = QString("x:")+QString::number(line().dx(),'d',1)+QString("m");
//    text_rect = painter->fontMetrics().boundingRect(text);
//    text_rect.translate(line().center());



//    if(boundingRect().contains(text_rect) && qAbs(line().dx()) > text_rect.width()){
//        painter->save();
//        painter->translate(line2.center());
//        painter->scale(1.0, -1.0);

//        if(line().dy()>0){
//            painter->drawText(0,0, text);
//        }else{
//            painter->drawText(0,-painter->fontMetrics().height(), text);
//        }

//        painter->restore();
//    }

//    // dy text
//    text = QString("y:")+QString::number(line().dy(),'d',1)+QString("m");
//    text_rect = painter->fontMetrics().boundingRect(text);
//    text_rect.translate(line().center());


//    if(boundingRect().contains(text_rect) && 2*qAbs(line().dy()) > text_rect.width()){
//        painter->save();
//        painter->translate(line1.center());
//        painter->scale(1.0, -1.0);

//        if(line().dx()>0){
//            painter->drawText(offset,0, text);
//        }else{
//            painter->drawText(-painter->fontMetrics().width(text),0, text);
//        }

//        painter->restore();
//    }

//    // theta text
//    text = QString::number(qAbs(theta()),'d',1)+QString("°");
//    text_rect = painter->fontMetrics().boundingRect(text);
//    text_rect.adjust(-0.80*text_rect.width(),-0.80*text_rect.width(),
//                     0.80*text_rect.width(),0.80*text_rect.width());

//    text_rect.translate(line().p1());



//    if(boundingRect().contains(text_rect) && line().length() > text_rect.width()){

//        painter->save();
//        painter->translate(line().p1());

//        painter->scale(1.0, -1.0);

//        if(line().dx()>=0){
//            painter->drawArc(-text_rect.width()/2,-text_rect.width()/2,
//                             text_rect.width(),text_rect.width(),0,16*theta());
//        }else if(line().dx()<0){
//            painter->drawArc(-text_rect.width()/2,-text_rect.width()/2,
//                             text_rect.width(),text_rect.width(),16*180,16*theta());
//        }



//        if(line().dx()>=0 && line().dy()<0){
//            painter->drawText(offset,0, text);
//        }else if(line().dx()>=0 && line().dy()>0){
//            painter->drawText(offset,-painter->fontMetrics().height(), text);
//        }else if(line().dx()<=0 && line().dy()>0){
//            painter->drawText(-painter->fontMetrics().width(text)-offset,-painter->fontMetrics().height(), text);
//        }else if(line().dx()<=0 && line().dy()<0){
//            painter->drawText(-painter->fontMetrics().width(text)-offset,0, text);
//        }


//        painter->restore();
//    }


}

double MyGraphicsShadedLineItem::theta() const
{
    // return angle between this.line1 and this.line2
    return atan(line().dy()/line().dx())* 180 / 3.14159265;
}

void MyGraphicsShadedLineItem::updateShadedLines()
{
    if(line().dx()>0 && line().dy()>0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(),line1.p1());
    }else if(line().dx()<0 && line().dy()>0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(),line1.p1());
    }else if(line().dx()<0 && line().dy()<0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(), line1.p1());
    }else if(line().dx()>0 && line().dy()<0){
        line1.setLine(line().p2().x(), line().p1().y(), line().p2().x(), line().p2().y());
        line2.setPoints(line().p1(), line1.p1());
    }
}

void MyGraphicsShadedLineItem::drawLines(QPainter *painter) const
{
    painter->drawLine(line()); //diagonal
    painter->drawLine(line1);  // horizontal line
    painter->drawLine(line2); // vertical line
    //        painter->drawRect(boundingRect()); // drawRectangle
}

void MyGraphicsShadedLineItem::drawText()
{

}



void MyGraphicsShadedLineItem::updateWidOfText(const QPainter *p)
{
    widthOfText = p->fontMetrics().width("x: 9999.999m");
    prepareGeometryChange();
}




