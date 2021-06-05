#include <QDebug>
#include <simulation/robot/Robot.hpp>

namespace simulation
{
Robot::Robot() : coordinates_(), direction_(Direction::North), prefix_("Robot") {}

Robot::Robot(Coordinates coordinates, Direction direction)
{
    coordinates_ = coordinates;
    direction_ = direction;
}

Coordinates& Robot::getCoordinates()
{
    return coordinates_;
}

void Robot::setCoordinates(Coordinates coordinates)
{
    coordinates_ = coordinates;
}

Direction& Robot::getDirection()
{
    return direction_;
}

void Robot::setDirection(Direction direction)
{
    direction_ = direction;
}

void Robot::turnLeft()
{
    emit signalOnTurningLeft("Turning left");

    switch (direction_)
    {
        case Direction::North:
            direction_ = Direction::West;
            break;
        case Direction::East:
            direction_ = Direction::North;
            break;
        case Direction::South:
            direction_ = Direction::East;
            break;
        case Direction::West:
            direction_ = Direction::South;
            break;
    }
}
void Robot::turnRight()
{
    emit signalOnTurningRight("Turning right");

    switch (direction_)
    {
        case Direction::North:
            direction_ = Direction::East;
            break;
        case Direction::East:
            direction_ = Direction::South;
            break;
        case Direction::South:
            direction_ = Direction::West;
            break;
        case Direction::West:
            direction_ = Direction::North;
            break;
    }
}
void Robot::moveForward()
{
    emit signalOnMovingForward("Move forward");

    int x = coordinates_.getX();
    int y = coordinates_.getY();

    switch (direction_)
    {
        case Direction::North:
            y--;
            break;
        case Direction::East:
            x++;
            break;
        case Direction::South:
            y++;
            break;
        case Direction::West:
            x--;
            break;
    }

    coordinates_.setX(x);
    coordinates_.setY(y);
}

}   // namespace simulation
