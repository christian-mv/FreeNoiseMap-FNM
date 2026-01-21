#include "simple_text_item.h"
#include <QPainter>

namespace fnm_ui {

SimpleTextItem::SimpleTextItem(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

void SimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   painter->setPen(Qt::black);
//   painter->drawRect(boundingRect());
   painter->scale(1,-1);
   painter->translate(boundingRect().topLeft().x(), -boundingRect().height());

   ::QGraphicsSimpleTextItem::paint(painter, option, widget);
}

}