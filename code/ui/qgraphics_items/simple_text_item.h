#ifndef FNM_UI_QGRAPHICS_SIMPLE_TEXT_ITEM_H
#define FNM_UI_QGRAPHICS_SIMPLE_TEXT_ITEM_H

#include<QGraphicsSimpleTextItem>

namespace fnm_ui {

class SimpleTextItem : public ::QGraphicsSimpleTextItem
{
public:

    SimpleTextItem(QGraphicsItem *parent = nullptr);

protected:

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

}
#endif // MYQGRAPHICSSIMPLETEXTITEM_H
