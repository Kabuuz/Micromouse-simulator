#ifndef APPLICATION_ALGORITHM_DEADENDEXCLUSIONALGORITHM_HPP
#define APPLICATION_ALGORITHM_DEADENDEXCLUSIONALGORITHM_HPP

#include <application/algorithms/DepthFirstSearchAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    class DeadEndExclusionAlgorithm : public DepthFirstSearchAlgorithm
    {
      public:
        DeadEndExclusionAlgorithm(std::string name, std::string parametersString);
        virtual void runStep() override;
        virtual void reset() override;

      private:
        void calculateWalls();
        void closeDeadEnds();
        void move();
        int calculateWallsInCell(int positionX, int positionY);
        void closeCell(int positionX, int positionY);
        void setNeighbourWallPresent(int positionY, int positionX, simulation::Direction direction);
        std::pair<int, int>
        getNeighbourCoordinates(int startPointX, int startPointY, simulation::Direction direction);
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_DEADENDEXCLUSIONALGORITHM_HPP
