#include "gui/mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QtWidgets>

namespace gui
{
MainWindow::MainWindow(gui::IPaintingWidgetHelper& helper, QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    topLeftGroupBox_ = new SettingsGroupBox("Settings");
    topRightGroupBox_ = new ControlGroupBox("Control");
    centralGroupBox_ = new InformationGroupBox(helper);
    bottomGroupBox_ = new StatisticsGroupBox("Statistics");

    mainWidget_ = new QWidget();

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(topLeftGroupBox_, 0, 0, 1, 1);
    mainLayout->addWidget(topRightGroupBox_, 0, 1, 1, 1);
    mainLayout->addWidget(centralGroupBox_, 1, 0, 1, 2);
    mainLayout->addWidget(bottomGroupBox_, 2, 0, 1, 2);

    mainWidget_->setLayout(mainLayout);
    setCentralWidget(mainWidget_);

    setWindowTitle("Micromouse Simulator");
}

SettingsGroupBox* MainWindow::getSettingsGroupBox()
{
    return topLeftGroupBox_;
}

ControlGroupBox* MainWindow::getControlGroupBox()
{
    return topRightGroupBox_;
}

InformationGroupBox* MainWindow::getInformationGroupBox()
{
    return centralGroupBox_;
}

StatisticsGroupBox* MainWindow::getStatisticsGroupBox()
{
    return bottomGroupBox_;
}

MainWindow::~MainWindow()
{
    delete ui;
}
}   // namespace gui
