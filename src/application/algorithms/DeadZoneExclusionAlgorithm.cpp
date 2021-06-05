#include <application/algorithms/DeadZoneExclusionAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    namespace
    {
        std::vector<std::pair<int, int>> finishPoints {{7, 7}, {7, 8}, {8, 7}, {8, 8}};

        constexpr float FLOOD_VALUE = 0.0f;
    }   // namespace

    DeadZoneExclusionAlgorithm::DeadZoneExclusionAlgorithm(std::string name,
                                                           std::string parametersString) :
        DepthFirstSearchAlgorithm(name, parametersString)
    {}

    void DeadZoneExclusionAlgorithm::reset()
    {
        DepthFirstSearchAlgorithm::reset();

        resetValues();
    }

    void DeadZoneExclusionAlgorithm::resetValues()
    {
        auto& valuesArray = micromouse_->getValuesArray();

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                valuesArray.at(row).at(column) = std::nullopt;
            }
        }
    }

    void DeadZoneExclusionAlgorithm::runStep()
    {
        if (inCrossroad())
        {
            auto& coordinates = micromouse_->getCoordinates();
            int micromouseX = coordinates.getX();
            int micromouseY = coordinates.getY();

            auto availableDirections = getAvailableNeighbours(micromouseX, micromouseY);

            for (auto& direction : availableDirections)
            {
                auto [x, y] = getNeighbourPosition(micromouseX, micromouseY, direction);

                std::vector<std::pair<int, int>> floodedCells;

                resetValues();

                startflooding(x, y, floodedCells);

                if (!isFinishPointsInVector(floodedCells))
                {
                    putWallInDirection(micromouseX, micromouseY, direction);
                }
            }
        }

        resetValues();
        move();
    }

    void DeadZoneExclusionAlgorithm::move()
    {
        DepthFirstSearchAlgorithm::runStep();
    }

    bool DeadZoneExclusionAlgorithm::inCrossroad()
    {
        int availableNeighbourCells = 0;
        if (!micromouse_->checkFrontWall())
        {
            availableNeighbourCells++;
        }
        if (!micromouse_->checkLeftWall())
        {
            availableNeighbourCells++;
        }

        if (!micromouse_->checkRightWall())
        {
            availableNeighbourCells++;
        }

        return availableNeighbourCells >= 2;
    }

    std::vector<simulation::Direction>
    DeadZoneExclusionAlgorithm::getAvailableNeighbours(int positionX, int positionY)
    {
        std::vector<simulation::Direction> directions {simulation::Direction::North,
                                                       simulation::Direction::East,
                                                       simulation::Direction::South,
                                                       simulation::Direction::West};

        std::vector<simulation::Direction> availableNeighbours;

        for (auto& direction : directions)
        {
            if (neighbourAvailable(positionX, positionY, direction))
            {
                availableNeighbours.push_back(direction);
            }
        }

        return availableNeighbours;
    }

    bool DeadZoneExclusionAlgorithm::neighbourAvailable(int startPointX,
                                                        int startPointY,
                                                        simulation::Direction direction)
    {
        if (micromouse_->getMaze()
                .getCell(startPointY, startPointX)
                .getWall(direction)
                .getWallState()
            != simulation::WallState::Present)
        {
            return true;
        }

        return false;
    }

    std::pair<int, int> DeadZoneExclusionAlgorithm::getNeighbourPosition(
        int positionX, int positionY, simulation::Direction direction)
    {
        switch (direction)
        {
            case simulation::Direction::North:
                return {positionX, positionY - 1};
            case simulation::Direction::East:
                return {positionX + 1, positionY};
            case simulation::Direction::South:
                return {positionX, positionY + 1};
            case simulation::Direction::West:
                return {positionX - 1, positionY};
            default:
                return {255, 255};
        }
    }

    void DeadZoneExclusionAlgorithm::startflooding(int x,
                                                   int y,
                                                   std::vector<std::pair<int, int>>& floodedCells)
    {
        auto& coordinates = micromouse_->getCoordinates();
        int micromouseX = coordinates.getX();
        int micromouseY = coordinates.getY();

        if (micromouseX == x && micromouseY == y)
        {
            return;
        }

        auto& valuesArray = micromouse_->getValuesArray();

        auto& value = valuesArray.at(y).at(x);

        if (value.has_value() && *value == FLOOD_VALUE)
        {
            return;
        }

        value = std::make_optional<float>(FLOOD_VALUE);
        floodedCells.push_back({x, y});

        auto availableDirections = getAvailableNeighbours(x, y);

        for (auto& direction : availableDirections)
        {
            auto [neighbourX, neighbourY] = getNeighbourPosition(x, y, direction);
            startflooding(neighbourX, neighbourY, floodedCells);
        }
    }

    bool DeadZoneExclusionAlgorithm::isFinishPointsInVector(
        std::vector<std::pair<int, int>>& floodedCells)
    {
        for (auto& point : floodedCells)
        {
            for (auto& finishPoint : finishPoints)
            {
                if (point.first == finishPoint.first && point.second == finishPoint.second)
                {
                    return true;
                }
            }
        }

        return false;
    }

    void DeadZoneExclusionAlgorithm::putWallInDirection(int positionX,
                                                        int positionY,
                                                        simulation::Direction direction)
    {
        micromouse_->getMaze()
            .getCell(positionY, positionX)
            .setWallState(direction, simulation::WallState::Present);
        setNeighbourWallPresent(positionY, positionX, direction);
    }

    void DeadZoneExclusionAlgorithm::setNeighbourWallPresent(int positionY,
                                                             int positionX,
                                                             simulation::Direction direction)
    {
        auto& maze = micromouse_->getMaze();

        auto [x, y] = getNeighbourPosition(positionX, positionY, direction);

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

}   // namespace algorithms
}   // namespace application
