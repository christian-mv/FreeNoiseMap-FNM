#ifndef MYGRAPHICSSHADEDLINEITEM_H
#define MYGRAPHICSSHADEDLINEITEM_H

#include<QGraphicsLineItem>
#include<QFont>


class MyQGraphicsSimpleTextItem;

class MyGraphicsShadedLineItem : public QGraphicsLineItem
{
public:
    MyGraphicsShadedLineItem();
    QRectF boundingRect() const override;



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    QLineF line1, line2;

    MyQGraphicsSimpleTextItem *distanceText;
    MyQGraphicsSimpleTextItem *horizontalText;
    MyQGraphicsSimpleTextItem *verticalText;
    MyQGraphicsSimpleTextItem *degreesText;

    double theta() const;
    void updateShadedLines();
    void drawLines(QPainter *painter) const;
    void drawText();
    QString textContainer;


};

#endif // MYGRAPHICSSHADEDLINEITEM_H
