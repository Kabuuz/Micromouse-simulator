#ifndef APPLICATION_ALGORITHM_DEADZONEEXCLUSIONALGORITHM_HPP
#define APPLICATION_ALGORITHM_DEADZONEEXCLUSIONALGORITHM_HPP

#include <application/algorithms/DepthFirstSearchAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    class DeadZoneExclusionAlgorithm : public DepthFirstSearchAlgorithm
    {
      public:
        DeadZoneExclusionAlgorithm(std::string name, std::string parametersString);
        virtual void runStep() override;
        virtual void reset() override;

      private:
        void move();
        void resetValues();
        bool inCrossroad();
        std::vector<simulation::Direction> getAvailableNeighbours(int positionX, int positionY);
        bool neighbourAvailable(int positionX, int positionY, simulation::Direction direction);
        std::pair<int, int>
        getNeighbourPosition(int positionX, int positionY, simulation::Direction direction);
        void startflooding(int x, int y, std::vector<std::pair<int, int>>& floodedCells);
        bool isFinishPointsInVector(std::vector<std::pair<int, int>>& floodedCells);
        void putWallInDirection(int positionX, int positionY, simulation::Direction direction);
        void setNeighbourWallPresent(int positionY, int positionX, simulation::Direction direction);
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_DEADZONEEXCLUSIONALGORITHM_HPP
