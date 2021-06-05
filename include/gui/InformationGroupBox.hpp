#ifndef GUI_INFORMATIONGROUPBOX_H
#define GUI_INFORMATIONGROUPBOX_H

#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <gui/IPaintingWidgetHelper.hpp>
#include <gui/PaintingWidget.hpp>

namespace gui
{
class InformationGroupBox : public QGroupBox
{
  public:
    InformationGroupBox(IPaintingWidgetHelper& helper);
    PaintingWidget* getPaintingWidget();
    QTextEdit* getLogWidget();
    void setPaintingWidgetSize(int width, int height);
    void setLogWidgetSize(int width, int height);

  private:
    QLabel* paintingWidgetFrame_;
    PaintingWidget* paintingWidget_;
    QTextEdit* logWidget_;
};
}   // namespace gui

#endif   // GUI_INFORMATIONGROUPBOX_H
