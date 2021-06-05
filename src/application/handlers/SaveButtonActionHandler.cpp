#include <QDebug>
#include <QImage>
#include <QPainter>
#include <application/handlers/SaveButtonActionHandler.hpp>
#include <application/paint/PaintingSettings.hpp>
#include <application/paint/PaintingWidgetHelper.hpp>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace application
{
namespace handlers
{
    namespace
    {
        constexpr char DOT_REPLACEMENT = '#';
        constexpr unsigned int IMAGE = 1;
        constexpr unsigned int LOGS = 2;
        constexpr unsigned int STATS = 3;
    }   // namespace

    SaveButtonActionHandler::SaveButtonActionHandler(gui::MainWindow& mainWindow,
                                                     simulation::Simulation& simulation,
                                                     QTimer& timer) :
        mainWindow_(mainWindow),
        simulation_(simulation),
        timer_(timer),
        prefix_("SaveButtonActionHandler")
    {}

    void SaveButtonActionHandler::doOnButtonSave()
    {
        handle({});
    }

    void SaveButtonActionHandler::handle(std::variant<int, std::string> change)
    {
        std::string path
            = mainWindow_.getSettingsGroupBox()->getsaveDirectoryLineEdit()->text().toStdString();

        if (path.empty())
        {
            return;
        }

        if (std::filesystem::exists(path))
        {
            saveImage(path);        // filename: algorithm_maze_img_date.png
            saveLogs(path);         // filename: algorithm_maze_log_date.txt
            saveStatistics(path);   // filename: algorithm_maze_stats_date.txt
        }
    }

    void SaveButtonActionHandler::saveImage(std::string path)
    {
        path += generateFilename(
            mainWindow_.getSettingsGroupBox()->getAlgorithmComboBox()->currentText().toStdString(),
            mainWindow_.getSettingsGroupBox()->getMazeComboBox()->currentText().toStdString(),
            IMAGE);

        QImage img(paint::PAINTING_AREA_WIDTH, paint::PAINTING_AREA_HEIGHT, QImage::Format_ARGB32);

        QPainter painter;
        painter.begin(&img);

        paint::PaintingWidgetHelper helper(simulation_);
        helper.paint(&painter);

        painter.end();

        try
        {
            img.save(QString::fromStdString(path));
        }
        catch (...)
        {
            qDebug() << prefix_ << "Invalid save path: " << QString::fromStdString(path);
        }
    }

    void SaveButtonActionHandler::saveLogs(std::string path)
    {
        path += generateFilename(
            mainWindow_.getSettingsGroupBox()->getAlgorithmComboBox()->currentText().toStdString(),
            mainWindow_.getSettingsGroupBox()->getMazeComboBox()->currentText().toStdString(),
            LOGS);

        QString data = mainWindow_.getInformationGroupBox()->getLogWidget()->toPlainText();
        QStringList dataLines = data.split(QRegExp("[\n]"), QString::SkipEmptyParts);

        std::ofstream file;
        file.open(path);

        if (!file.good())
        {
            qDebug() << prefix_ << "Invalid save path: " << QString::fromStdString(path);
            return;
        }

        for (int i = 0; i < dataLines.size(); ++i)
        {
            file << dataLines.at(i).toStdString() + "\n";
        }

        saveMazeFile(file);

        file.close();
    }

    void SaveButtonActionHandler::saveMazeFile(std::ofstream& file)
    {
        file << "\n";
        file << "Maze data:\n";

        std::string mazeDirectory
            = mainWindow_.getSettingsGroupBox()->getMazeDirectoryLineEdit()->text().toStdString()
            + mainWindow_.getSettingsGroupBox()->getMazeComboBox()->currentText().toStdString();

        std::ifstream mazeFile;
        mazeFile.open(mazeDirectory);

        if (mazeFile.good())
        {
            std::string line;
            while (std::getline(mazeFile, line))
            {
                file << (line);
            }
        }

        mazeFile.close();
    }

    void SaveButtonActionHandler::saveStatistics(std::string path)
    {
        path += generateFilename(
            mainWindow_.getSettingsGroupBox()->getAlgorithmComboBox()->currentText().toStdString(),
            mainWindow_.getSettingsGroupBox()->getMazeComboBox()->currentText().toStdString(),
            STATS);

        std::ofstream file;
        file.open(path);

        if (!file.good())
        {
            qDebug() << prefix_ << "Invalid save path: " << QString::fromStdString(path);
            return;
        }

        using guiStat = gui::StatisticsEnum;
        using simStat = simulation::StatisticId;

        std::vector<guiStat> statistics {guiStat::STATISTIC_X,
                                         guiStat::STATISTIC_Y,
                                         guiStat::STATISTIC_TURNS,
                                         guiStat::STATISTIC_DISTANCE,
                                         guiStat::STATISTIC_DISCOVERED,
                                         guiStat::STATISTIC_VISITED_AGAIN};

        auto& labels = mainWindow_.getStatisticsGroupBox()->getStatisticLabels();
        auto& values = mainWindow_.getStatisticsGroupBox()->getStatisticValueLabels();

        for (const auto& statistic : statistics)
        {
            file << labels.at(statistic)->text().toStdString()
                    + values.at(statistic)->text().toStdString() + "\n";
        }

        file.close();
    }

    std::string SaveButtonActionHandler::generateFilename(std::string algorithmName,
                                                          std::string mazeName,
                                                          int fileType)
    {
        std::replace(mazeName.begin(), mazeName.end(), '.', DOT_REPLACEMENT);
        std::string fileName = algorithmName + "_" + mazeName + "_";
        // extension

        // file type
        fileName += getFileType(fileType);

        // date
        fileName += getDate();

        // extension
        fileName += getFileExtension(fileType);

        return fileName;
    }

    std::string SaveButtonActionHandler::getFileType(int fileType)
    {
        if (fileType == IMAGE)
        {
            return "img";
        }
        else if (fileType == LOGS)
        {
            return "log";
        }
        else if (fileType == STATS)
        {
            return "stats";
        }

        return "";
    }

    std::string SaveButtonActionHandler::getFileExtension(int fileType)
    {
        if (fileType == IMAGE)
        {
            return ".png";
        }
        else if (fileType == LOGS)
        {
            return ".txt";
        }
        else if (fileType == STATS)
        {
            return ".txt";
        }

        return "";
    }

    std::string SaveButtonActionHandler::getDate()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "_%d-%m-%Y_%H-%M-%S");
        auto str = oss.str();

        return str;
    }

}   // namespace handlers
}   // namespace application
