#ifndef SIMULATION_DIRECTION_HPP_
#define SIMULATION_DIRECTION_HPP_

#include <string>

namespace simulation
{
enum class Direction
{
    North,
    East,
    South,
    West
};

inline std::string to_string(Direction& direction)
{
    switch (direction)
    {
        case Direction::North:
            return "North";
        case Direction::East:
            return "East";
        case Direction::South:
            return "South";
        case Direction::West:
            return "West";
        default:
            return "Unknown Direction";
    }
}

}   // namespace simulation

#endif   // SIMULATION_DIRECTION_HPP_
