#include <QDebug>
#include <application/handlers/ResetButtonActionHandler.hpp>
#include <application/updaters/StatisticLabelUpdater.hpp>

namespace application
{
namespace handlers
{
    ResetButtonActionHandler::ResetButtonActionHandler(gui::MainWindow& mainWindow,
                                                       simulation::Simulation& simulation,
                                                       QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("ResetButtonActionHandler")
    {}

    void ResetButtonActionHandler::doOnButtonReset()
    {
        handle({});
    }

    void ResetButtonActionHandler::handle(std::variant<int, std::string> change)
    {
        const auto& simulationState = simulation_.getSimulationState();

        if (simulationState == simulation::SimulationState::Running)
        {
            timer_.stop();
        }
        if (simulationState == simulation::SimulationState::Paused
            || simulationState == simulation::SimulationState::Running
            || simulationState == simulation::SimulationState::Finished)
        {
            mainWindow_.getSettingsGroupBox()->enableElementsDuringSimulation();
            simulation_.resetSimulation();
            mainWindow_.getInformationGroupBox()->getLogWidget()->clear();

            updaters::StatisticLabelUpdater::update(
                simulation_.getStatistics(),
                mainWindow_.getStatisticsGroupBox()->getStatisticValueLabels());

            mainWindow_.getInformationGroupBox()->getPaintingWidget()->animate();
            simulation_.setSimulationState(simulation::SimulationState::Reseted);
        }
    }

}   // namespace handlers
}   // namespace application
