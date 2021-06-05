#ifndef SIMULATION_STATISTICS_HPP
#define SIMULATION_STATISTICS_HPP

#include <QObject>
#include <QString>
#include <map>
#include <simulation/Coordinates.hpp>

namespace simulation
{
enum StatisticId
{
    X_COORDINATE_ID = 1,
    Y_COORDINATE_ID,
    DISTANCE_ID,
    TURNS_ID,
    DISCOVERED_CELLS_ID
};

struct Statistic
{
    StatisticId id;

    union
    {
        int newStatisticValue;
        int changeStatisticByValue;
    };
};

class Statistics : public QObject
{
    Q_OBJECT
  public:
    Statistics(int x = 0, int y = 0, int distance = 0, int turns = 0, int discoveredCells = 0);
    int getStatistic(StatisticId id);
    void reset(int x = 0, int y = 0, int distance = 0, int turns = 0, int discoveredCells = 0);

  public slots:
    void doOnStatisticChange(Statistic statistic);

  private:
    std::map<StatisticId, int> statisticsMap_;
    QString prefix_;
};

}   // namespace simulation

#endif   // SIMULATION_STATISTICS_HPP
