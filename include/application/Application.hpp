#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QObject>
#include <QString>
#include <QTimer>
#include <application/handlers/HandlerRegistrator.hpp>
#include <application/algorithms/AlgorithmsRegistrator.hpp>
#include <application/paint/PaintingWidgetHelper.hpp>
#include <gui/mainwindow.h>
#include <simulation/Simulation.hpp>

namespace application
{
class Application : public QObject
{
    Q_OBJECT

  public:
    Application();
    void startApplication();

  private:
    void initializeGuiElementsWithValues();
    void initializeGuiSettingsElements();
    void initializeGuiControlElements();
    void initializeGuiInformationElements();

    std::unique_ptr<simulation::Simulation> simulation_;
    std::unique_ptr<paint::PaintingWidgetHelper> paintingWidgetHelper_;
    std::unique_ptr<gui::MainWindow> mainWindow_;
    std::unique_ptr<QTimer> timer_;
    std::unique_ptr<algorithms::AlgorithmsRegistrator> algorithmsRegistrator_;
    std::unique_ptr<handlers::HandlerRegistrator> handlerRegistrator_;

    QString prefix_;
};

}   // namespace application

#endif   // APPLICATION_HPP
