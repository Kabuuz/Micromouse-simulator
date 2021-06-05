#ifndef APPLICATION_PAINT_DATAPAINTER_HPP
#define APPLICATION_PAINT_DATAPAINTER_HPP

#include <QPainter>
#include <QPen>
#include <application/paint/IPainter.hpp>
#include <simulation/fwd.hpp>
#include <QFont>

namespace application
{
namespace paint
{
    class DataPainter : public IPainter
    {
      public:
        DataPainter(simulation::ValuesArray& data);

        virtual void paint(QPainter* painter) override;
        virtual void setColor(unsigned int color) override;
        virtual void setWidth(unsigned int width) override;

      private:
        QPen pen_;
        QFont font_;
        simulation::ValuesArray& data_;
    };
}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_DATAPAINTER_HPP
