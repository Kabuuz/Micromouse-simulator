#ifndef SIMULATION_WALL_HPP_
#define SIMULATION_WALL_HPP_

#include <QString>
#include <simulation/maze/WallState.hpp>

namespace simulation
{
class Wall
{
  public:
    Wall();
    Wall(WallState state);
    WallState& getWallState();
    void setWallState(WallState state);

  private:
    WallState state_;
};

}   // namespace simulation

#endif   // SIMULATION_WALL_HPP_
