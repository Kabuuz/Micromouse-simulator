#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <gui/PaintingWidget.hpp>

namespace gui
{
PaintingWidget::PaintingWidget(IPaintingWidgetHelper& helper, QWidget* parent) :
    QWidget(parent), helper_(helper), prefix_("PaintingWidget")
{}

void PaintingWidget::animate()
{
    update();
}

void PaintingWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper_.paint(&painter, event);
    painter.end();
}

}   // namespace gui
