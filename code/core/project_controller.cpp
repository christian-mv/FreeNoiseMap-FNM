#include "project_controller.h"
#include "noise_engine.h"

namespace fnm_core {

ProjectController::ProjectController() {
}

NoiseGrid& ProjectController::getNoiseGrid() {
    return noiseGrid;
}

const NoiseGrid& ProjectController::getNoiseGrid() const {
    return noiseGrid;
}

void ProjectController::setGridSettings(const GridSettings& settings) {
    noiseGrid.setSettings(settings);
}

const GridSettings& ProjectController::getSettings() const {
    return noiseGrid.getSettings();
}

bool ProjectController::runCalculation(const std::vector<PointSource*>& pointSources,
                                       const std::vector<LineSourceSegment*>& lineSources,
                                       const std::vector<BarrierSegment*>& barriers,
                                       std::function<bool(double percentage)> progressCallback) {
    
    auto& matrix = noiseGrid.getMatrix();
    size_t totalRows = matrix.size();

    for(size_t i = 0; i < totalRows; i++) {
        // Report progress and check for cancellation
        if (progressCallback) {
            double percent = (static_cast<double>(i) / totalRows) * 100.0;
            if (!progressCallback(percent)) {
                return false; // Cancelled
            }
        }

        // Iterate receivers in the current row
        for(auto& currentReceiver : matrix.at(i)) {
            
            // 1. Calculate noise from Point Sources
            for(const auto* source : pointSources) {
                NoiseEngine::P2P(*source, currentReceiver, barriers);
            }

            // 2. Calculate noise from Line Sources
            for(const auto* lineSegment : lineSources) {
                // Split line segment into point sources
                // fromLineToPointSources returns a vector of PointSource objects (by value)
                std::vector<PointSource> subSources = NoiseEngine::fromLineToPointSources(lineSegment, 22.0);
                
                for(auto& subSource : subSources) {
                    NoiseEngine::P2P(subSource, currentReceiver, barriers);
                }
            }
        }
    }
    
    // Final progress update
    if (progressCallback) {
        progressCallback(100.0);
    }

    return true;
}

} // namespace fnm_core
