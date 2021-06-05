#include <QDebug>
#include <application/algorithms/CenterLeftAlgorithm.hpp>
#include <application/algorithms/CenterRightAlgorithm.hpp>
#include <application/algorithms/LeftWallAlgorithm.hpp>
#include <application/algorithms/PartitionCentralModifiedAlgorithm.hpp>
#include <application/algorithms/RightWallAlgorithm.hpp>
#include <map>
#include <vector>

namespace application
{
namespace algorithms
{
    PartitionCentralModifiedAlgorithm::PartitionCentralModifiedAlgorithm(
        std::string name, std::string parametersString) :
        PartitionCentralBaseAlgorithm(name, parametersString)
    {}

    void PartitionCentralModifiedAlgorithm::runStep()
    {
        auto PartitionIt = getCurrentPartition(micromouse_->getCoordinates());

        if (PartitionIt == partitions_.end())
        {
            qCritical() << QString::fromStdString(name_) << "No partition found";
        }
        else
        {
            std::shared_ptr<Algorithm> algorithm
                = getAlgorithm(*PartitionIt, micromouse_->getDirection());

            if (algorithm != nullptr)
            {
                auto [newCoordinates, newDirection] = simulateAlgorithmStep(algorithm);

                simulation::Direction directionOfVirtualWall;
                simulation::Coordinates savedCoordinates;

                if (micromouse_->getVisitedArray()
                            .at(newCoordinates.getY())
                            .at(newCoordinates.getX())
                        == true
                    && currentCellIsOnCrossroad())
                {
                    directionOfVirtualWall
                        = getDirectionToNextCell(micromouse_->getCoordinates(), newCoordinates);

                    micromouse_->getMaze().getCell(micromouse_->getCoordinates()).setWallState(
                                                        directionOfVirtualWall,
                                                        simulation::WallState::Present);

                    savedCoordinates = micromouse_->getCoordinates();

                    algorithm->runStep();
                }
                else
                {
                    algorithm->runStep();
                }
            }
            else
            {
                qCritical() << QString::fromStdString(name_) << "No algorithm found";
            }
        }
    }

    // return coordinates and direction after algorithm simulation
    std::pair<simulation::Coordinates, simulation::Direction>
    PartitionCentralModifiedAlgorithm::simulateAlgorithmStep(std::shared_ptr<Algorithm> algorithm)
    {
        // block signals from micromouse
        bool oldState = micromouse_->blockSignals(true);

        // save current state
        simulation::Coordinates savedCoordinates = micromouse_->getCoordinates();
        simulation::Direction savedDirection = micromouse_->getDirection();

        // run algorithm
        algorithm->runStep();

        // save new state
        simulation::Coordinates newCoordinates = micromouse_->getCoordinates();
        simulation::Direction newDirection = micromouse_->getDirection();

        // restore saved state
        micromouse_->setCoordinates(savedCoordinates);
        micromouse_->setDirection(savedDirection);

        // enable signal emitting
        micromouse_->blockSignals(oldState);

        return {newCoordinates, newDirection};
    }

    bool PartitionCentralModifiedAlgorithm::currentCellIsOnCrossroad()
    {
        int availableNeighbourCells = 0;
        if (!micromouse_->checkFrontWall())
        {
            availableNeighbourCells++;
        }
        if (!micromouse_->checkLeftWall())
        {
            availableNeighbourCells++;
        }

        if (!micromouse_->checkRightWall())
        {
            availableNeighbourCells++;
        }

        return availableNeighbourCells >= 2;
    }

    simulation::Direction PartitionCentralModifiedAlgorithm::getDirectionToNextCell(
        simulation::Coordinates& firstCellCoordinates,
        simulation::Coordinates& secondCellCoordinates)
    {
        int x1 = firstCellCoordinates.getX();
        int y1 = firstCellCoordinates.getY();
        int x2 = secondCellCoordinates.getX();
        int y2 = secondCellCoordinates.getY();

        simulation::Direction direction;

        if (x1 < x2)
        {
            direction = simulation::Direction::East;
        }
        else if (x1 > x2)
        {
            direction = simulation::Direction::West;
        }
        else if (y1 < y2)
        {
            direction = simulation::Direction::South;
        }
        else if (y1 > y2)
        {
            direction = simulation::Direction::North;
        }

        return direction;
    }

}   // namespace algorithms
}   // namespace application
