#ifndef APPLICATION_ALGORITHM_CENTERRIGHTALGORITHM_HPP
#define APPLICATION_ALGORITHM_CENTERRIGHTALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>

namespace application
{
namespace algorithms
{
    class CenterRightAlgorithm : public Algorithm
    {
      public:
        CenterRightAlgorithm(std::string name,std::string parametersString);
        virtual void runStep() override;

      private:
        bool checkLeftWall();
        bool checkRightWall();
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_CENTERRIGHTALGORITHM_HPP
