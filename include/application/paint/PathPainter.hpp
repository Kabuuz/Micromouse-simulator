#ifndef APPLICATION_PAINT_PATHPAINTER_HPP
#define APPLICATION_PAINT_PATHPAINTER_HPP

#include <QLinearGradient>
#include <QPen>
#include <application/paint/IPainter.hpp>
#include <simulation/fwd.hpp>

namespace application
{
namespace paint
{
    class PathPainter : public IPainter
    {
      public:
        PathPainter(simulation::VisitedArray& visitedArray);

        virtual void paint(QPainter* painter) override;
        virtual void setColor(unsigned int color) override;
        virtual void setWidth(unsigned int width) override;

      private:
        QPen pen_;
        QLinearGradient colorGradient_;
        simulation::VisitedArray& visitedArray_;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_PATHPAINTER_HPP
