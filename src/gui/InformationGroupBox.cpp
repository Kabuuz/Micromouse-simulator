#include <QHBoxLayout>
#include <gui/InformationGroupBox.hpp>

namespace gui
{
InformationGroupBox::InformationGroupBox(IPaintingWidgetHelper& helper) :
    QGroupBox(),
    paintingWidgetFrame_(new QLabel()),
    paintingWidget_(new PaintingWidget(helper, paintingWidgetFrame_)),
    logWidget_(new QTextEdit())
{
    QHBoxLayout* layout = new QHBoxLayout;

    logWidget_->setReadOnly(true);

    layout->addWidget(paintingWidgetFrame_);
    layout->addWidget(logWidget_);

    this->setLayout(layout);
}

PaintingWidget* InformationGroupBox::getPaintingWidget()
{
    return paintingWidget_;
}

QTextEdit* InformationGroupBox::getLogWidget()
{
    return logWidget_;
}

void InformationGroupBox::setPaintingWidgetSize(int width, int height)
{
    paintingWidget_->setFixedSize(width, height);

    paintingWidgetFrame_->setFixedWidth(width);
    paintingWidgetFrame_->setFixedHeight(height);
}

void InformationGroupBox::setLogWidgetSize(int width, int height)
{
    logWidget_->setFixedWidth(width);
    logWidget_->setFixedHeight(height);
}

}   // namespace gui
