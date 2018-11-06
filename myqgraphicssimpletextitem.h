#ifndef MYQGRAPHICSSIMPLETEXTITEM_H
#define MYQGRAPHICSSIMPLETEXTITEM_H

#include<QGraphicsSimpleTextItem>

class MyQGraphicsSimpleTextItem : public QGraphicsSimpleTextItem
{
public:

    MyQGraphicsSimpleTextItem(QGraphicsItem *parent = nullptr);

protected:

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // MYQGRAPHICSSIMPLETEXTITEM_H
