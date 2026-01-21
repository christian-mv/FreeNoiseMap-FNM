#include "simple_text.h"
#include <QPainter>

namespace fnm {

QGraphicsSimpleTextItem::QGraphicsSimpleTextItem(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

void QGraphicsSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   painter->setPen(Qt::black);
//   painter->drawRect(boundingRect());
   painter->scale(1,-1);
   painter->translate(boundingRect().topLeft().x(), -boundingRect().height());

   ::QGraphicsSimpleTextItem::paint(painter, option, widget);
}

}