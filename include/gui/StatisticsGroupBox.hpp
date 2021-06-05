#ifndef GUI_STATISTICSGROUPBOX_HPP
#define GUI_STATISTICSGROUPBOX_HPP

#include <QGroupBox>
#include <QLabel>

namespace gui
{
enum StatisticsEnum
{
    STATISTIC_X,
    STATISTIC_Y,
    STATISTIC_DISTANCE,
    STATISTIC_TURNS,
    STATISTIC_DISCOVERED,
    STATISTIC_VISITED_AGAIN
};

class StatisticsGroupBox : public QGroupBox
{
  public:
    StatisticsGroupBox(QString title);
    std::map<StatisticsEnum, QLabel*>& getStatisticValueLabels();
    std::map<StatisticsEnum, QLabel*>& getStatisticLabels();

  private:
    std::map<StatisticsEnum, QLabel*> statisticLabels_;
    std::map<StatisticsEnum, QLabel*> statisticLabelValues_;
};
}   // namespace gui

#endif   // GUI_STATISTICSGROUPBOX_HPP
