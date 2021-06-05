#ifndef SIMULATION_FWD_HPP_
#define SIMULATION_FWD_HPP_

#include <memory>
#include <optional>
#include <simulation/maze/MazeSettings.hpp>
#include <vector>

namespace simulation
{
class IAlgorithm;
using IAlgorithmPtr = std::shared_ptr<IAlgorithm>;

using VisitedArray = std::array<std::array<bool, MAZE_COLUMNS>, MAZE_ROWS>;
using ValuesArray = std::array<std::array<std::optional<float>, MAZE_COLUMNS>, MAZE_ROWS>;
}   // namespace simulation

#endif   // SIMULATION_FWD_HPP_
