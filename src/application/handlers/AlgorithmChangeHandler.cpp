#include <QDebug>
#include <application/handlers/AlgorithmChangeHandler.hpp>

namespace application
{
namespace handlers
{
    AlgorithmChangeHandler::AlgorithmChangeHandler(
        gui::MainWindow& mainWindow,
        simulation::Simulation& simulation,
        algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
        QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        algorithmsRegistrator_(algorithmsRegistrator),
        timer_(timer),
        prefix_("AlgorithmChangeHandler")
    {}

    void AlgorithmChangeHandler::doOnAlgorithmChange(const QString& text)
    {
        handle({text.toStdString()});
    }

    void AlgorithmChangeHandler::handle(std::variant<int, std::string> change)
    {
        mainWindow_.getSettingsGroupBox()->getParametersLineEdit()->setText(QString::fromStdString(
            algorithmsRegistrator_.getAlgorithm(std::get<std::string>(change))
                ->getDefaultParamsString()));
    }

}   // namespace handlers
}   // namespace application
