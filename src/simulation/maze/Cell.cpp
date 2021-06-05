#include <QDebug>
#include <simulation/maze/Cell.hpp>

namespace simulation
{
Cell::Cell(WallState defaultWallState) :
    northWall_(defaultWallState),
    eastWall_(defaultWallState),
    southWall_(defaultWallState),
    westWall_(defaultWallState),
    prefix_("Cell")
{}

Wall& Cell::getWall(Direction direction)
{
    switch (direction)
    {
        case Direction::North:
            return northWall_;
            break;
        case Direction::East:
            return eastWall_;
            break;
        case Direction::South:
            return southWall_;
            break;
        case Direction::West:
            return westWall_;
            break;
        default:
            qCritical() << prefix_ << __FUNCTION__
                        << "Wrong direction: " << QString(static_cast<int>(direction));
            return northWall_;
            break;
    }
}

void Cell::setWallState(Direction direction, WallState state)
{
    switch (direction)
    {
        case Direction::North:
            northWall_.setWallState(state);
            break;
        case Direction::East:
            eastWall_.setWallState(state);
            break;
        case Direction::South:
            southWall_.setWallState(state);
            break;
        case Direction::West:
            westWall_.setWallState(state);
            break;
        default:
            qCritical() << prefix_ << __FUNCTION__
                        << "Wrong direction: " << QString(static_cast<int>(direction));
            break;
    }
}

}   // namespace simulation
