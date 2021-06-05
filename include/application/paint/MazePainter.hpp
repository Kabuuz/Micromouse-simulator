#ifndef APPLICATION_PAINT_MAZEPAINTER_HPP
#define APPLICATION_PAINT_MAZEPAINTER_HPP

#include <QPen>
#include <application/paint/IPainter.hpp>
#include <simulation/maze/Cell.hpp>
#include <simulation/maze/MazeWrapper.hpp>

namespace application
{
namespace paint
{
    class MazePainter : public IPainter
    {
      public:
        MazePainter(simulation::MazeWrapper& maze);

        virtual void paint(QPainter* painter) override;
        virtual void setColor(unsigned int color) override;
        virtual void setWidth(unsigned int width) override;

      private:
        void paintSingleCell(QPainter* painter, int row, int column, simulation::Cell& cell);

        QPen pen_;
        simulation::MazeWrapper& maze_;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_MAZEPAINTER_HPP
