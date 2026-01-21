#include <QPainter>
#include <QDebug>
#include <QLineF>
#include <cmath>
#include <QColor>
#include <QStaticText>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTransform>
#include "qgraphics_item_shaded_line.h"
#include "qgraphics_item_simple_text.h"


FnmGraphicsItemShadedLine::FnmGraphicsItemShadedLine()
{
    distanceText = new FnmQGraphicsSimpleTextItem(this);
    horizontalText = new FnmQGraphicsSimpleTextItem(this);
    verticalText = new FnmQGraphicsSimpleTextItem(this);
    degreesText = new FnmQGraphicsSimpleTextItem(this);

//    distanceText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    horizontalText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    verticalText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

}

QRectF FnmGraphicsItemShadedLine::boundingRect() const
{

    // expandimos un poco el rectangulo para garantizar que el
    // renderizado en cada operación se abarca completament cuando
    // se hacen movimientos rápidos con el mouse.
    return QGraphicsLineItem::boundingRect().adjusted(-0.01*line().length(),
                                                      -0.01*line().length(),
                                                      0.01*line().length(),
                                                      0.01*line().length());
}


void FnmGraphicsItemShadedLine::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // set painter for lines
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(QColor(0,0,0,200));
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setCosmetic(true); // line doesn't change when zoomming
    painter->setPen(pen);


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

    // degrees text
    static double offset;
    offset = 0.15*line().dx();
    textContainer = QString("θ:")+QString::number(qAbs(theta()),'d',1)+QString("°");
    degreesText->setText(textContainer);
    degreesText->setPos(this->mapToItem(this, line().p1().x()+offset/2,
                                        line().p1().y()));
    degreesText->show();



    // scale textsItems
    distanceText->setScale(1/scene()->views().first()->transform().m11());
    horizontalText->setScale(1/scene()->views().first()->transform().m11());
    verticalText->setScale(1/scene()->views().first()->transform().m11());
    degreesText->setScale(1/scene()->views().first()->transform().m11());

    // ellipse text

    //    // theta text

        QRectF text_rect = QRectF(0, 0,2*offset, 2*offset);

        text_rect.adjust(-0.80*text_rect.width(),-0.80*text_rect.width(),
                         0.80*text_rect.width(),0.80*text_rect.width());

        text_rect.translate(line().p1());


        painter->translate(line().p1());

        painter->scale(1.0, -1.0);

        QRectF archRect(-text_rect.width()/2,-text_rect.width()/2,
                        text_rect.width(),text_rect.width());

        if(line().dx()>=0){

            painter->drawArc(archRect,0,static_cast<int>(16*theta()));

        }else if(line().dx()<0){

            painter->drawArc(archRect,16*180,static_cast<int>(16*theta()));

        }


    // this corrects positions of some items:


    if(distanceText->collidesWithItem(verticalText,Qt::IntersectsItemBoundingRect) && verticalText->collidesWithItem(horizontalText,Qt::IntersectsItemBoundingRect)){
        textContainer = QString("d:")+QString::number(line().length(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dx:")+QString::number(line().dx(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dy:")+QString::number(line().dy(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("θ:")+QString::number(qAbs(theta()),'d',1)+QString("°");
        verticalText->hide();
        horizontalText->hide();
        degreesText->hide();
        distanceText->setText(textContainer);
        distanceText->setPos(line().p2().x()+offset,line().p2().y()+offset);
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

    if(horizontalText->collidesWithItem(degreesText,Qt::IntersectsItemBoundingRect)){ // horizontal text and degrees text

        degreesText->setPos(degreesText->x(),degreesText->y()-horizontalText->sceneBoundingRect().height());
    }

    if(verticalText->collidesWithItem(degreesText,Qt::IntersectsItemBoundingRect)){ // horizontal text and degrees text

        degreesText->setPos(verticalText->x(),degreesText->y()-verticalText->sceneBoundingRect().height());
    }

    if(distanceText->collidesWithItem(degreesText,Qt::IntersectsItemBoundingRect)){ // horizontal text and degrees text

        textContainer = QString("d:")+QString::number(line().length(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dx:")+QString::number(line().dx(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("dy:")+QString::number(line().dy(),'d',1)+QString("m");
        textContainer = textContainer + "\n" + QString("θ:")+QString::number(qAbs(theta()),'d',1)+QString("°");
        verticalText->hide();
        horizontalText->hide();
        degreesText->hide();
        distanceText->setText(textContainer);
        if(line().dx()>=0){
            distanceText->setPos(line().p2().x()+offset,line().p2().y()+offset);
        }else if(line().dx()<0 && line().dy()>=0){
            distanceText->setPos(line().p2().x()-offset,line().p2().y()-offset);

        }else if(line().dx()<0 && line().dy()<0){
            distanceText->setPos(line().p2().x(),
                                 line().p2().y()+distanceText->boundingRect().height()/2);
        }

    }

}

double FnmGraphicsItemShadedLine::theta() const
{
    // return angle between this.line1 and this.line2
    return atan(line().dy()/line().dx())* 180 / 3.14159265;
}

void FnmGraphicsItemShadedLine::updateShadedLines()
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

void FnmGraphicsItemShadedLine::drawLines(QPainter *painter) const
{
    painter->drawLine(line()); //diagonal
    painter->drawLine(line1);  // horizontal line
    painter->drawLine(line2); // vertical line
//            painter->drawRect(boundingRect()); // drawRectangle
}







