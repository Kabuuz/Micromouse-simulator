#ifndef APPLICATION_ALGORITHMS_ALGORITHMSTATECHECKER_HPP
#define APPLICATION_ALGORITHMS_ALGORITHMSTATECHECKER_HPP

#include <simulation/robot/Micromouse.hpp>

namespace application
{
namespace algorithms
{
    class AlgorithmStateChecker
    {
      public:
        AlgorithmStateChecker();
        bool isAlgorithmFinished(simulation::Micromouse& micromouse);
    };

}   // namespace algorithms
}   // namespace application
#endif   // APPLICATION_ALGORITHMS_ALGORITHMSTATECHECKER_HPP
