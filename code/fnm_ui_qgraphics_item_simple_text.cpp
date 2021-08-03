#include "fnm_ui_qgraphics_item_simple_text.h"
#include <QPainter>


FnmQGraphicsSimpleTextItem::FnmQGraphicsSimpleTextItem(QGraphicsItem *parent)
{
    this->setParentItem(parent);
}

void FnmQGraphicsSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   painter->setPen(Qt::black);
//   painter->drawRect(boundingRect());
   painter->scale(1,-1);
   painter->translate(boundingRect().topLeft().x(), -boundingRect().height());

   QGraphicsSimpleTextItem::paint(painter, option, widget);
}
