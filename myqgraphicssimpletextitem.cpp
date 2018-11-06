#include "myqgraphicssimpletextitem.h"
#include <QPainter>


MyQGraphicsSimpleTextItem::MyQGraphicsSimpleTextItem(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

void MyQGraphicsSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   painter->setPen(Qt::black);
   painter->drawRect(boundingRect());
   painter->scale(1,-1);
   painter->translate(boundingRect().topLeft().x(), -boundingRect().height());

   QGraphicsSimpleTextItem::paint(painter, option, widget);
}
