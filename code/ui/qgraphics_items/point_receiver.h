#ifndef FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H
#define FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H

#include "abstract_point.h"
namespace fnm { class CorePointReceiver; }

namespace fnm_ui {

class PointReceiver : public AbstractPointSource
{
public:
    PointReceiver();
    void setPointReceiver(fnm::CorePointReceiver *source);
    fnm::CorePointReceiver* getPointReceiver()const;
    virtual int	type() const override;

};

}
#endif