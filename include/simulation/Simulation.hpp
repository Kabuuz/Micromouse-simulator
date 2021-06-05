#ifndef SIMULATION_SIMULATION_HPP_
#define SIMULATION_SIMULATION_HPP_

#include <QDebug>
#include <QObject>
#include <QString>
#include <simulation/SimulationState.hpp>
#include <simulation/Statistics.hpp>
#include <simulation/algorithm/IAlgorithm.hpp>
#include <simulation/fwd.hpp>
#include <simulation/maze/MazeWrapper.hpp>
#include <simulation/robot/Micromouse.hpp>

namespace simulation
{
class Simulation : public QObject
{
    Q_OBJECT

  public:
    Simulation();

    void update();
    const SimulationState& getSimulationState() const;
    void setSimulationMaze(MazeWrapper maze);
    MazeWrapper& getSimulationMaze();
    std::shared_ptr<Micromouse> getMicromouse();
    Statistics& getStatistics();
    void setAlgorithm(IAlgorithmPtr algorithm);
    void setSimulationState(SimulationState state);
    void resetSimulation();
    void runStep();

  private:
    IAlgorithmPtr algorithm_;
    MazeWrapper maze_;
    std::shared_ptr<Micromouse> micromouse_;
    SimulationState simulationState_;
    Statistics statistics_;
    QString prefix_;
};

}   // namespace simulation

#endif   // SIMULATION_SIMULATION_HPP_
