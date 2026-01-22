#include "noise_grid.h"
#include "noise_engine.h"

namespace fnm_core {

NoiseGrid::NoiseGrid()
{
}

NoiseGrid::NoiseGrid(const GridSettings &settings)
{
    setSettings(settings);
}

void NoiseGrid::setSettings(const GridSettings &settings)
{
    this->settings = settings;
    unsigned int nRows = this->settings.countRows();
    unsigned int nColumns = this->settings.countColumns();

    initMatrix(nRows, nColumns);

    for(unsigned int i = 0; i < nRows; i++){
        for(unsigned int j = 0; j < nColumns; j++){
            matrix.at(j).at(i) = PointReceiver(this->settings.getLeft()
                                                    + i*this->settings.getDeltaX(),
                                                    this->settings.getTop()+j*this->settings.getDeltaY(),
                                                    0, -88.0,
                                                    false);
        }
    }
}

const GridSettings& NoiseGrid::getSettings() const
{
    return settings;
}

std::vector<std::vector<PointReceiver>>& NoiseGrid::getMatrix()
{
    return matrix;
}

const std::vector<std::vector<PointReceiver>>& NoiseGrid::getMatrix() const
{
    return matrix;
}

void NoiseGrid::initMatrix(unsigned int n, unsigned int m)
{
    matrix.resize(m);
    for(unsigned int i = 0 ; i < m ; ++i){
        matrix[i].resize(n);
    }
}

void NoiseGrid::resetReceivers()
{
    for(auto &row: matrix){
        for(auto &receiver: row){
            receiver.set_Leq(-88);
        }
    }
}

void NoiseGrid::interpolate()
{
    unsigned int factor = settings.getInterpolatorFactor();
    if(factor<=1){return;}

    double dx = settings.getDeltaX()/factor;
    double dy = settings.getDeltaY()/factor;
    double Leqx_temp;
    double Leqy_temp;

    // 1. Interpolate X axis for each row
    std::vector<std::vector<PointReceiver>> matrixXInterpolated;
    matrixXInterpolated.reserve(matrix.size());

    for(const auto &row : matrix) {
        std::vector<PointReceiver> newRow;
        newRow.reserve(row.size() * factor);

        for(size_t j = 0; j < row.size(); ++j) {
            const auto &r = row[j];
            newRow.push_back(r);

            if(j < row.size() - 1) {
                const auto &nextR = row[j+1];
                for(unsigned int k=1; k<factor; k++){
                    NoiseEngine::interpolationValueAt(r.get_x(),
                                                      r.get_Leq(),
                                                      r.get_x()+k*dx,
                                                      Leqx_temp,
                                                      nextR.get_x(),
                                                      nextR.get_Leq());

                    newRow.emplace_back(r.get_x()+k*dx, r.get_y(), r.get_z(), Leqx_temp, true);
                }
            }
        }
        matrixXInterpolated.push_back(std::move(newRow));
    }

    // 2. Interpolate Y axis (insert rows)
    std::vector<std::vector<PointReceiver>> finalMatrix;
    finalMatrix.reserve(matrixXInterpolated.size() * factor);

    for(size_t i = 0; i < matrixXInterpolated.size(); ++i) {
        finalMatrix.push_back(matrixXInterpolated[i]);

        if(i < matrixXInterpolated.size() - 1) {
            const auto &currentRow = matrixXInterpolated[i];
            const auto &nextRow = matrixXInterpolated[i+1];

            for(unsigned int k=1; k<factor; k++) {
                std::vector<PointReceiver> interpolatedRow;
                interpolatedRow.reserve(currentRow.size());

                for(size_t j=0; j<currentRow.size(); ++j) {
                    const auto &r = currentRow[j];
                    const auto &nextR = nextRow[j];

                    NoiseEngine::interpolationValueAt(r.get_y(),
                                                      r.get_Leq(),
                                                      r.get_y()+k*dy,
                                                      Leqy_temp,
                                                      nextR.get_y(),
                                                      nextR.get_Leq());

                    interpolatedRow.emplace_back(r.get_x(), r.get_y()+k*dy, r.get_z(), Leqy_temp, true);
                }
                finalMatrix.push_back(std::move(interpolatedRow));
            }
        }
    }

    matrix = std::move(finalMatrix);
}

void NoiseGrid::clearInterpolated()
{
    std::vector<std::vector<PointReceiver>> newMatrix;
    newMatrix.reserve(matrix.size());

    for(const auto& row : matrix) {
        if(row.empty()) continue;

        if(row.front().isInterpolated()) {
            continue;
        }

        std::vector<PointReceiver> newRow;
        newRow.reserve(row.size());
        for(const auto& r : row) {
            if(!r.isInterpolated()) {
                newRow.push_back(r);
            }
        }
        if(!newRow.empty()) {
            newMatrix.push_back(std::move(newRow));
        }
    }
    matrix = std::move(newMatrix);
}

}
