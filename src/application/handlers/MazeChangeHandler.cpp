#include <QDebug>
#include <QString>
#include <application/handlers/MazeChangeHandler.hpp>
#include <application/maze/MazeBuilder.hpp>

namespace application
{
namespace handlers
{
    MazeChangeHandler::MazeChangeHandler(gui::MainWindow& mainWindow,
                                         simulation::Simulation& simulation,
                                         QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("MazeChangeHandler")
    {}

    void MazeChangeHandler::doOnMazeChange(const QString& text)
    {
        handle(text.toStdString());
    }

    void MazeChangeHandler::handle(std::variant<int, std::string> change)
    {
        std::string mazeDirectory = mainWindow_.getSettingsGroupBox()
                                        ->getMazeDirectoryLineEdit()
                                        ->text()
                                        .toUtf8()
                                        .constData()
            + std::get<std::string>(change);

        simulation_.setSimulationMaze(maze::MazeBuilder::createMaze(mazeDirectory));
        simulation_.update();
        mainWindow_.getInformationGroupBox()->getPaintingWidget()->animate();
    }

}   // namespace handlers
}   // namespace application
