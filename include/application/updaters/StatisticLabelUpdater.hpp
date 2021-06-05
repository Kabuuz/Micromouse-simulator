#ifndef APPLICATION_STATISTICLABELUPDATER_HPP
#define APPLICATION_STATISTICLABELUPDATER_HPP

#include <gui/StatisticsGroupBox.hpp>
#include <simulation/Statistics.hpp>
#include <QLabel>

namespace application
{
namespace updaters
{

class StatisticLabelUpdater
{
public:
    static void update(simulation::Statistics& statistics, std::map<gui::StatisticsEnum, QLabel*>& labels);

private:
    StatisticLabelUpdater() = default;
};

}
}

#endif // APPLICATION_STATISTICLABELUPDATER_HPP
