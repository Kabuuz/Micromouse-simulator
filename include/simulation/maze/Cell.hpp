#ifndef SIMULATION_CELL_HPP_
#define SIMULATION_CELL_HPP_

#include <QString>
#include <simulation/Direction.hpp>
#include <simulation/maze/Wall.hpp>

namespace simulation
{
class Cell
{
  public:
    Cell(WallState defaultWallState = WallState::NotPresent);

    Wall& getWall(Direction direction);
    void setWallState(Direction direction, WallState state);

  private:
    Wall northWall_;
    Wall eastWall_;
    Wall southWall_;
    Wall westWall_;
    QString prefix_;
};

}   // namespace simulation

#endif   // SIMULATION_CELL_HPP_
