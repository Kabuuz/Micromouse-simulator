#include <QDebug>
#include <application/maze/MazeFileReader.hpp>
#include <simulation/Coordinates.hpp>
#include <simulation/maze/Cell.hpp>
#include <simulation/maze/MazeSettings.hpp>
#include <simulation/maze/WallState.hpp>

namespace application
{
namespace maze
{
    namespace
    {
        constexpr unsigned int PARAMS_SIZE = 6;
        constexpr unsigned int X_POSITION = 1;
        constexpr unsigned int Y_POSITION = 0;
        constexpr unsigned int NORTH_WALL_POSITION = 2;
        constexpr unsigned int EAST_WALL_POSITION = 3;
        constexpr unsigned int SOUTH_WALL_POSITION = 4;
        constexpr unsigned int WEST_WALL_POSITION = 5;

        constexpr char DATA_DELIMITER = ';';
    }   // namespace

    MazeFileReader::MazeFileReader(std::string& fileName) :
        mazeFile_(fileName), prefix_("MazeFileReader")
    {}

    MazeFileReader::~MazeFileReader()
    {
        if (mazeFile_.is_open())
        {
            mazeFile_.close();
        }
    }

    simulation::MazeWrapper MazeFileReader::createMaze()
    {
        if (mazeFile_.good())
        {
            qDebug() << prefix_ << __FUNCTION__ << " File exists";
            auto paramsStringVect = getCellParamsFromMazeFile();

            simulation::MazeWrapper maze;

            for (auto paramsString : paramsStringVect)
            {
                auto params = convertStringToParamsVector(paramsString);
                if (params.size() == PARAMS_SIZE)
                {
                    auto [coordinates, cell] = createCellFromParams(params);

                    if (coordinates.getX() > simulation::MAZE_COLUMNS || coordinates.getX() < 0
                        || coordinates.getY() > simulation::MAZE_ROWS || coordinates.getY() < 0)
                    {
                        qDebug() << prefix_ << "Invalid cell coordinates: " << coordinates.getX()
                                 << ", " << coordinates.getY();
                    }
                    else
                    {
                        maze.setCell(coordinates, cell);
                    }
                }
                else
                {
                    qDebug() << prefix_ << "Invalid number of params, expected: " << PARAMS_SIZE
                             << ", actual: " << params.size();
                }
            }

            return maze;
        }

        qCritical() << prefix_ << __FUNCTION__ << " File not found!";

        return simulation::MazeWrapper();
    }

    std::vector<std::string> MazeFileReader::getCellParamsFromMazeFile()
    {
        std::vector<std::string> paramsStringVect;
        std::string line;

        while (std::getline(mazeFile_, line))
        {
            paramsStringVect.push_back(line);
        }

        return paramsStringVect;
    }

    std::vector<int> MazeFileReader::convertStringToParamsVector(std::string& paramsStr)
    {
        // Y;X;N;E;S;W
        std::vector<int> params;

        while (!paramsStr.empty())
        {
            // delete unnecessary characters from string
            auto caretReturnIt = find_if(
                paramsStr.begin(), paramsStr.end(), [](char sign) { return sign == '\r'; });
            paramsStr.erase(caretReturnIt, paramsStr.end());
            // get params from string
            auto delimiterIt = find_if(paramsStr.begin(), paramsStr.end(), [](char sign) {
                return sign == DATA_DELIMITER;
            });

            std::string paramStr(paramsStr.begin(), delimiterIt);

            try
            {
                params.push_back(std::stoi(paramStr));
            }
            catch (const std::invalid_argument& e)
            {
                qDebug() << prefix_ << "Argument is not an integer";
                return {};
            }

            if (delimiterIt != paramsStr.end())
            {
                paramsStr.erase(paramsStr.begin(), delimiterIt + 1);
            }
            else
            {
                paramsStr.erase(paramsStr.begin(), delimiterIt);
            }
        }

        return params;
    }

    std::tuple<simulation::Coordinates, simulation::Cell>
    MazeFileReader::createCellFromParams(const std::vector<int> params)
    {
        simulation::Coordinates coordinates;
        coordinates.setX(params.at(X_POSITION));
        coordinates.setY(params.at(Y_POSITION));

        simulation::Cell cell;
        cell.setWallState(simulation::Direction::North,
                          convertToWallState(params.at(NORTH_WALL_POSITION)));
        cell.setWallState(simulation::Direction::East,
                          convertToWallState(params.at(EAST_WALL_POSITION)));
        cell.setWallState(simulation::Direction::South,
                          convertToWallState(params.at(SOUTH_WALL_POSITION)));
        cell.setWallState(simulation::Direction::West,
                          convertToWallState(params.at(WEST_WALL_POSITION)));

        return std::make_tuple(coordinates, cell);
    }

    simulation::WallState MazeFileReader::convertToWallState(int state)
    {
        switch (state)
        {
            case 1:
                return simulation::WallState::Present;
            case 2:
                return simulation::WallState::Unknown;
            default:
                return simulation::WallState::NotPresent;
        }
    }

}   // namespace maze
}   // namespace application
