#ifndef RECEIVERS_GRID_H
#define RECEIVERS_GRID_H

#include "grid_settings.h"
#include "receiver.h"
#include <vector>


using namespace std;

class ReceiversGrid
{
public:
    explicit ReceiversGrid(const GridSettings *settings = nullptr);
    bool setGrid(const GridSettings *settings);

private:



};

#endif // RECEIVERSGRID_H
