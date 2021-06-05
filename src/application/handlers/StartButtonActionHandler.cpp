#include <QDebug>
#include <application/algorithms/AlgorithmParametersConverter.hpp>
#include <application/handlers/StartButtonActionHandler.hpp>
#include <json/json.h>

namespace application
{
namespace handlers
{
    StartButtonActionHandler::StartButtonActionHandler(
        gui::MainWindow& mainWindow,
        simulation::Simulation& simulation,
        algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
        QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        algorithmsRegistrator_(algorithmsRegistrator),
        timer_(timer),
        prefix_("StartButtonActionHandler")
    {}

    void StartButtonActionHandler::doOnButtonStart()
    {
        handle({});
    }

    void StartButtonActionHandler::handle(std::variant<int, std::string> change)
    {
        if (simulation_.getSimulationState() == simulation::SimulationState::Reseted)
        {
            std::string maze = mainWindow_.getSettingsGroupBox()
                                   ->getMazeComboBox()
                                   ->currentText()
                                   .toLocal8Bit()
                                   .constData();
            mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(   // log maze
                QString::fromStdString("Maze: " + maze));

            std::string algorithmName = mainWindow_.getSettingsGroupBox()
                                            ->getAlgorithmComboBox()
                                            ->currentText()
                                            .toStdString();

            mainWindow_
                .getInformationGroupBox()   // log algorithm
                ->getLogWidget()
                ->insertPlainText(QString::fromStdString("\nAlgorithm: " + algorithmName));

            // convert params
            std::string paramsToConvert
                = mainWindow_.getSettingsGroupBox()->getParametersLineEdit()->text().toStdString();
            std::string defaultParams
                = algorithmsRegistrator_.getAlgorithm(algorithmName)->getDefaultParamsString();
            bool dataIsCorrect;
            Json::Value paramsJson = algorithms::AlgorithmParametersConverter::convertParams(
                paramsToConvert, defaultParams, dataIsCorrect);

            algorithmsRegistrator_.getAlgorithm(algorithmName)->setParameters(paramsJson);
            algorithmsRegistrator_.getAlgorithm(algorithmName)->reset();
            simulation_.setAlgorithm(algorithmsRegistrator_.getAlgorithm(algorithmName));

            std::string paramsToLog = (dataIsCorrect) ? paramsToConvert : defaultParams;
            mainWindow_
                .getInformationGroupBox()   // log parameters
                ->getLogWidget()
                ->insertPlainText(QString::fromStdString("\nParameters: " + paramsToLog));

            mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(
                QString::fromStdString(
                    "\nPosition:"
                    + std::to_string(simulation_.getMicromouse()->getCoordinates().getX()) + ","
                    + std::to_string(simulation_.getMicromouse()->getCoordinates().getY())));
            mainWindow_.getInformationGroupBox()->getLogWidget()->insertPlainText(
                QString::fromStdString(
                    "\nDirection:"
                    + simulation::to_string(simulation_.getMicromouse()->getDirection())));

            mainWindow_.getSettingsGroupBox()->disableElementsDuringSimulation();
            simulation_.setSimulationState(simulation::SimulationState::Running);
            timer_.start(mainWindow_.getControlGroupBox()->getSliderValueLabel()->text().toInt());
        }
        if (simulation_.getSimulationState() == simulation::SimulationState::Paused)
        {
            simulation_.setSimulationState(simulation::SimulationState::Running);
            timer_.start(mainWindow_.getControlGroupBox()->getSliderValueLabel()->text().toInt());
        }
    }

}   // namespace handlers
}   // namespace application
