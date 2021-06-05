#ifndef APPLICATION_HANDLERS_STARTBUTTONACTIONHANDLER_HPP
#define APPLICATION_HANDLERS_STARTBUTTONACTIONHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>
#include <application/algorithms/AlgorithmsRegistrator.hpp>

namespace application
{
namespace handlers
{
    class StartButtonActionHandler : public IHandler
    {
      public:
        StartButtonActionHandler(gui::MainWindow& mainWindow,
                                 simulation::Simulation& simulation,
                                 algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
                                 QTimer& timer);

      public slots:
        void doOnButtonStart();

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        algorithms::AlgorithmsRegistrator& algorithmsRegistrator_;
        QTimer& timer_;
        QString prefix_;
    };   // namespace IHandler

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_HANDLERS_STARTBUTTONACTIONHANDLER_HPP
