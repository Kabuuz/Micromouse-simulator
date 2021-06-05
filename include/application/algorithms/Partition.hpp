#ifndef APPLICATION_ALGORITHM_PARTITION_HPP
#define APPLICATION_ALGORITHM_PARTITION_HPP

#include <simulation/Coordinates.hpp>
#include <simulation/Direction.hpp>

namespace application
{
namespace algorithms
{
    enum AlgorithmEnum
    {
        RightWallFollower,
        CenterRight,
        CenterLeft,
        LeftWallFollower
    };

    struct Partition
    {
        simulation::Coordinates leftUpPosition;
        simulation::Coordinates rightDownPosition;
        std::map<simulation::Direction, AlgorithmEnum> algorithmMap;
    };

}   // namespace algorithms
}   // namespace application
#endif   // APPLICATION_ALGORITHM_PARTITION_HPP