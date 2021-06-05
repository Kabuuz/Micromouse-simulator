#ifndef APPLICATION_ALGORITHM_PARTITIONCENTRALBASEALGORITHM_HPP
#define APPLICATION_ALGORITHM_PARTITIONCENTRALBASEALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>
#include <application/algorithms/Partition.hpp>
#include <application/algorithms/CenterLeftAlgorithm.hpp>
#include <application/algorithms/CenterRightAlgorithm.hpp>
#include <application/algorithms/LeftWallAlgorithm.hpp>
#include <application/algorithms/RightWallAlgorithm.hpp>
#include <simulation/Coordinates.hpp>
#include <simulation/Direction.hpp>

namespace application
{
namespace algorithms
{
    class PartitionCentralBaseAlgorithm : public Algorithm
    {
      public:
        PartitionCentralBaseAlgorithm(std::string name,std::string parametersString);
        virtual void runStep() override;
        virtual void setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse) override;

      protected:
        std::vector<Partition>::iterator getCurrentPartition(simulation::Coordinates& coordinate);
        std::shared_ptr<Algorithm> getAlgorithm(Partition& partition,
                                                simulation::Direction& direction);

        std::shared_ptr<CenterLeftAlgorithm> centerLeftAlgorithmPtr_;
        std::shared_ptr<CenterRightAlgorithm> centerRightAlgorithmPtr_;
        std::shared_ptr<LeftWallAlgorithm> leftWallAlgorithmPtr_;
        std::shared_ptr<RightWallAlgorithm> rightWallAlgorithmPtr_;
        std::vector<Partition> partitions_;

      private:
        std::vector<Partition> createPartitions();
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_PARTITIONCENTRALBASEALGORITHM_HPP
