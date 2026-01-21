#ifndef FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H
#define FNM_QGRAPHICS_ITEM_POINT_RECEIVER_H

#include "abstract_point.h"
namespace fnm_core { class PointReceiver; }

namespace fnm_ui {

class PointReceiver : public AbstractPointSource
{
public:
    PointReceiver();
    void setPointReceiver(fnm_core::PointReceiver *source);
    fnm_core::PointReceiver* getPointReceiver()const;
    virtual int	type() const override;

};

}
#endif
