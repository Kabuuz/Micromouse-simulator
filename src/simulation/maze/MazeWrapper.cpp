#include <memory>
#include <simulation/maze/MazeSettings.hpp>
#include <simulation/maze/MazeWrapper.hpp>

namespace simulation
{
MazeWrapper::MazeWrapper(WallState defaultWallState)
{
    maze_ = std::vector<std::vector<Cell>>(MAZE_ROWS, std::vector<Cell>(MAZE_COLUMNS, Cell()));

    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int column = 0; column < MAZE_COLUMNS; column++)
        {
            Cell cell(defaultWallState);   // maze border for default maze
            if (row == 0)
            {
                cell.getWall(Direction::North).setWallState(WallState::Present);
            }
            if (row == MAZE_ROWS - 1)
            {
                cell.getWall(Direction::South).setWallState(WallState::Present);
            }
            if (column == 0)
            {
                cell.getWall(Direction::West).setWallState(WallState::Present);
            }
            if (column == MAZE_COLUMNS - 1)
            {
                cell.getWall(Direction::East).setWallState(WallState::Present);
            }
            maze_.at(row).at(column) = cell;
        }
    }
}

Cell& MazeWrapper::getCell(const int& row, const int& column)
{
    return maze_.at(row).at(column);
}

Cell& MazeWrapper::getCell(Coordinates& coordinates)
{
    return maze_.at(coordinates.getY()).at(coordinates.getX());
}

void MazeWrapper::setCell(const int& row, const int& column, Cell cell)
{
    maze_.at(row).at(column) = cell;
}

void MazeWrapper::setCell(Coordinates& coordinates, Cell cell)
{
    maze_.at(coordinates.getY()).at(coordinates.getX()) = cell;
}

}   // namespace simulation
