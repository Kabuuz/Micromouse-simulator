#ifndef APPLICATION_ALGORITHM_ETFLOODFILLALGORITHM_HPP
#define APPLICATION_ALGORITHM_ETFLOODFILLALGORITHM_HPP

#include <QString>
#include <application/algorithms/FloodfillAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    class ETFloodfillAlgorithm : public FloodfillAlgorithm
    {
      public:
        ETFloodfillAlgorithm(std::string name, std::string parametersString);

      protected:
        virtual std::optional<float>
        generateCValue(int currentPointX,
                       int currentPointY,
                       std::vector<simulation::Direction> availableNeighbours,
                       float minimumNeighbourValue) override;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_ETFLOODFILLALGORITHM_HPP
