#include <QDebug>
#include <simulation/SimulationSettings.hpp>
#include <simulation/maze/MazeSettings.hpp>
#include <simulation/robot/Micromouse.hpp>

namespace simulation
{
Micromouse::Micromouse() : Robot(), maze_(MazeWrapper(WallState::Unknown)), prefix_("Micromouse")
{
    resetMaze();
    resetPosition();
}

WallState& Micromouse::checkWallState(Direction direction)
{
    return maze_.getCell(getCoordinates().getY(), getCoordinates().getX())
        .getWall(direction)
        .getWallState();
}

void Micromouse::setWallState(Direction direction, WallState state)
{
    maze_.getCell(getCoordinates().getY(), getCoordinates().getX())
        .getWall(direction)
        .setWallState(state);
}

bool Micromouse::checkFrontWall()
{
    bool isWallDetected = false;
    Direction direction = getDirection();

    if (checkWallState(direction) == WallState::Present)
    {
        isWallDetected = true;
    }

    return isWallDetected;
}

bool Micromouse::checkLeftWall()
{
    bool isWallDetected = false;
    Direction direction = getDirection();

    switch (direction)
    {
        case Direction::North:
            if (checkWallState(Direction::West) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::East:
            if (checkWallState(Direction::North) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::South:
            if (checkWallState(Direction::East) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::West:
            if (checkWallState(Direction::South) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
    }
    return isWallDetected;
}

bool Micromouse::checkRightWall()
{
    bool isWallDetected = false;
    Direction direction = getDirection();

    switch (direction)
    {
        case Direction::North:
            if (checkWallState(Direction::East) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::East:
            if (checkWallState(Direction::South) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::South:
            if (checkWallState(Direction::West) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
        case Direction::West:
            if (checkWallState(Direction::North) == WallState::Present)
            {
                isWallDetected = true;
            }
            break;
    }
    return isWallDetected;
}

void Micromouse::updateCurrentCells(Cell& cell)
{
    int yCoordinate = getCoordinates().getY();
    int xCoordinate = getCoordinates().getX();

    if (visitedArray_.at(yCoordinate).at(xCoordinate) == false)
    {
        std::vector<Direction> directions {
            Direction::North, Direction::East, Direction::South, Direction::West};
        // update cells
        for (auto& direction : directions)
        {
            maze_.getCell(getCoordinates()).setWallState(direction, cell.getWall(direction).getWallState());
        }

        // set cell visited
        visitedArray_.at(yCoordinate).at(xCoordinate) = true;

        emitSignal(DISCOVERED_CELLS_ID, 1);
    }
}

void Micromouse::reset()
{
    resetMaze();
    resetPosition();
}

void Micromouse::resetMaze()
{
    maze_ = MazeWrapper(WallState::Unknown);

    // reset visited array and values array
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int column = 0; column < MAZE_COLUMNS; column++)
        {
            visitedArray_.at(row).at(column) = false;
            valuesArray_.at(row).at(column) = std::nullopt;
        }
    }
}

void Micromouse::resetPosition()
{
    Coordinates coordinates;
    coordinates.setY(START_ROW_DEFAULT);
    coordinates.setX(START_COLUMN_DEFAULT);
    setCoordinates(coordinates);
    setDirection(START_DIRECTION_DEFAULT);
}

MazeWrapper& Micromouse::getMaze()
{
    return maze_;
}

VisitedArray& Micromouse::getVisitedArray()
{
    return visitedArray_;
}

ValuesArray& Micromouse::getValuesArray()
{
    return valuesArray_;
}

void Micromouse::turnLeft()
{
    Robot::turnLeft();

    emitSignal(TURNS_ID, 1);
}

void Micromouse::turnRight()
{
    Robot::turnRight();

    emitSignal(TURNS_ID, 1);
}

void Micromouse::moveForward()
{
    Robot::moveForward();

    emitSignal(X_COORDINATE_ID, getCoordinates().getX());
    emitSignal(Y_COORDINATE_ID, getCoordinates().getY());
    emitSignal(DISTANCE_ID, 1);
}

void Micromouse::emitSignal(StatisticId id, int value)
{
    Statistic statistic;
    statistic.id = id;

    if (id == X_COORDINATE_ID || id == Y_COORDINATE_ID)
    {
        statistic.newStatisticValue = value;
    }
    else
    {
        statistic.changeStatisticByValue = value;
    }

    emit stateChanged(statistic);
}

}   // namespace simulation
