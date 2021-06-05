#ifndef APPLICATION_SCANBUTTONACTIONHANDLER_HPP
#define APPLICATION_SCANBUTTONACTIONHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class ScanButtonActionHandler : public IHandler
    {
      public:
        ScanButtonActionHandler(gui::MainWindow& mainWindow,
                                simulation::Simulation& simulation,
                                QTimer& timer);

      public slots:
        void doOnAction();

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        std::vector<std::string>  scanForMazeFiles();
        void filterFiles(std::vector<std::string>& files);

        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        QTimer& timer_;
        QString prefix_;
    };   // namespace IHandler

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_SCANBUTTONACTIONHANDLER_HPP
