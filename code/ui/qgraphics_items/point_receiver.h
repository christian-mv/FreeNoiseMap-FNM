#ifndef FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H
#define FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H

#include "abstract_point.h"
namespace fnm_core { class CorePointReceiver; }

namespace fnm_ui {

class PointReceiver : public AbstractPointSource
{
public:
    PointReceiver();
    void setPointReceiver(fnm_core::CorePointReceiver *source);
    fnm_core::CorePointReceiver* getPointReceiver()const;
    virtual int	type() const override;

};

}
#endif
