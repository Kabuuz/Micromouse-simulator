#include <QGridLayout>
#include <gui/StatisticsGroupBox.hpp>

namespace gui
{
StatisticsGroupBox::StatisticsGroupBox(QString title) : QGroupBox(title)
{
    QGridLayout* layout = new QGridLayout;

    statisticLabels_ = {{STATISTIC_X, new QLabel("X:")},
                        {STATISTIC_Y, new QLabel("Y:")},
                        {STATISTIC_DISTANCE, new QLabel("Distance:")},
                        {STATISTIC_TURNS, new QLabel("Turns:")},
                        {STATISTIC_DISCOVERED, new QLabel("Discovered:")},
                        {STATISTIC_VISITED_AGAIN, new QLabel("Visited several times:")}};
    statisticLabelValues_ = {{STATISTIC_X, new QLabel("0")},
                             {STATISTIC_Y, new QLabel("0")},
                             {STATISTIC_DISTANCE, new QLabel("0")},
                             {STATISTIC_TURNS, new QLabel("0")},
                             {STATISTIC_DISCOVERED, new QLabel("0")},
                             {STATISTIC_VISITED_AGAIN, new QLabel("0")}};

    layout->addWidget(statisticLabels_.at(STATISTIC_X), 1, 0);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_X), 1, 1);
    layout->addWidget(statisticLabels_.at(STATISTIC_Y), 2, 0);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_Y), 2, 1);
    layout->addWidget(statisticLabels_.at(STATISTIC_DISTANCE), 1, 2);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_DISTANCE), 1, 3);
    layout->addWidget(statisticLabels_.at(STATISTIC_TURNS), 2, 2);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_TURNS), 2, 3);
    layout->addWidget(statisticLabels_.at(STATISTIC_DISCOVERED), 1, 4);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_DISCOVERED), 1, 5);
    layout->addWidget(statisticLabels_.at(STATISTIC_VISITED_AGAIN), 2, 4);
    layout->addWidget(statisticLabelValues_.at(STATISTIC_VISITED_AGAIN), 2, 5);

    this->setLayout(layout);
}

std::map<StatisticsEnum, QLabel*>& StatisticsGroupBox::getStatisticValueLabels()
{
    return statisticLabelValues_;
}

std::map<StatisticsEnum, QLabel*>& StatisticsGroupBox::getStatisticLabels()
{
    return statisticLabels_;
}

}   // namespace gui
