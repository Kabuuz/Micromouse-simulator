#ifndef APPLICATION_HANDLERS_PAUSEBUTTONACTIONHANDLER_HPP
#define APPLICATION_HANDLERS_PAUSEBUTTONACTIONHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class PauseButtonActionHandler : public IHandler
    {
      public:
        PauseButtonActionHandler(gui::MainWindow& mainWindow,
                                 simulation::Simulation& simulation,
                                 QTimer& timer);

      public slots:
        void doOnButtonPause();

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        QTimer& timer_;
        QString prefix_;
    };

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_HANDLERS_PAUSEBUTTONACTIONHANDLER_HPP
