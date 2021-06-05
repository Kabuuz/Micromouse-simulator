#ifndef APPLICATION_SLIDERCHANGEHANDLER_HPP
#define APPLICATION_SLIDERCHANGEHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class SliderChangeHandler : public IHandler
    {
      public:
        SliderChangeHandler(gui::MainWindow& mainWindow,
                            simulation::Simulation& simulation,
                            QTimer& timer);

      public slots:
        void doOnSliderChange(int value);

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        QTimer& timer_;
        QString prefix_;
    };   // namespace IHandler

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_SLIDERCHANGEHANDLER_HPP
