#include <QPainter>
#include <application/paint/MazePainter.hpp>
#include <application/paint/PaintingSettings.hpp>

namespace application
{
namespace paint
{
    MazePainter::MazePainter(simulation::MazeWrapper& maze): maze_(maze) {}

    void MazePainter::paint(QPainter* painter)
    {
        for (unsigned int row = 0; row < CELL_ROWS; row++)
        {
            for (unsigned int column = 0; column < CELL_COLUMNS; column++)
            {
                paintSingleCell(painter, row, column, maze_.getCell(row, column));
            }
        }
    }

    void MazePainter::setColor(unsigned int color)
    {
        pen_.setColor(color);
    }

    void MazePainter::setWidth(unsigned int width)
    {
        pen_.setWidth(width);
    }

    void MazePainter::paintSingleCell(
        QPainter* painter, int row, int column,  simulation::Cell& cell)
    {
        painter->setPen(pen_);

        QPointF leftUpPoint(column * (WALL_WIDTH + CELL_WIDTH) + WALL_WIDTH / 2,
                            row * (WALL_WIDTH + CELL_HEIGHT) + WALL_WIDTH / 2);
        QPointF rightUpPoint = leftUpPoint + QPointF(WALL_WIDTH + CELL_WIDTH, 0);
        QPointF leftDownPoint = leftUpPoint + QPointF(0, WALL_WIDTH + CELL_WIDTH);
        QPointF rightDownPoint
            = leftUpPoint + QPointF(WALL_WIDTH + CELL_WIDTH, WALL_WIDTH + CELL_WIDTH);

        if (cell.getWall(simulation::Direction::North).getWallState()
            == simulation::WallState::Present)
        {
            painter->drawLine(leftUpPoint, rightUpPoint);
        }
        if (cell.getWall(simulation::Direction::East).getWallState()
            == simulation::WallState::Present)
        {
            painter->drawLine(rightUpPoint, rightDownPoint);
        }
        if (cell.getWall(simulation::Direction::South).getWallState()
            == simulation::WallState::Present)
        {
            painter->drawLine(leftDownPoint, rightDownPoint);
        }
        if (cell.getWall(simulation::Direction::West).getWallState()
            == simulation::WallState::Present)
        {
            painter->drawLine(leftUpPoint, leftDownPoint);
        }
    }

}   // namespace paint
}   // namespace application
