#include "receivers_grid.h"
#include <iostream>

using namespace std;

ReceiversGrid::ReceiversGrid(const GridSettings *settings)
{
    if(!settings)
        return;


    if(!setGrid(settings))
        cerr << "ReceiversGrid class wasn't "
                "properly loaded, check ReceiversGrid object";

}

bool ReceiversGrid::setGrid(const GridSettings *settings)
{


}
