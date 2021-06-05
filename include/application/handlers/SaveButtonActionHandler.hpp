#ifndef APPLICATION_SAVEBUTTONACTIONHANDLER_HPP
#define APPLICATION_SAVEBUTTONACTIONHANDLER_HPP

#include <QTimer>
#include <application/handlers/IHandler.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
namespace handlers
{
    class SaveButtonActionHandler : public IHandler
    {
      public:
        SaveButtonActionHandler(gui::MainWindow& mainWindow,
                                simulation::Simulation& simulation,
                                QTimer& timer);

      public slots:
        void doOnButtonSave();

      protected:
        virtual void handle(std::variant<int, std::string> change) override;

      private:
        void saveImage(std::string path);
        void saveLogs(std::string path);
        void saveStatistics(std::string path);
        std::string generateFilename(std::string algorithmName, std::string mazeName, int fileType);
        std::string getFileType(int fileType);
        std::string getFileExtension(int fileType);
        std::string getDate();
        void saveMazeFile(std::ofstream& file);

        gui::MainWindow& mainWindow_;
        simulation::Simulation& simulation_;
        QTimer& timer_;
        QString prefix_;
    };   // namespace IHandler

}   // namespace handlers
}   // namespace application

#endif   // APPLICATION_SAVEBUTTONACTIONHANDLER_HPP
