#include <QDebug>
#include <application/handlers/ScanButtonActionHandler.hpp>
#include <filesystem>

namespace application
{
namespace handlers
{
    ScanButtonActionHandler::ScanButtonActionHandler(gui::MainWindow& mainWindow,
                                                     simulation::Simulation& simulation,
                                                     QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("ScanButtonActionHandler")
    {}

    void ScanButtonActionHandler::doOnAction()
    {
        handle({});
    }

    void ScanButtonActionHandler::handle(std::variant<int, std::string> change)
    {
        mainWindow_.getSettingsGroupBox()->getMazeComboBox()->clear();

        auto files = scanForMazeFiles();

        filterFiles(files);

        for (const auto& file : files)
        {
            mainWindow_.getSettingsGroupBox()->getMazeComboBox()->addItem(
                QString::fromStdString(file));
        }
    }

    std::vector<std::string> ScanButtonActionHandler::scanForMazeFiles()
    {
        std::vector<std::string> filesInDirectory;

        std::string path
            = mainWindow_.getSettingsGroupBox()->getMazeDirectoryLineEdit()->text().toStdString();

        if (path.empty() || !std::filesystem::exists(path))
        {
            return filesInDirectory;
        }

        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            filesInDirectory.push_back(entry.path());
        }

        return filesInDirectory;
    }

    void ScanButtonActionHandler::filterFiles(std::vector<std::string>& files)
    {
        std::vector<std::string> extensions = {".csv", ".txt"};

        auto hasInvalidExtension = [&extensions](const std::string& file) {
            return std::none_of(
                extensions.begin(), extensions.end(), [&file](const auto& extension) {
                    std::size_t pos = file.find_last_of(extension);
                    return pos != std::string::npos;
                });
        };

        // remove files with invalid extension
        std::remove_if(files.begin(), files.end(), hasInvalidExtension);

        // leave only filename with extension
        for (auto& file : files)

        {
            std::size_t pos = file.find_last_of("/");

            if (pos != std::string::npos)
            {
                pos++;
                file = file.substr(pos);
            }
        }
    }

}   // namespace handlers
}   // namespace application
