#ifndef APPLICATION_MAZE_MAZEBUILDER_HPP
#define APPLICATION_MAZE_MAZEBUILDER_HPP

#include <simulation/maze/MazeWrapper.hpp>

namespace application
{
namespace maze
{
    class MazeBuilder
    {
      public:
        MazeBuilder() = delete;
        MazeBuilder(const MazeBuilder&) = delete;
        MazeBuilder& operator=(const MazeBuilder&) = delete;

        static simulation::MazeWrapper createMaze(std::string& mazeDirectory);
    };

}   // namespace maze
}   // namespace application

#endif   // APPLICATION_MAZE_MAZEBUILDER_HPP
