#include <QDebug>
#include <QString>
#include <application/maze/MazeBuilder.hpp>
#include <application/maze/MazeFileReader.hpp>

namespace application
{
namespace maze
{
    simulation::MazeWrapper MazeBuilder::createMaze(std::string& mazeDirectory)
    {
            qDebug() << "Creating maze from file: " + QString::fromStdString(mazeDirectory);
            MazeFileReader fileReader(mazeDirectory);
            return fileReader.createMaze();
    }

}   // namespace maze
}   // namespace application
