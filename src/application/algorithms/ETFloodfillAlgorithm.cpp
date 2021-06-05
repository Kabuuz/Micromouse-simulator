#include <QDebug>
#include <application/algorithms/ETFloodfillAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    ETFloodfillAlgorithm::ETFloodfillAlgorithm(std::string name, std::string parametersString) :
        FloodfillAlgorithm(name, parametersString)
    {}

    std::optional<float>
    ETFloodfillAlgorithm::generateCValue(int currentPointX,
                                         int currentPointY,
                                         std::vector<simulation::Direction> availableNeighbours,
                                         float minimumNeighbourValue)
    {
        std::optional<float> cValue;

        auto minimumValueAndNotPresentWall = std::find_if(
            availableNeighbours.begin(),
            availableNeighbours.end(),
            [this, &currentPointX, &currentPointY, &minimumNeighbourValue](auto& direction) {
                auto [x, y] = getNeighbourCoordinates(currentPointX, currentPointY, direction);
                auto& value = micromouse_->getValuesArray().at(y).at(x);
                auto wallState = micromouse_->getMaze()
                                     .getCell(currentPointY, currentPointX)
                                     .getWall(direction)
                                     .getWallState();
                return (value.has_value() && *value == minimumNeighbourValue
                        && wallState == simulation::WallState::NotPresent);
            });

        if (minimumValueAndNotPresentWall != availableNeighbours.end())
        {
            cValue = std::make_optional<float>(minimumNeighbourValue + 1.0f);
        }
        else
        {
            float T = parameters_["T"].asFloat();
            cValue = std::make_optional<float>(minimumNeighbourValue + 1.0f + T);
        }

        return cValue;
    }

}   // namespace algorithms
}   // namespace application
