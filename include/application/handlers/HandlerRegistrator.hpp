#ifndef APPLICATION_HANDLERS_HANDLERREGISTRATOR_HPP
#define APPLICATION_HANDLERS_HANDLERREGISTRATOR_HPP

#include <QObject>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>
#include <application/algorithms/AlgorithmsRegistrator.hpp>

namespace application
{
namespace handlers
{
    class HandlerRegistrator : public QObject
    {
        Q_OBJECT

      public:
        HandlerRegistrator(gui::MainWindow& mainWindow,
                           simulation::Simulation& simulation,
                           algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
                           QTimer& timer);
        void registerHandlers();

      private:
        void registerTextEditHandler();
        void registerScanButtonActionHandler();
        void registerPauseButtonActionHandler();
        void registerStartButtonActionHandler();
        void registerResetButtonActionHandler();
        void registerSaveButtonActionHandler();
        void registerMazeChangeHandler();
        void registerAlgorithmChangeHandler();
        void registerSlideChangeHandler();
        void registerTimerActionHandler();

        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        algorithms::AlgorithmsRegistrator& algorithmsRegistrator_;
        QTimer& timer_;
        std::vector<std::unique_ptr<IHandler>> handlers_;
    };

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_HANDLERS_GUI_HANDLERREGISTRATOR_HPP
