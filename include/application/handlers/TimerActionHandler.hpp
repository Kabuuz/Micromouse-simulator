#ifndef APPLICATION_TIMERACTIONHANDLER_HPP
#define APPLICATION_TIMERACTIONHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class TimerActionHandler : public IHandler
    {
      public:
        TimerActionHandler(gui::MainWindow& mainWindow,
                           simulation::Simulation& simulation,
                           QTimer& timer);

      public slots:
        void doOnTimeout();

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

#endif   // APPLICATION_TIMERACTIONHANDLER_HPP
