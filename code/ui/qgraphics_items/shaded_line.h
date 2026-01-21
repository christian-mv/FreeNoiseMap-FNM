#ifndef FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H
#define FNM_UI_QGRAPHICS_SHADED_LINE_ITEM_H

#include<QGraphicsLineItem>
#include<QFont>


class FnmQGraphicsSimpleTextItem;

class FnmGraphicsItemShadedLine : public QGraphicsLineItem
{
public:
    FnmGraphicsItemShadedLine();
    QRectF boundingRect() const override;



protected:
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:

    QLineF line1, line2;

    FnmQGraphicsSimpleTextItem *distanceText;
    FnmQGraphicsSimpleTextItem *horizontalText;
    FnmQGraphicsSimpleTextItem *verticalText;
    FnmQGraphicsSimpleTextItem *degreesText;

    double theta() const;
    void updateShadedLines();
    void drawLines(QPainter *painter) const;

    QString textContainer;


};

#endif // MYGRAPHICSSHADEDLINEITEM_H
