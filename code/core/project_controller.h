#ifndef FNM_CORE_PROJECT_CONTROLLER_H
#define FNM_CORE_PROJECT_CONTROLLER_H

#include "noise_grid.h"
#include "point_source.h"
#include "line_source_segment.h"
#include "barrier_segment.h"
#include <vector>
#include <functional>

namespace fnm_core {

class ProjectController {
public:
    ProjectController();

    // Data Access
    NoiseGrid& getNoiseGrid();
    const NoiseGrid& getNoiseGrid() const;

    void setGridSettings(const GridSettings& settings);
    const GridSettings& getSettings() const;

    // Calculation
    // Returns true if completed, false if cancelled (via callback returning false)
    bool runCalculation(const std::vector<PointSource*>& pointSources,
                        const std::vector<LineSourceSegment*>& lineSources,
                        const std::vector<const BarrierSegment*>& barriers,
                        std::function<bool(double percentage)> progressCallback);

private:
    NoiseGrid noiseGrid;
};

} // namespace fnm_core

#endif // FNM_CORE_PROJECT_CONTROLLER_H
