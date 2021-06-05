#include <application/algorithms/DeadEndExclusionAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    DeadEndExclusionAlgorithm::DeadEndExclusionAlgorithm(std::string name,
                                                         std::string parametersString) :
        DepthFirstSearchAlgorithm(name, parametersString)
    {}

    void DeadEndExclusionAlgorithm::reset()
    {
        DepthFirstSearchAlgorithm::reset();

        auto& valuesArray = micromouse_->getValuesArray();

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                valuesArray.at(row).at(column) = std::make_optional<float>(0);
            }
        }
    }

    void DeadEndExclusionAlgorithm::runStep()
    {
        calculateWalls();
        closeDeadEnds();
        move();
    }

    void DeadEndExclusionAlgorithm::calculateWalls()
    {
        auto& valuesArray = micromouse_->getValuesArray();

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                int wallsInCell = calculateWallsInCell(column, row);
                valuesArray.at(row).at(column) = std::make_optional<float>(wallsInCell);
            }
        }
    }

    int DeadEndExclusionAlgorithm::calculateWallsInCell(int positionX, int positionY)
    {
        auto& maze = micromouse_->getMaze();

        std::vector<simulation::Direction> directions {simulation::Direction::North,
                                                       simulation::Direction::East,
                                                       simulation::Direction::South,
                                                       simulation::Direction::West};

        int wallsDetected = 0;

        for (auto& direction : directions)
        {
            if (maze.getCell(positionY, positionX).getWall(direction).getWallState()
                == simulation::WallState::Present)
            {
                wallsDetected++;
            }
        }

        return wallsDetected;
    }

    void DeadEndExclusionAlgorithm::closeDeadEnds()
    {
        auto& valuesArray = micromouse_->getValuesArray();
        auto& coordinates = micromouse_->getCoordinates();
        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                if (row == coordinates.getY() && column == coordinates.getX())
                {
                    continue;
                }

                if (auto& value = valuesArray.at(row).at(column); value.has_value() && *value == 3)
                {
                    closeCell(column, row);
                    calculateWalls();
                    closeDeadEnds();
                }
            }
        }
    }

    void DeadEndExclusionAlgorithm::closeCell(int positionX, int positionY)
    {
        auto& maze = micromouse_->getMaze();

        std::vector<simulation::Direction> directions {simulation::Direction::North,
                                                       simulation::Direction::East,
                                                       simulation::Direction::South,
                                                       simulation::Direction::West};

        for (auto& direction : directions)
        {
            maze.getCell(positionY, positionX)
                .setWallState(direction, simulation::WallState::Present);
            setNeighbourWallPresent(positionY, positionX, direction);
        }
    }

    void DeadEndExclusionAlgorithm::setNeighbourWallPresent(int positionY,
                                                            int positionX,
                                                            simulation::Direction direction)
    {
        auto& maze = micromouse_->getMaze();

        auto [x, y] = getNeighbourCoordinates(positionX, positionY, direction);

        if (x < 0 || x >= simulation::MAZE_COLUMNS || y < 0 || y >= simulation::MAZE_ROWS)
        {
            return;
        }

        simulation::Direction directionInNeighbour;

        switch (direction)
        {
            case simulation::Direction::North:
                directionInNeighbour = simulation::Direction::South;
                break;
            case simulation::Direction::East:
                directionInNeighbour = simulation::Direction::West;
                break;
            case simulation::Direction::South:
                directionInNeighbour = simulation::Direction::North;
                break;
            case simulation::Direction::West:
                directionInNeighbour = simulation::Direction::East;
                break;
            default:
                directionInNeighbour = simulation::Direction::North;
        }

        maze.getCell(y, x).setWallState(directionInNeighbour, simulation::WallState::Present);
    }

    std::pair<int, int> DeadEndExclusionAlgorithm::getNeighbourCoordinates(
        int startPointX, int startPointY, simulation::Direction direction)
    {
        switch (direction)
        {
            case simulation::Direction::North:
                return {startPointX, startPointY - 1};
            case simulation::Direction::East:
                return {startPointX + 1, startPointY};
            case simulation::Direction::South:
                return {startPointX, startPointY + 1};
            case simulation::Direction::West:
                return {startPointX - 1, startPointY};
            default:
                return {255, 255};
        }
    }

    void DeadEndExclusionAlgorithm::move()
    {
        DepthFirstSearchAlgorithm::runStep();
    }

}   // namespace algorithms
}   // namespace application
