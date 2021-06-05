#ifndef APPLICATION_ALGORITHMS_ALGORITHMSREGISTRATOR_HPP
#define APPLICATION_ALGORITHMS_ALGORITHMSREGISTRATOR_HPP

#include <application/algorithms/Algorithm.hpp>
#include <simulation/robot/Micromouse.hpp>

namespace application
{
namespace algorithms
{
    class AlgorithmsRegistrator
    {
      public:
        AlgorithmsRegistrator(std::shared_ptr<simulation::Micromouse> micromouse);
        void registerAlgorithms();
        std::shared_ptr<Algorithm> getAlgorithm(std::string name);
        std::vector<std::string> getNamesOfRegisteredAlgorithms();

      private:
        void setupRegisteredAlgorithms();

        std::vector<std::shared_ptr<Algorithm>> algorithms_;
        std::shared_ptr<simulation::Micromouse> micromouse_;
    };

}   // namespace algorithms
}   // namespace application
#endif   // APPLICATION_ALGORITHMS_ALGORITHMSREGISTRATOR_HPP
