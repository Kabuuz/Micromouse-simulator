#ifndef APPLICATION_ALGORITHM_FLOODFILLALGORITHM_HPP
#define APPLICATION_ALGORITHM_FLOODFILLALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>

namespace application
{
namespace algorithms
{
    class FloodfillAlgorithm : public Algorithm
    {
      public:
        FloodfillAlgorithm(std::string name, std::string parametersString);
        virtual void runStep() override;
        virtual void reset() override;

      protected:
        std::pair<int, int>
        getNeighbourCoordinates(int startPointX, int startPointY, simulation::Direction direction);
        virtual std::optional<float>
        generateCValue(int currentPointX,
                       int currentPointY,
                       std::vector<simulation::Direction> availableNeighbours,
                       float minimumNeighbourValue);

      private:
        void initializeFinishCells();
        bool mazeFlooded();
        void updateActualCValue(int startPointX,
                                int startPointY,
                                std::vector<simulation::Direction> availableNeighbours);
        float getCurrentCellValue(int currentPointX, int currentPointY);
        std::vector<simulation::Direction> getAvailableNeighbours(int currentPointX,
                                                                  int currentPointY);
        bool neighbourAvailable(int startPointX, int startPointY, simulation::Direction direction);
        std::optional<float>
        getMinimumValueFromNeighbours(int startPointX,
                                      int startPointY,
                                      std::vector<simulation::Direction> availableNeighbours);
        void initializeMazeWithDefaultValues();
        void initializeMazeWithValues();
        simulation::Direction
        chooseMoveDirection(int startPointX,
                            int startPointY,
                            std::vector<simulation::Direction> availableNeighbours);
        void moveInDirection(simulation::Direction direction);
        bool isRightNeighbourCell(int startPointX, int startPointY, int nextPointX, int nextPointY);
        bool isLeftNeighbourCell(int startPointX, int startPointY, int nextPointX, int nextPointY);
        bool isFrontNeighbourCell(int startPointX, int startPointY, int nextPointX, int nextPointY);
        bool isBackNeighbourCell(int startPointX, int startPointY, int nextPointX, int nextPointY);
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_FLOODFILLALGORITHM_HPP
