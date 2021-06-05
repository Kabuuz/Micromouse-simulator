#include <QDebug>
#include <application/algorithms/FloodfillAlgorithm.hpp>
#include <map>
#include <random>
#include <simulation/maze/MazeSettings.hpp>

namespace application
{
namespace algorithms
{
    namespace
    {
        constexpr int TURN_LEFT {0};
        constexpr int TURN_RIGHT {1};
    }   // namespace

    FloodfillAlgorithm::FloodfillAlgorithm(std::string name, std::string parametersString) :
        Algorithm(name, parametersString)
    {}

    void FloodfillAlgorithm::runStep()
    {
        auto& actualCoordinates = micromouse_->getCoordinates();
        int positionX = actualCoordinates.getX();
        int positionY = actualCoordinates.getY();

        auto availableNeighbours = getAvailableNeighbours(positionX, positionY);

        int oldCValue = getCurrentCellValue(positionX, positionY);
        updateActualCValue(positionX, positionY, availableNeighbours);
        int newCValue = getCurrentCellValue(positionX, positionY);

        if (oldCValue != newCValue)
        {
            initializeMazeWithValues();
        }

        simulation::Direction direction
            = chooseMoveDirection(positionX, positionY, availableNeighbours);
        moveInDirection(direction);
    }

    void FloodfillAlgorithm::reset()
    {
        initializeMazeWithValues();
    }

    void FloodfillAlgorithm::initializeMazeWithDefaultValues()
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

    void FloodfillAlgorithm::initializeMazeWithValues()
    {
        initializeMazeWithDefaultValues();

        initializeFinishCells();

        std::vector<std::pair<int, int>> cellsFloodedInPreviousStep {
            {7, 7}, {7, 8}, {8, 7}, {8, 8}};
        std::vector<std::pair<int, int>> cellsFlooded {};
        std::vector<simulation::Direction> directions {simulation::Direction::North,
                                                       simulation::Direction::East,
                                                       simulation::Direction::South,
                                                       simulation::Direction::West};

        auto& valuesArray = micromouse_->getValuesArray();

        while (!mazeFlooded())
        {
            for (int row = 0; row < simulation::MAZE_ROWS; row++)
            {
                for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
                {
                    auto availableNeighbours = getAvailableNeighbours(column, row);
                    auto minimumValue
                        = getMinimumValueFromNeighbours(column, row, availableNeighbours);

                    if (minimumValue.has_value())
                    {
                        if (valuesArray.at(row).at(column) == std::nullopt
                            || valuesArray.at(row).at(column) > *minimumValue + 1)
                        {
                            valuesArray.at(row).at(column)
                                = generateCValue(column, row, availableNeighbours, *minimumValue);
                        }
                    }
                }
            }
        }
    }

    std::optional<float>
    FloodfillAlgorithm::generateCValue(int currentPointX,
                                       int currentPointY,
                                       std::vector<simulation::Direction> availableNeighbours,
                                       float minimumNeighbourValue)
    {
        return std::make_optional<float>(minimumNeighbourValue + 1.0f);
    }

