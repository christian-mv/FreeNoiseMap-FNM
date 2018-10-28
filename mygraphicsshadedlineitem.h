#ifndef MYGRAPHICSSHADEDLINEITEM_H
#define MYGRAPHICSSHADEDLINEITEM_H

#include<QGraphicsLineItem>


class MyGraphicsShadedLineItem : public QGraphicsLineItem
{
public:
    MyGraphicsShadedLineItem();



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:


};

#endif // MYGRAPHICSSHADEDLINEITEM_H
