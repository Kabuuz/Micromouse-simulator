#ifndef APPLICATION_ALGORITHM_RIGHT_WALL_ALGORITHM_HPP_
#define APPLICATION_ALGORITHM_RIGHT_WALL_ALGORITHM_HPP_

#include <QString>
#include <application/algorithms/Algorithm.hpp>

namespace application
{
namespace algorithms
{
    class RightWallAlgorithm : public Algorithm
    {
      public:
        RightWallAlgorithm(std::string name,std::string parametersString);
        virtual void runStep() override;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_RIGHT_WALL_ALGORITHM_HPP_
