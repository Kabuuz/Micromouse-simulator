#include <simulation/Simulation.hpp>

namespace simulation
{
Simulation::Simulation() :
    maze_(),
    micromouse_(std::make_shared<Micromouse>()),
    simulationState_(SimulationState::Reseted),
    statistics_(micromouse_->getCoordinates().getX(), micromouse_->getCoordinates().getY()),
    prefix_("Simulation")
{
    connect(micromouse_.get(),
            &Micromouse::stateChanged,
            &statistics_,
            &Statistics::doOnStatisticChange);
}

void Simulation::update()
{
    micromouse_->updateCurrentCells(maze_.getCell(micromouse_->getCoordinates()));
}

void Simulation::runStep()
{
    if (simulationState_ == SimulationState::Running)
    {
        algorithm_->runStep();
    }
}

void Simulation::resetSimulation()
{
    simulationState_ = SimulationState::Reseted;
    micromouse_->reset();
    statistics_.reset(micromouse_->getCoordinates().getX(), micromouse_->getCoordinates().getY());
}

void Simulation::setSimulationState(SimulationState state)
{
    simulationState_ = state;
}

const SimulationState& Simulation::getSimulationState() const
{
    return simulationState_;
}

void Simulation::setSimulationMaze(MazeWrapper maze)
{
    maze_ = maze;
}

MazeWrapper& Simulation::getSimulationMaze()
{
    return maze_;
}

std::shared_ptr<Micromouse> Simulation::getMicromouse()
{
    return micromouse_;
}

Statistics& Simulation::getStatistics()
{
    return statistics_;
}

void Simulation::setAlgorithm(IAlgorithmPtr algorithm)
{
    algorithm_ = algorithm;
}

}   // namespace simulation
