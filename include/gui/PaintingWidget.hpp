#ifndef GUI_PAINTING_WIDGET_HPP
#define GUI_PAINTING_WIDGET_HPP

#include <QString>
#include <QWidget>
#include <gui/IPaintingWidgetHelper.hpp>

namespace gui
{
class PaintingWidget : public QWidget
{
    Q_OBJECT

  public:
    PaintingWidget(IPaintingWidgetHelper& helper, QWidget* parent);

  public slots:
    void animate();

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    IPaintingWidgetHelper& helper_;
    QString prefix_;
};

}   // namespace gui

#endif   // GUI_PAINTING_WIDGET_HPP
