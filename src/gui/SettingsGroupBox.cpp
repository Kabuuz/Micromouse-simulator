#include <QGridLayout>
#include <gui/SettingsGroupBox.hpp>

namespace gui
{
SettingsGroupBox::SettingsGroupBox(QString title) :
    QGroupBox(title),
    mazeDirectory_(new QLabel("Maze directory:")),
    mazePath_(new QLineEdit("")),
    scanButton_(new QPushButton("Scan")),
    mazeLabel_(new QLabel("Maze:")),
    mazeComboBox_(new QComboBox()),
    algorithmParametersLabel_(new QLabel("Parameters:")),
    algorithmParameters_(new QLineEdit()),
    algorithmLabel_(new QLabel("Algorithm:")),
    algorithmComboBox_(new QComboBox()),
    saveDirectoryLabel_(new QLabel("Save directory:")),
    saveDirectoryLineEdit_(new QLineEdit())
{
    QGridLayout* layout = new QGridLayout;

    layout->addWidget(mazeDirectory_, 0, 0);
    layout->addWidget(mazePath_, 0, 1, 1, 2);
    layout->addWidget(scanButton_, 0, 3);
    layout->addWidget(mazeLabel_, 1, 0);
    layout->addWidget(mazeComboBox_, 1, 1, 1, 3);
    layout->addWidget(algorithmLabel_, 2, 0);
    layout->addWidget(algorithmComboBox_, 2, 1, 1, 3);
    layout->addWidget(algorithmParametersLabel_, 3, 0);
    layout->addWidget(algorithmParameters_, 3, 1, 1, 3);
    layout->addWidget(saveDirectoryLabel_, 4, 0);
    layout->addWidget(saveDirectoryLineEdit_, 4, 1, 1, 3);

    this->setLayout(layout);

    this->setContentsMargins(0, 0, 0, 0);
}

QLineEdit* SettingsGroupBox::getMazeDirectoryLineEdit()
{
    return mazePath_;
}

QPushButton* SettingsGroupBox::getScanButton()
{
    return scanButton_;
}

QComboBox* SettingsGroupBox::getMazeComboBox()
{
    return mazeComboBox_;
}

QComboBox* SettingsGroupBox::getAlgorithmComboBox()
{
    return algorithmComboBox_;
}

QLineEdit* SettingsGroupBox::getParametersLineEdit()
{
    return algorithmParameters_;
}

QLineEdit* SettingsGroupBox::getsaveDirectoryLineEdit()
{
    return saveDirectoryLineEdit_;
}

void SettingsGroupBox::disableElementsDuringSimulation()
{
    mazeComboBox_->setEnabled(false);
    algorithmComboBox_->setEnabled(false);
}

void SettingsGroupBox::enableElementsDuringSimulation()
{
    mazeComboBox_->setEnabled(true);
    algorithmComboBox_->setEnabled(true);
}

}   // namespace gui
