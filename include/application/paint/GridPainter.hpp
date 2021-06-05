#ifndef APPLICATION_PAINT_GRIDPAINTER_HPP
#define APPLICATION_PAINT_GRIDPAINTER_HPP

#include <QPen>
#include <application/paint/IPainter.hpp>

namespace application
{
namespace paint
{
    class GridPainter : public IPainter
    {
      public:
        GridPainter();

        virtual void paint(QPainter* painter) override;
        virtual void setColor(unsigned int color) override;
        virtual void setWidth(unsigned int width) override;

      private:
        QPen pen_;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_GRIDPAINTER_HPP
