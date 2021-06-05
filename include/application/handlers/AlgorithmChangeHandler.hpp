#ifndef APPLICATION_ALGORITHMCHANGEHANDLER_HPP
#define APPLICATION_ALGORITHMCHANGEHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>
#include <application/algorithms/AlgorithmsRegistrator.hpp>

namespace application
{
namespace handlers
{
    class AlgorithmChangeHandler : public IHandler
    {
      public:
        AlgorithmChangeHandler(gui::MainWindow& mainWindow,
                               simulation::Simulation& simulation,
                               algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
                               QTimer& timer);

      public slots:
        void doOnAlgorithmChange(const QString& text);

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

#endif   // APPLICATION_ALGORITHMCHANGEHANDLER_HPP
