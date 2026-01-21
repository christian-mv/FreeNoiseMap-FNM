#ifndef FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H
#define FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H

#include "abstract_point.h"
namespace fnm { class CorePointReceiver; }

namespace fnm {

class QgraphicsItemPointReceiver : public QgraphicsItemAbstractPointSource
{
public:
    QgraphicsItemPointReceiver();
    void setPointReceiver(fnm::CorePointReceiver *source);
    fnm::CorePointReceiver* getPointReceiver()const;
    virtual int	type() const override;

};

}
#endif