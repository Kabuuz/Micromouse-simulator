#include <application/paint/DataPainter.hpp>
#include <application/paint/GridPainter.hpp>
#include <application/paint/MazePainter.hpp>
#include <application/paint/PaintingSettings.hpp>
#include <application/paint/PaintingWidgetHelper.hpp>
#include <application/paint/PathPainter.hpp>
#include <application/paint/RobotPainter.hpp>
#include <simulation/fwd.hpp>
#include <simulation/maze/MazeSettings.hpp>
#include <QRectF>

namespace application
{
namespace paint
{
    PaintingWidgetHelper::PaintingWidgetHelper(simulation::Simulation& simulation) :
        simulation_(simulation), prefix_("Helper")
    {
        createPainters();
    }

    void PaintingWidgetHelper::paint(QPainter* painter, QPaintEvent* event)
    {
        setBackground(painter);

        for (auto& objectPainter : painters_)
        {
            objectPainter->paint(painter);
        }
    }

    void PaintingWidgetHelper::createPainters()
    {
        auto gridPainter = std::make_unique<GridPainter>();
        gridPainter->setColor(GRID_COLOR);
        gridPainter->setWidth(WALL_WIDTH);

        auto mazePainter1 = std::make_unique<MazePainter>(simulation_.getSimulationMaze());
        mazePainter1->setColor(SIMULATION_MAZE_COLOR);
        mazePainter1->setWidth(WALL_WIDTH);

        auto mazePainter2 = std::make_unique<MazePainter>(simulation_.getMicromouse()->getMaze());
        mazePainter2->setColor(MICROMOUSE_MAZE_COLOR);
        mazePainter2->setWidth(WALL_WIDTH);

        auto pathPainter
            = std::make_unique<PathPainter>(simulation_.getMicromouse()->getVisitedArray());
        pathPainter->setColor(VISITED_CELL_COLOR);
        pathPainter->setWidth(1);

        auto robotPainter = std::make_unique<RobotPainter>(*simulation_.getMicromouse());
        robotPainter->setColor(ROBOT_COLOR);
        robotPainter->setWidth(1);

        auto dataPainter
            = std::make_unique<DataPainter>(simulation_.getMicromouse()->getValuesArray());
        dataPainter->setColor(TEXT_COLOR);
        dataPainter->setWidth(FONT_SIZE);

        painters_.push_back(std::move(gridPainter));
        painters_.push_back(std::move(mazePainter1));
        painters_.push_back(std::move(mazePainter2));
        painters_.push_back(std::move(pathPainter));
        painters_.push_back(std::move(robotPainter));
        painters_.push_back(std::move(dataPainter));
    }

    void PaintingWidgetHelper::setBackground(QPainter* painter)
    {
        QRectF rect(0,0,PAINTING_AREA_WIDTH,PAINTING_AREA_HEIGHT);
        painter->fillRect(rect, BACKGROUND_COLOR);
    }

}   // namespace paint
}   // namespace application