    bool FloodfillAlgorithm::mazeFlooded()
    {
        auto& valuesArray = micromouse_->getValuesArray();

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                if (valuesArray.at(row).at(column) == std::nullopt)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void FloodfillAlgorithm::initializeFinishCells()
    {
        auto& valuesArray = micromouse_->getValuesArray();
        int finishInitialValue = 0;

        valuesArray.at(7).at(7) = std::make_optional<float>(0.0f);
        valuesArray.at(7).at(8) = std::make_optional<float>(0.0f);
        valuesArray.at(8).at(7) = std::make_optional<float>(0.0f);
        valuesArray.at(8).at(8) = std::make_optional<float>(0.0f);
    }

    float FloodfillAlgorithm::getCurrentCellValue(int currentPointX, int currentPointY)
    {
        auto& valuesArray = micromouse_->getValuesArray();

        if (auto& value = valuesArray.at(currentPointY).at(currentPointX); value.has_value())
        {
            return *value;
        }
        else
        {
            return 255.0f;
        }
    }

    void FloodfillAlgorithm::updateActualCValue(
        int startPointX, int startPointY, std::vector<simulation::Direction> availableNeighbours)
    {
        auto minimumNeighbourValue
            = getMinimumValueFromNeighbours(startPointX, startPointY, availableNeighbours);

        auto& valuesArray = micromouse_->getValuesArray();

        if (minimumNeighbourValue.has_value())
        {
            valuesArray.at(startPointY).at(startPointX)
                = std::make_optional<float>(*minimumNeighbourValue + 1.0f);
        }
    }

    std::vector<simulation::Direction> FloodfillAlgorithm::getAvailableNeighbours(int currentPointX,
                                                                                  int currentPointY)
    {
        std::vector<simulation::Direction> directions {simulation::Direction::North,
                                                       simulation::Direction::East,
                                                       simulation::Direction::South,
                                                       simulation::Direction::West};

        std::vector<simulation::Direction> availableNeighbours;

        for (auto& direction : directions)
        {
            if (neighbourAvailable(currentPointX, currentPointY, direction))
            {
                availableNeighbours.push_back(direction);
            }
        }

        return availableNeighbours;
    }

    bool FloodfillAlgorithm::neighbourAvailable(int startPointX,
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

    std::optional<float> FloodfillAlgorithm::getMinimumValueFromNeighbours(
        int startPointX, int startPointY, std::vector<simulation::Direction> availableNeighbours)
    {
        std::vector<float> values;
        auto& valuesArray = micromouse_->getValuesArray();

        for (auto& direction : availableNeighbours)
        {
            const auto& [neighbourX, neighbourY]
                = getNeighbourCoordinates(startPointX, startPointY, direction);
            auto& optionalValue = valuesArray.at(neighbourY).at(neighbourX);

            if (optionalValue.has_value())
            {
                values.push_back(*optionalValue);
            }
        }

        if (values.empty())
        {
            return std::nullopt;
        }

        return std::make_optional<float>(*(std::min_element(values.begin(), values.end())));
    }

    std::pair<int, int> FloodfillAlgorithm::getNeighbourCoordinates(int startPointX,
                                                                    int startPointY,
                                                                    simulation::Direction direction)
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

    simulation::Direction FloodfillAlgorithm::chooseMoveDirection(
        int startPointX, int startPointY, std::vector<simulation::Direction> availableNeighbours)
    {
        std::map<simulation::Direction, float> values;
        auto& valuesArray = micromouse_->getValuesArray();

        for (auto& direction : availableNeighbours)
        {
            const auto& [neighbourX, neighbourY]
                = getNeighbourCoordinates(startPointX, startPointY, direction);
            auto& optionalValue = valuesArray.at(neighbourY).at(neighbourX);

            if (optionalValue.has_value())
            {
                values[direction] = *optionalValue;
            }
        }

        auto minimumValue
            = getMinimumValueFromNeighbours(startPointX, startPointY, availableNeighbours);
        std::vector<simulation::Direction> neighboursWithMinimalValue;
        for (auto& direction : availableNeighbours)
        {
            auto [x, y] = getNeighbourCoordinates(startPointX, startPointY, direction);

            auto& value = valuesArray.at(y).at(x);

            if (auto& value = valuesArray.at(y).at(x); value.has_value())
            {
                if (minimumValue.has_value() && *value == *minimumValue)
                {
                    neighboursWithMinimalValue.push_back(direction);
                }
            }
        }

        auto frontNeighbourIt
            = std::find_if(neighboursWithMinimalValue.begin(),
                           neighboursWithMinimalValue.end(),
                           [&startPointX, &startPointY, this](auto& direction) {
                               auto [x, y]
                                   = getNeighbourCoordinates(startPointX, startPointY, direction);
                               return isFrontNeighbourCell(startPointX, startPointY, x, y);
                           });

        if (frontNeighbourIt != neighboursWithMinimalValue.end())
        {
            return *frontNeighbourIt;
        }

        auto rightNeighbourIt
            = std::find_if(neighboursWithMinimalValue.begin(),
                           neighboursWithMinimalValue.end(),
                           [&startPointX, &startPointY, this](auto& direction) {
                               auto [x, y]
                                   = getNeighbourCoordinates(startPointX, startPointY, direction);
                               return isRightNeighbourCell(startPointX, startPointY, x, y);
                           });

        auto leftNeighbourIt
            = std::find_if(neighboursWithMinimalValue.begin(),
                           neighboursWithMinimalValue.end(),
                           [&startPointX, &startPointY, this](auto& direction) {
                               auto [x, y]
                                   = getNeighbourCoordinates(startPointX, startPointY, direction);
                               return isLeftNeighbourCell(startPointX, startPointY, x, y);
                           });

        if (rightNeighbourIt != neighboursWithMinimalValue.end()
            && leftNeighbourIt != neighboursWithMinimalValue.end())
        {
            std::random_device rd;
            std::mt19937 generator {rd()};
            std::uniform_int_distribution<int> range(0, 1);
            int turnDirection = range(generator);
            if (turnDirection == TURN_LEFT)
            {
                return *leftNeighbourIt;
            }
            else if (turnDirection == TURN_RIGHT)
            {
                return *rightNeighbourIt;
            }
        }
        else if (rightNeighbourIt != neighboursWithMinimalValue.end())
        {
            return *rightNeighbourIt;
        }
        else if (leftNeighbourIt != neighboursWithMinimalValue.end())
        {
            return *leftNeighbourIt;
        }

        auto backNeighbourIt
            = std::find_if(neighboursWithMinimalValue.begin(),
                           neighboursWithMinimalValue.end(),
                           [&startPointX, &startPointY, this](auto& direction) {
                               auto [x, y]
                                   = getNeighbourCoordinates(startPointX, startPointY, direction);
                               return isBackNeighbourCell(startPointX, startPointY, x, y);
                           });

        if (backNeighbourIt != neighboursWithMinimalValue.end())
        {
            return *backNeighbourIt;
        }

        qDebug() << "No available direction";
        return simulation::Direction::North;
    }

    void FloodfillAlgorithm::moveInDirection(simulation::Direction direction)
    {
        simulation::Coordinates& currentCoordinates = micromouse_->getCoordinates();
        int micromousePositionX = currentCoordinates.getX();
        int micromousePositionY = currentCoordinates.getY();
        auto [nextPositionX, nextPositionY]
            = getNeighbourCoordinates(micromousePositionX, micromousePositionY, direction);

        if (isRightNeighbourCell(
                micromousePositionX, micromousePositionY, nextPositionX, nextPositionY))
        {
            micromouse_->turnRight();
            micromouse_->moveForward();
        }
        else if (isLeftNeighbourCell(
                     micromousePositionX, micromousePositionY, nextPositionX, nextPositionY))
        {
            micromouse_->turnLeft();
            micromouse_->moveForward();
        }
        else if (isFrontNeighbourCell(
                     micromousePositionX, micromousePositionY, nextPositionX, nextPositionY))
        {
            micromouse_->moveForward();
        }
        else if (isBackNeighbourCell(
                     micromousePositionX, micromousePositionY, nextPositionX, nextPositionY))
        {
            std::random_device rd;
            std::mt19937 generator {rd()};
            std::uniform_int_distribution<int> range(0, 1);
            int turnDirection = range(generator);
            if (turnDirection == TURN_LEFT)
            {
                micromouse_->turnLeft();
                micromouse_->turnLeft();
                micromouse_->moveForward();
            }
            else if (turnDirection == TURN_RIGHT)
            {
                micromouse_->turnRight();
                micromouse_->turnRight();
                micromouse_->moveForward();
            }
        }
    }

    bool FloodfillAlgorithm::isRightNeighbourCell(int startPointX,
                                                  int startPointY,
                                                  int nextPointX,
                                                  int nextPointY)
    {
        switch (micromouse_->getDirection())
        {
            case simulation::Direction::North:
                startPointX++;
                break;
            case simulation::Direction::East:
                startPointY++;
                break;
            case simulation::Direction::South:
                startPointX--;
                break;
            case simulation::Direction::West:
                startPointY--;
                break;
        }

        return (nextPointX == startPointX && nextPointY == startPointY);
    }

    bool FloodfillAlgorithm::isLeftNeighbourCell(int startPointX,
                                                 int startPointY,
                                                 int nextPointX,
                                                 int nextPointY)
    {
        switch (micromouse_->getDirection())
        {
            case simulation::Direction::North:
                startPointX--;
                break;
            case simulation::Direction::East:
                startPointY--;
                break;
            case simulation::Direction::South:
                startPointX++;
                break;
            case simulation::Direction::West:
                startPointY++;
                break;
        }

        return (nextPointX == startPointX && nextPointY == startPointY);
    }

    bool FloodfillAlgorithm::isFrontNeighbourCell(int startPointX,
                                                  int startPointY,
                                                  int nextPointX,
                                                  int nextPointY)
    {
        switch (micromouse_->getDirection())
        {
            case simulation::Direction::North:
                startPointY--;
                break;
            case simulation::Direction::East:
                startPointX++;
                break;
            case simulation::Direction::South:
                startPointY++;
                break;
            case simulation::Direction::West:
                startPointX--;
                break;
        }

        return (nextPointX == startPointX && nextPointY == startPointY);
    }

    bool FloodfillAlgorithm::isBackNeighbourCell(int startPointX,
                                                 int startPointY,
                                                 int nextPointX,
                                                 int nextPointY)
    {
        switch (micromouse_->getDirection())
        {
            case simulation::Direction::North:
                startPointY++;
                break;
            case simulation::Direction::East:
                startPointX--;
                break;
            case simulation::Direction::South:
                startPointY--;
                break;
            case simulation::Direction::West:
                startPointX++;
                break;
        }

        return (nextPointX == startPointX && nextPointY == startPointY);
    }

}   // namespace algorithms
}   // namespace application
