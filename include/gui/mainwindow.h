#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <gui/ControlGroupBox.hpp>
#include <gui/InformationGroupBox.hpp>
#include <gui/SettingsGroupBox.hpp>
#include <gui/StatisticsGroupBox.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

namespace gui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(gui::IPaintingWidgetHelper& helper, QWidget* parent = nullptr);
    ~MainWindow();

    SettingsGroupBox* getSettingsGroupBox();
    ControlGroupBox* getControlGroupBox();
    InformationGroupBox* getInformationGroupBox();
    StatisticsGroupBox* getStatisticsGroupBox();

  private:
    QWidget* mainWidget_;
    SettingsGroupBox* topLeftGroupBox_;
    ControlGroupBox* topRightGroupBox_;
    InformationGroupBox* centralGroupBox_;
    StatisticsGroupBox* bottomGroupBox_;

    Ui::MainWindow* ui;
};
}   // namespace gui

#endif   // GUI_MAINWINDOW_H
