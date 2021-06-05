#include <QDebug>
#include <application/algorithms/AlgorithmStateChecker.hpp>
#include <application/handlers/TimerActionHandler.hpp>
#include <application/updaters/StatisticLabelUpdater.hpp>

namespace application
{
namespace handlers
{
    TimerActionHandler::TimerActionHandler(gui::MainWindow& mainWindow,
                                           simulation::Simulation& simulation,
                                           QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("TimerActionHandler")
    {}

    void TimerActionHandler::doOnTimeout()
    {
        handle({});
    }

    void TimerActionHandler::handle(std::variant<int, std::string> change)
    {
        simulation_.update();
        simulation_.runStep();
        simulation_.update();

        mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(
            QString::fromStdString(
                "\nPosition:" + std::to_string(simulation_.getMicromouse()->getCoordinates().getX())
                + "," + std::to_string(simulation_.getMicromouse()->getCoordinates().getY())));
        mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(
            QString::fromStdString("\nDirection:"
                                   + to_string(simulation_.getMicromouse()->getDirection())));

        updaters::StatisticLabelUpdater::update(
            simulation_.getStatistics(),
            mainWindow_.getStatisticsGroupBox()->getStatisticValueLabels());

        mainWindow_.getInformationGroupBox()->getPaintingWidget()->animate();

        algorithms::AlgorithmStateChecker algorithmStateChecker;

        if (algorithmStateChecker.isAlgorithmFinished(*simulation_.getMicromouse()))
        {
            timer_.stop();
            simulation_.setSimulationState(simulation::SimulationState::Finished);
            mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(
                QString::fromStdString("\nSimulation finished"));
        }
    }

}   // namespace handlers
}   // namespace application
