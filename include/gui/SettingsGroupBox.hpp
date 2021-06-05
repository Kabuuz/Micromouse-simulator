#ifndef GUI_SETTINGSGROUPBOX_HPP
#define GUI_SETTINGSGROUPBOX_HPP

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace gui
{
class SettingsGroupBox : public QGroupBox
{
  public:
    SettingsGroupBox(QString title);
    QLineEdit* getMazeDirectoryLineEdit();
    QPushButton* getScanButton();
    QLineEdit* getParametersLineEdit();
    QLineEdit* getsaveDirectoryLineEdit();
    QComboBox* getMazeComboBox();
    QComboBox* getAlgorithmComboBox();
    void disableElementsDuringSimulation();
    void enableElementsDuringSimulation();

  private:
    QLabel* mazeDirectory_;
    QLineEdit* mazePath_;
    QPushButton* scanButton_;
    QLabel* mazeLabel_;
    QComboBox* mazeComboBox_;
    QLabel* algorithmLabel_;
    QComboBox* algorithmComboBox_;
    QLabel* algorithmParametersLabel_;
    QLineEdit* algorithmParameters_;
    QLabel* saveDirectoryLabel_;
    QLineEdit* saveDirectoryLineEdit_;
};
}   // namespace gui
#endif   // GUI_SETTINGSGROUPBOX_HPP
