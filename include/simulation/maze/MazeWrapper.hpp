#ifndef SIMULATION_MAZE_HPP_
#define SIMULATION_MAZE_HPP_

#include <simulation/Coordinates.hpp>
#include <simulation/fwd.hpp>
#include <simulation/maze/Cell.hpp>
#include <vector>

namespace simulation
{
using Maze = std::vector<std::vector<Cell>>;

class MazeWrapper
{
  public:
    MazeWrapper(WallState defaultWallState = WallState::NotPresent);
    Cell& getCell(const int& row, const int& column);
    Cell& getCell(Coordinates& coordinates);
    void setCell(const int& row, const int& column, Cell cell);
    void setCell(Coordinates& coordinates, Cell cell);

  private:
    Maze maze_;
};

}   // namespace simulation

#endif   // SIMULATION_MAZE_HPP_
