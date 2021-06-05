#ifndef APPLICATION_ALGORITHM_LEFTWALLALGORITHM_HPP
#define APPLICATION_ALGORITHM_LEFTWALLALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>

namespace application
{
namespace algorithms
{
    class LeftWallAlgorithm : public Algorithm
    {
      public:
        LeftWallAlgorithm(std::string name, std::string parametersString);
        virtual void runStep() override;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_LEFTWALLALGORITHM_HPP
