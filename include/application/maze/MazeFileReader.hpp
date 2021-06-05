#ifndef APPLICATION_MAZE_MAZEFILEREADER_HPP
#define APPLICATION_MAZE_MAZEFILEREADER_HPP

#include <fstream>
#include <simulation/Coordinates.hpp>
#include <simulation/maze/Cell.hpp>
#include <simulation/maze/MazeWrapper.hpp>
#include <string>
#include <vector>

namespace application
{
namespace maze
{
    class MazeFileReader
    {
      public:
        MazeFileReader(std::string& fileName);
        MazeFileReader(const MazeFileReader&) = delete;
        MazeFileReader& operator=(const MazeFileReader&) = delete;
        ~MazeFileReader();

        simulation::MazeWrapper createMaze();

      private:
        std::vector<std::string> getCellParamsFromMazeFile();
        std::vector<int> convertStringToParamsVector(std::string& paramsStr);
        std::tuple<simulation::Coordinates, simulation::Cell>
        createCellFromParams(const std::vector<int> params);
        simulation::WallState convertToWallState(int state);

        std::ifstream mazeFile_;
        QString prefix_;
    };

}   // namespace maze
}   // namespace application

#endif   // APPLICATION_MAZE_MAZEFILEREADER_HPP
