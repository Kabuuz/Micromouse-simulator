#include <QDebug>
#include <application/handlers/PauseButtonActionHandler.hpp>

namespace application
{
namespace handlers
{
    PauseButtonActionHandler::PauseButtonActionHandler(gui::MainWindow& mainWindow,
                                                       simulation::Simulation& simulation,
                                                       QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("PauseButtonActionHandler")
    {}

    void PauseButtonActionHandler::doOnButtonPause()
    {
        handle({});
    }

    void PauseButtonActionHandler::handle(std::variant<int, std::string> change)
    {
        if (simulation_.getSimulationState() == simulation::SimulationState::Running)
        {
            simulation_.setSimulationState(simulation::SimulationState::Paused);
            timer_.stop();
        }
    }

}   // namespace handlers
}   // namespace application
