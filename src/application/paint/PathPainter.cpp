#include <QPainter>
#include <application/paint/PathPainter.hpp>
#include <application/paint/PaintingSettings.hpp>

namespace application
{
namespace paint
{
    PathPainter::PathPainter(simulation::VisitedArray& visitedArray) : visitedArray_(visitedArray) {}

    void PathPainter::paint(QPainter* painter)
    {
        painter->setPen(pen_);

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                if (visitedArray_.at(row).at(column) == true)
                {
                    int x = column * (WALL_WIDTH + CELL_WIDTH) + WALL_WIDTH;
                    int y = row * (WALL_WIDTH + CELL_HEIGHT) + WALL_WIDTH;
                    painter->fillRect(QRect(x, y, CELL_WIDTH, CELL_HEIGHT), colorGradient_);
                }
            }
        }
    }

    void PathPainter::setColor(unsigned int color)
    {
        pen_.setColor(color);

        colorGradient_= QLinearGradient(0, 0, 0, 100);
        colorGradient_.setColorAt(0.0, color);
        colorGradient_.setColorAt(1.0, color);
    }

    void PathPainter::setWidth(unsigned int width)
    {
        pen_.setWidth(width);
    }

}   // namespace paint
}   // namespace application
