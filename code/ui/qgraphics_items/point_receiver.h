#ifndef FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H
#define FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H

#include "abstract_point.h"
class FnmCorePointReceiver;


class FnmQgraphicsItemPointReceiver : public FnmQgraphicsItemAbstractPointSource
{
public:
    FnmQgraphicsItemPointReceiver();
    void setPointReceiver(FnmCorePointReceiver *source);
    FnmCorePointReceiver* getPointReceiver()const;
    virtual int	type() const override;

};

#endif
