#ifndef APPLICATION_PAINT_PAINTINGWIDGETHELPER_HPP
#define APPLICATION_PAINT_PAINTINGWIDGETHELPER_HPP

#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <application/paint/IPainter.hpp>
#include <gui/IPaintingWidgetHelper.hpp>
#include <simulation/Simulation.hpp>

namespace application
{
namespace paint
{
    class PaintingWidgetHelper : public gui::IPaintingWidgetHelper
    {
      public:
        PaintingWidgetHelper(simulation::Simulation& simulation);

      public:
        virtual void paint(QPainter* painter, QPaintEvent* event= nullptr) override;

      private:
        void createPainters();
        void setBackground(QPainter* painter);

        simulation::Simulation& simulation_;
        std::vector<std::unique_ptr<paint::IPainter>> painters_;
        QString prefix_;
    };

}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_PAINTINGWIDGETHELPER_HPP
