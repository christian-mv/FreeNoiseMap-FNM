#ifndef FNM_CORE_TYPES_NAMESPACE_H
#define FNM_CORE_TYPES_NAMESPACE_H

namespace fnm_core {

struct Rect {
    double x;
    double y;
    double width;
    double height;

    double left() const { return x; }
    double right() const { return x + width; }
    double top() const { return y; }
    double bottom() const { return y + height; }
};

namespace TypeId{
    enum {
        RasterPixmapItemType =  65536,
        PointSourceItemType = 65537,
        MultiLineSourceItemType = 65538,
        AcousticBarrierItemType= 65539,
        PolyLineItemType = 65540,
        PointReceiverItemType = 65541
         };
}
}


#endif // FNM_TYPES_H
