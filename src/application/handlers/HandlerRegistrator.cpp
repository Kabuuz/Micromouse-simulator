#include <QDebug>
#include <application/handlers/AlgorithmChangeHandler.hpp>
#include <application/handlers/HandlerRegistrator.hpp>
#include <application/handlers/MazeChangeHandler.hpp>
#include <application/handlers/PauseButtonActionHandler.hpp>
#include <application/handlers/ResetButtonActionHandler.hpp>
#include <application/handlers/SaveButtonActionHandler.hpp>
#include <application/handlers/SliderChangeHandler.hpp>
#include <application/handlers/ScanButtonActionHandler.hpp>
#include <application/handlers/StartButtonActionHandler.hpp>
#include <application/handlers/TextEditHandler.hpp>
#include <application/handlers/TimerActionHandler.hpp>

namespace application
{
namespace handlers
{
    HandlerRegistrator::HandlerRegistrator(gui::MainWindow& mainWindow,
                                           simulation::Simulation& simulation,
                                           algorithms::AlgorithmsRegistrator& algorithmsRegistrator,
                                           QTimer& timer) :
        mainWindow_(mainWindow), simulation_(simulation),algorithmsRegistrator_(algorithmsRegistrator), timer_(timer)
    {}

    void HandlerRegistrator::registerHandlers()
    {
        registerTextEditHandler();
        registerScanButtonActionHandler();
        registerPauseButtonActionHandler();
        registerStartButtonActionHandler();
        registerResetButtonActionHandler();
        registerSaveButtonActionHandler();
        registerMazeChangeHandler();
        registerAlgorithmChangeHandler();
        registerSlideChangeHandler();
        registerTimerActionHandler();
    }

    void HandlerRegistrator::registerTextEditHandler()
    {
        auto textEditHandler = std::make_unique<TextEditHandler>(
            mainWindow_.getInformationGroupBox()->getLogWidget());

        connect(simulation_.getMicromouse().get(),
                &simulation::Robot::signalOnMovingForward,
                textEditHandler.get(),
                &TextEditHandler::doOnTextAdded);
        connect(simulation_.getMicromouse().get(),
                &simulation::Robot::signalOnTurningLeft,
                textEditHandler.get(),
                &TextEditHandler::doOnTextAdded);
        connect(simulation_.getMicromouse().get(),
                &simulation::Robot::signalOnTurningRight,
                textEditHandler.get(),
                &TextEditHandler::doOnTextAdded);

        handlers_.push_back(std::move(textEditHandler));
    }

    void HandlerRegistrator::registerScanButtonActionHandler() 
    {
        auto scanButtonActionHandler
            = std::make_unique<ScanButtonActionHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getSettingsGroupBox()->getScanButton(),
                &QPushButton::pressed,
                scanButtonActionHandler.get(),
                &ScanButtonActionHandler::doOnAction);

        handlers_.push_back(std::move(scanButtonActionHandler));
    }

    void HandlerRegistrator ::registerPauseButtonActionHandler()
    {
        using button = gui::ButtonsEnum;

        auto pauseButtonActionHandler
            = std::make_unique<PauseButtonActionHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getControlGroupBox()->getControlButtons().at(button::BUTTON_PAUSE),
                &QPushButton::pressed,
                pauseButtonActionHandler.get(),
                &PauseButtonActionHandler::doOnButtonPause);

        handlers_.push_back(std::move(pauseButtonActionHandler));
    }
    void HandlerRegistrator ::registerStartButtonActionHandler()
    {
        using button = gui::ButtonsEnum;

        auto startButtonActionHandler
            = std::make_unique<StartButtonActionHandler>(mainWindow_, simulation_,algorithmsRegistrator_, timer_);

        connect(mainWindow_.getControlGroupBox()->getControlButtons().at(button::BUTTON_START),
                &QPushButton::pressed,
                startButtonActionHandler.get(),
                &StartButtonActionHandler::doOnButtonStart);

        handlers_.push_back(std::move(startButtonActionHandler));
    }

    void HandlerRegistrator ::registerResetButtonActionHandler()
    {
        using button = gui::ButtonsEnum;

        auto resetButtonActionHandler
            = std::make_unique<ResetButtonActionHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getControlGroupBox()->getControlButtons().at(button::BUTTON_RESET),
                &QPushButton::pressed,
                resetButtonActionHandler.get(),
                &ResetButtonActionHandler::doOnButtonReset);

        handlers_.push_back(std::move(resetButtonActionHandler));
    }
    void HandlerRegistrator ::registerSaveButtonActionHandler()
    {
        using button = gui::ButtonsEnum;

        auto saveButtonActionHandler
            = std::make_unique<SaveButtonActionHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getControlGroupBox()->getControlButtons().at(button::BUTTON_SAVE),
                &QPushButton::pressed,
                saveButtonActionHandler.get(),
                &SaveButtonActionHandler::doOnButtonSave);

        handlers_.push_back(std::move(saveButtonActionHandler));
    }

    void HandlerRegistrator ::registerMazeChangeHandler()
    {
        auto mazeChangeHandler
            = std::make_unique<MazeChangeHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getSettingsGroupBox()->getMazeComboBox(),
                &QComboBox::currentTextChanged,
                mazeChangeHandler.get(),
                &MazeChangeHandler::doOnMazeChange);

        handlers_.push_back(std::move(mazeChangeHandler));
    }
    void HandlerRegistrator ::registerAlgorithmChangeHandler()
    {
        auto algorithmChangeHandler
            = std::make_unique<AlgorithmChangeHandler>(mainWindow_, simulation_,algorithmsRegistrator_, timer_);

        connect(mainWindow_.getSettingsGroupBox()->getAlgorithmComboBox(),
                &QComboBox::currentTextChanged,
                algorithmChangeHandler.get(),
                &AlgorithmChangeHandler::doOnAlgorithmChange);

        handlers_.push_back(std::move(algorithmChangeHandler));
    }

    void HandlerRegistrator::registerSlideChangeHandler()
    {
        auto sliderChangeHandler
            = std::make_unique<SliderChangeHandler>(mainWindow_, simulation_, timer_);

        connect(mainWindow_.getControlGroupBox()->getSlider(),
                &QSlider::valueChanged,
                sliderChangeHandler.get(),
                &SliderChangeHandler::doOnSliderChange);

        handlers_.push_back(std::move(sliderChangeHandler));
    }

    void HandlerRegistrator::registerTimerActionHandler()
    {
        auto timerActionHandler
            = std::make_unique<TimerActionHandler>(mainWindow_, simulation_, timer_);

        connect(
            &timer_, &QTimer::timeout, timerActionHandler.get(), &TimerActionHandler::doOnTimeout);

        handlers_.push_back(std::move(timerActionHandler));
    }

}   // namespace handlers
}   // namespace application
