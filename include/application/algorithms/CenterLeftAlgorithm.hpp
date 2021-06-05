#ifndef APPLICATION_ALGORITHM_CENTERLEFTALGORITHM_HPP
#define APPLICATION_ALGORITHM_CENTERLEFTALGORITHM_HPP

#include <QString>
#include <application/algorithms/Algorithm.hpp>

namespace application
{
namespace algorithms
{
    class CenterLeftAlgorithm : public Algorithm
    {
      public:
        CenterLeftAlgorithm(std::string name,std::string parametersString);
        virtual void runStep() override;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_CENTERLEFTALGORITHM_HPP
