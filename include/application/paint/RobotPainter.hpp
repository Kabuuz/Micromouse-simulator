#ifndef APPLICATION_PAINT_ROBOTPAINTER_HPP
#define APPLICATION_PAINT_ROBOTPAINTER_HPP

#include <QLinearGradient>
#include <QPen>
#include <application/paint/IPainter.hpp>
#include <simulation/robot/Micromouse.hpp>

namespace application
{
namespace paint
{
    class RobotPainter : public IPainter
    {
      public:
        RobotPainter(simulation::Micromouse& micromouse);

        virtual void paint(QPainter* painter) override;
        virtual void setColor(unsigned int color) override;
        virtual void setWidth(unsigned int width) override;

      private:
        QPen pen_;
        QLinearGradient bodyColorGradient_;
        QLinearGradient frontColorGradient_;
        simulation::Micromouse& micromouse_;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_ROBOTPAINTER_HPP
