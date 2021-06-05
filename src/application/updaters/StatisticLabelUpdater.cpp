#include <application/updaters/StatisticLabelUpdater.hpp>

namespace application
{
namespace updaters
{
    void StatisticLabelUpdater::update(simulation::Statistics& statistics,
                                       std::map<gui::StatisticsEnum, QLabel*>& labels)
    {
        // statistics from simulation
        using guiStat = gui::StatisticsEnum;
        using simStat = simulation::StatisticId;

        std::vector<std::pair<guiStat, simStat>> statisticsPairs {
            {guiStat::STATISTIC_X, simStat::X_COORDINATE_ID},
            {guiStat::STATISTIC_Y, simStat::Y_COORDINATE_ID},
            {guiStat::STATISTIC_TURNS, simStat::TURNS_ID},
            {guiStat::STATISTIC_DISTANCE, simStat::DISTANCE_ID},
            {guiStat::STATISTIC_DISCOVERED, simStat::DISCOVERED_CELLS_ID},
        };

        for (const auto& [guiLabelEnum, simValEnum] : statisticsPairs)
        {
            labels.at(guiLabelEnum)->setText(QString::number(statistics.getStatistic(simValEnum)));
        }

        // statistics calculated basing on simulations statistics
        int visitedAgain = statistics.getStatistic(simStat::DISTANCE_ID)
            - statistics.getStatistic(simStat::DISCOVERED_CELLS_ID);
        visitedAgain = (visitedAgain < 0) ? 0 : visitedAgain;
        labels.at(guiStat::STATISTIC_VISITED_AGAIN)->setText(QString::number(visitedAgain));
    }
}   // namespace updaters
}   // namespace application
