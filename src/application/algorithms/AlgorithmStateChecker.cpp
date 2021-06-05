#include <application/algorithms/AlgorithmStateChecker.hpp>
#include <simulation/Coordinates.hpp>

namespace application
{
namespace algorithms
{
    namespace
    {
        std::vector<simulation::Coordinates> finishPoints {simulation::Coordinates(7, 7),
                                                           simulation::Coordinates(7, 8),
                                                           simulation::Coordinates(8, 7),
                                                           simulation::Coordinates(8, 8)};
    }

    AlgorithmStateChecker::AlgorithmStateChecker() {}

    bool AlgorithmStateChecker::isAlgorithmFinished(simulation::Micromouse& micromouse)
    {
        simulation::Coordinates& micromouseCoordinates = micromouse.getCoordinates();
        auto finishPointIt = std::find_if(
            finishPoints.begin(), finishPoints.end(), [&micromouseCoordinates](auto& coordinates) {
                return ((micromouseCoordinates.getX() == coordinates.getX())
                        && (micromouseCoordinates.getY() == coordinates.getY()));
            });

        return finishPointIt != finishPoints.end();
    }

}   // namespace algorithms
}   // namespace application
