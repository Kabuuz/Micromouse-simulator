#include <QHBoxLayout>
#include <gui/ControlGroupBox.hpp>

namespace gui
{
ControlGroupBox::ControlGroupBox(QString title) :
    QGroupBox(title),
    intervalLabel_(new QLabel("Simulation step interval:")),
    slider_(new QSlider(Qt::Horizontal)),
    sliderLabel_(new QLabel("")),
    sliderUnitLabel_(new QLabel("")),
    controlButtons_({{BUTTON_START, new QPushButton("Start")},
                     {BUTTON_SAVE, new QPushButton("Save")},
                     {BUTTON_PAUSE, new QPushButton("Pause")},
                     {BUTTON_RESET, new QPushButton("Reset")}})
{
    QVBoxLayout* layout = new QVBoxLayout;

    QGroupBox* upperGroupBox = new QGroupBox();
    QHBoxLayout* upperGroupBoxLayout = new QHBoxLayout;

    upperGroupBoxLayout->addWidget(controlButtons_.at(BUTTON_RESET));
    upperGroupBoxLayout->addWidget(controlButtons_.at(BUTTON_START));
    upperGroupBoxLayout->addWidget(controlButtons_.at(BUTTON_PAUSE));
    upperGroupBoxLayout->addWidget(controlButtons_.at(BUTTON_SAVE));
    upperGroupBoxLayout->setMargin(0);
    upperGroupBox->setLayout(upperGroupBoxLayout);

    QGroupBox* lowerGroupBox = new QGroupBox();
    QVBoxLayout* lowerGroupBoxLayout = new QVBoxLayout;

    QGroupBox* sliderGroupBox = new QGroupBox();
    QHBoxLayout* sliderGroupBoxLayout = new QHBoxLayout;

    sliderGroupBoxLayout->addWidget(slider_);
    sliderGroupBoxLayout->addWidget(sliderLabel_);
    sliderGroupBoxLayout->addWidget(sliderUnitLabel_);
    sliderGroupBoxLayout->setMargin(0);
    sliderGroupBox->setLayout(sliderGroupBoxLayout);

    lowerGroupBoxLayout->addWidget(intervalLabel_);
    lowerGroupBoxLayout->addWidget(sliderGroupBox);
    lowerGroupBox->setLayout(lowerGroupBoxLayout);

    layout->addWidget(upperGroupBox);
    layout->addWidget(lowerGroupBox);

    this->setContentsMargins(0, 0, 0, 0);

    this->setLayout(layout);
}

std::map<ButtonsEnum, QPushButton*>& ControlGroupBox::getControlButtons()
{
    return controlButtons_;
}

QSlider* ControlGroupBox::getSlider()
{
    return slider_;
}

QLabel* ControlGroupBox::getSliderValueLabel()
{
    return sliderLabel_;
}

QLabel* ControlGroupBox::getSliderUnitLabel()
{
    return sliderUnitLabel_;
}

}   // namespace gui
