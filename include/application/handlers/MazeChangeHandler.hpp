#ifndef APPLICATION_MAZECHANGEHANDLER_HPP
#define APPLICATION_MAZECHANGEHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class MazeChangeHandler : public IHandler
    {
      public:
        MazeChangeHandler(gui::MainWindow& mainWindow,
                          simulation::Simulation& simulation,
                          QTimer& timer);

      public slots:
        void doOnMazeChange(const QString& text);

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

#endif   // APPLICATION_MAZECHANGEHANDLER_HPP
