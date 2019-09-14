#ifndef FNM_UI_QGRAPHICS_SIMPLE_TEXT_ITEM_H
#define FNM_UI_QGRAPHICS_SIMPLE_TEXT_ITEM_H

#include<QGraphicsSimpleTextItem>

class FnmQGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:

    FnmQGraphicsSimpleTextItem(QGraphicsItem *parent = nullptr);

protected:

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // MYQGRAPHICSSIMPLETEXTITEM_H
