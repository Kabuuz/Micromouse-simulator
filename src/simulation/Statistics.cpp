#include <QDebug>
#include <simulation/Statistics.hpp>

namespace simulation
{
Statistics::Statistics(int x, int y, int distance, int turns, int discoveredCells) :
    prefix_("Statistics")
{
    statisticsMap_[X_COORDINATE_ID] = x;
    statisticsMap_[Y_COORDINATE_ID] = y;
    statisticsMap_[DISTANCE_ID] = distance;
    statisticsMap_[TURNS_ID] = turns;
    statisticsMap_[DISCOVERED_CELLS_ID] = discoveredCells;
}

int Statistics::getStatistic(const StatisticId id)
{
    auto statisticIt = statisticsMap_.find(id);

    if (statisticIt != statisticsMap_.end())
    {
        return statisticIt->second;
    }
    else
    {
        qWarning() << prefix_ << "No statistics with id: " << static_cast<int>(id);
        return 0;
    }
}

void Statistics::reset(int x, int y, int distance, int turns, int discoveredCells)
{
    statisticsMap_[X_COORDINATE_ID] = x;
    statisticsMap_[Y_COORDINATE_ID] = y;
    statisticsMap_[DISTANCE_ID] = distance;
    statisticsMap_[TURNS_ID] = turns;
    statisticsMap_[DISCOVERED_CELLS_ID] = discoveredCells;
}

void Statistics::doOnStatisticChange(Statistic statistic)
{
    auto statisticMapIt = statisticsMap_.find(statistic.id);

    if (statisticMapIt != statisticsMap_.end())
    {
        if (statistic.id == X_COORDINATE_ID || statistic.id == Y_COORDINATE_ID)
        {
            statisticMapIt->second = statistic.newStatisticValue;
        }
        else
        {
            statisticMapIt->second += statistic.changeStatisticByValue;
        }
    }
}

}   // namespace simulation
