#ifndef FNM_CORE_NOISE_GRID_H
#define FNM_CORE_NOISE_GRID_H

#include <vector>
#include "point_receiver.h"
#include "grid_settings.h"

namespace fnm_core {

class NoiseGrid
{
public:
    NoiseGrid();
    explicit NoiseGrid(const GridSettings &settings);

    void setSettings(const GridSettings &settings);
    const GridSettings& getSettings() const;

    // Data Access
    std::vector<std::vector<PointReceiver>>& getMatrix();
    const std::vector<std::vector<PointReceiver>>& getMatrix() const;

    void resetReceivers();
    void interpolate();
    void clearInterpolated();

private:
    GridSettings settings;
    std::vector<std::vector<PointReceiver>> matrix;

    void initMatrix(unsigned int rows, unsigned int cols);
};

}
#endif // FNM_CORE_NOISE_GRID_H
