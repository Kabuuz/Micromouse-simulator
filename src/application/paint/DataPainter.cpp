#include <QDebug>
#include <application/paint/DataPainter.hpp>
#include <application/paint/PaintingSettings.hpp>
#include <sstream>
#include <iomanip>

namespace application
{
namespace paint
{
    DataPainter::DataPainter(simulation::ValuesArray& data) : data_(data) {}

    void DataPainter::paint(QPainter* painter)
    {
        painter->setPen(pen_);
        painter->setFont(font_);

        for (int row = 0; row < simulation::MAZE_ROWS; row++)
        {
            for (int column = 0; column < simulation::MAZE_COLUMNS; column++)
            {
                const auto& value = data_.at(row).at(column);
                if (value.has_value())
                {
                    int x = column * (WALL_WIDTH + CELL_WIDTH) + WALL_WIDTH;
                    int y = row * (WALL_WIDTH + CELL_HEIGHT) + WALL_WIDTH;

                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(1) << *value;
                    std::string s = stream.str();

                    painter->drawText(QRect(x, y, CELL_WIDTH, CELL_HEIGHT),
                                      Qt::AlignCenter,
                                      QString::fromStdString(s));
                }
            }
        }
    }

    void DataPainter::setColor(unsigned int color)
    {
        pen_.setColor(color);
    }

    void DataPainter::setWidth(unsigned int width)
    {
        font_.setPixelSize(width);
    }

}   // namespace paint
}   // namespace application
