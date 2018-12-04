#ifndef MY_QGRAPHICS_LINE_SOURCES_ITEM_H
#define MY_QGRAPHICS_LINE_SOURCES_ITEM_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <vector>


class SingleLineSource;



class MyQGraphicsLineSourcesItem : public QGraphicsPathItem
{
public:
    MyQGraphicsLineSourcesItem(QGraphicsItem *parent = nullptr, QPointF startPoint = QPointF(0,0));
    void addSource(SingleLineSource* source);
    int countSources() const;
    const std::vector<SingleLineSource*> getLineSources() const;
    QPainterPath path;

private:
    std::vector<SingleLineSource*> vectorLineSources;




};

#endif // MYGRAPHICSLINESOURCESITEM_H
