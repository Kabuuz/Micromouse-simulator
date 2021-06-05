#include <simulation/maze/Wall.hpp>

namespace simulation
{
Wall::Wall() : state_(WallState::NotPresent) {}

Wall::Wall(WallState state) : state_ {state} {}

WallState& Wall::getWallState()
{
    return state_;
}

void Wall::setWallState(WallState state)
{
    state_ = state;
}

}   // namespace simulation
