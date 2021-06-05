#include <application/handlers/SliderChangeHandler.hpp>

#include <QDebug>

namespace application
{
namespace handlers
{

    SliderChangeHandler::SliderChangeHandler(gui::MainWindow& mainWindow,
                                                       simulation::Simulation& simulation,
                                                       QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("SliderChangeHandler")
    {}

    void SliderChangeHandler::doOnSliderChange(int value)
    {
        handle(value);
    }

    void SliderChangeHandler::handle(std::variant<int, std::string> change)
    {
        mainWindow_.getControlGroupBox()->getSliderValueLabel()->setText(
            QString::fromStdString(std::to_string(std::get<int>(change))));
        timer_.setInterval(std::get<int>(change));
    }

}   // namespace handlers
}   // namespace application

