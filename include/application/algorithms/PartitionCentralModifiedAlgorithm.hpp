#ifndef APPLICATION_ALGORITHM_PARTITIONCENTRALMODIFIEDALGORITHM_HPP
#define APPLICATION_ALGORITHM_PARTITIONCENTRALMODIFIEDALGORITHM_HPP

#include <QString>
#include <application/algorithms/PartitionCentralBaseAlgorithm.hpp>
#include <simulation/Coordinates.hpp>
#include <simulation/Direction.hpp>

namespace application
{
namespace algorithms
{
    struct Partition;

    class PartitionCentralModifiedAlgorithm : public PartitionCentralBaseAlgorithm
    {
      public:
        PartitionCentralModifiedAlgorithm(std::string name,std::string parametersString);
        virtual void runStep() override;

      private:
        std::pair<simulation::Coordinates, simulation::Direction>
        simulateAlgorithmStep(std::shared_ptr<Algorithm> algorithm);
        bool currentCellIsOnCrossroad();
        simulation::Direction
        getDirectionToNextCell(simulation::Coordinates& firstCellCoordinates,
                               simulation::Coordinates& secondCellCoordinates);
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_PARTITIONCENTRALMODIFIEDALGORITHM_HPP
