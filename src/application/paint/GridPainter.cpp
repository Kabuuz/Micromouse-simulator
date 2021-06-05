#include <QPainter>
#include <application/paint/GridPainter.hpp>
#include <application/paint/PaintingSettings.hpp>

namespace application
{
namespace paint
{
    GridPainter::GridPainter() {}

    void GridPainter::paint(QPainter* painter)
    {
        painter->setPen(pen_);

        for (unsigned int row = 0; row < CELL_ROWS; row++)
        {
            for (unsigned int column = 0; column < CELL_COLUMNS; column++)
            {
                QPointF leftUpPoint(column * (WALL_WIDTH + CELL_WIDTH) + WALL_WIDTH / 2,
                                    row * (WALL_WIDTH + CELL_HEIGHT) + WALL_WIDTH / 2);
                QPointF rightUpPoint = leftUpPoint + QPointF(WALL_WIDTH + CELL_WIDTH, 0);
                QPointF leftDownPoint = leftUpPoint + QPointF(0, WALL_WIDTH + CELL_WIDTH);
                QPointF rightDownPoint
                    = leftUpPoint + QPointF(WALL_WIDTH + CELL_WIDTH, WALL_WIDTH + CELL_WIDTH);

                painter->drawLine(leftUpPoint, rightUpPoint);
                painter->drawLine(leftUpPoint, leftDownPoint);
                painter->drawLine(rightUpPoint, rightDownPoint);
                painter->drawLine(leftDownPoint, rightDownPoint);
            }
        }
    }

    void GridPainter::setColor(unsigned int color)
    {
        pen_.setColor(color);
    }

    void GridPainter::setWidth(unsigned int width)
    {
        pen_.setWidth(width);
    }

}   // namespace paint
}   // namespace application
