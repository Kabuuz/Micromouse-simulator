#ifndef GUI_CONTROLGROUPBOX_HPP
#define GUI_CONTROLGROUPBOX_HPP

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

namespace gui
{
enum ButtonsEnum
{
    BUTTON_PAUSE,
    BUTTON_START,
    BUTTON_RESET,
    BUTTON_SAVE,
};

class ControlGroupBox : public QGroupBox
{
  public:
    ControlGroupBox(QString title);
    std::map<ButtonsEnum, QPushButton*>& getControlButtons();
    QSlider* getSlider();
    QLabel* getSliderValueLabel();
    QLabel* getSliderUnitLabel();

  private:
    std::map<ButtonsEnum, QPushButton*> controlButtons_;
    QLabel* intervalLabel_;
    QSlider* slider_;
    QLabel* sliderLabel_;
    QLabel* sliderUnitLabel_;
};
}   // namespace gui

#endif   // GUI_CONTROLGROUPBOX_HPP
