#include <QDebug>
#include <application/Application.hpp>
#include <application/paint/PaintingSettings.hpp>
#include <application/updaters/StatisticLabelUpdater.hpp>

namespace application
{
namespace
{
    constexpr int MINIMUM_TIME = 50;
    constexpr int MAXIMUM_TIME = 10000;
    const std::string TIME_UNIT = "ms";
}   // namespace

Application::Application() :
    simulation_(std::make_unique<simulation::Simulation>()),
    paintingWidgetHelper_(std::make_unique<paint::PaintingWidgetHelper>(*simulation_)),
    mainWindow_(std::make_unique<gui::MainWindow>(*paintingWidgetHelper_)),
    timer_(std::make_unique<QTimer>(mainWindow_.get())),
    algorithmsRegistrator_(
        std::make_unique<algorithms::AlgorithmsRegistrator>(simulation_->getMicromouse())),
    handlerRegistrator_(std::make_unique<handlers::HandlerRegistrator>(
        *mainWindow_, *simulation_, *algorithmsRegistrator_, *timer_)),
    prefix_("Application")
{
    algorithmsRegistrator_->registerAlgorithms();
    handlerRegistrator_->registerHandlers();

    initializeGuiElementsWithValues();

    updaters::StatisticLabelUpdater::update(
        simulation_->getStatistics(),
        mainWindow_->getStatisticsGroupBox()->getStatisticValueLabels());
}

void Application::startApplication()
{
    mainWindow_->show();
}

void Application::initializeGuiElementsWithValues()
{
    initializeGuiSettingsElements();
    initializeGuiControlElements();
    initializeGuiInformationElements();
}

void Application::initializeGuiSettingsElements()
{
    mainWindow_->getSettingsGroupBox()->getMazeComboBox()->clear();

    for (const auto& name : algorithmsRegistrator_->getNamesOfRegisteredAlgorithms())
    {
        mainWindow_->getSettingsGroupBox()->getAlgorithmComboBox()->addItem(
            QString::fromStdString(name));
    }

    mainWindow_->getSettingsGroupBox()->getParametersLineEdit()->setText(
        QString::fromStdString(algorithmsRegistrator_
                                   ->getAlgorithm(mainWindow_->getSettingsGroupBox()
                                                      ->getAlgorithmComboBox()
                                                      ->currentText()
                                                      .toStdString())
                                   ->getDefaultParamsString()));
}

void Application::initializeGuiControlElements()
{
    mainWindow_->getControlGroupBox()->getSlider()->setRange(MINIMUM_TIME, MAXIMUM_TIME);
    mainWindow_->getControlGroupBox()->getSliderValueLabel()->setText(
        QString::number(MINIMUM_TIME));
    mainWindow_->getControlGroupBox()->getSliderUnitLabel()->setText(
        QString::fromStdString(TIME_UNIT));
}

void Application::initializeGuiInformationElements()
{
    int controlGroupBoxWidth = 400;
    mainWindow_->getSettingsGroupBox()->setFixedWidth(paint::PAINTING_AREA_WIDTH);
    mainWindow_->getControlGroupBox()->setFixedWidth(controlGroupBoxWidth);
    mainWindow_->getInformationGroupBox()->setPaintingWidgetSize(paint::PAINTING_AREA_WIDTH,
                                                                 paint::PAINTING_AREA_HEIGHT);
    mainWindow_->getInformationGroupBox()->setLogWidgetSize(controlGroupBoxWidth,
                                                            paint::PAINTING_AREA_HEIGHT);

    mainWindow_->getInformationGroupBox()->getPaintingWidget()->animate();
}

}   // namespace application
