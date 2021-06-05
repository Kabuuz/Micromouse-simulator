#include <application/algorithms/AlgorithmsRegistrator.hpp>
#include <application/algorithms/CenterLeftAlgorithm.hpp>
#include <application/algorithms/CenterRightAlgorithm.hpp>
#include <application/algorithms/DeadEndExclusionAlgorithm.hpp>
#include <application/algorithms/DeadZoneExclusionAlgorithm.hpp>
#include <application/algorithms/DepthFirstSearchAlgorithm.hpp>
#include <application/algorithms/ETFloodfillAlgorithm.hpp>
#include <application/algorithms/FloodfillAlgorithm.hpp>
#include <application/algorithms/LeftWallAlgorithm.hpp>
#include <application/algorithms/PartitionCentralBaseAlgorithm.hpp>
#include <application/algorithms/PartitionCentralModifiedAlgorithm.hpp>
#include <application/algorithms/RightWallAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    AlgorithmsRegistrator::AlgorithmsRegistrator(
        std::shared_ptr<simulation::Micromouse> micromouse) :
        micromouse_(micromouse)
    {}

    void AlgorithmsRegistrator::registerAlgorithms()
    {
        algorithms_.push_back(std::make_shared<CenterLeftAlgorithm>("CenterLeftAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<CenterRightAlgorithm>("CenterRightAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<DeadEndExclusionAlgorithm>("DeadEndExclusionAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<DeadZoneExclusionAlgorithm>("DeadZoneExclusionAlgorithm", "{}"));
        algorithms_.push_back(
            std::make_shared<DepthFirstSearchAlgorithm>("DepthFirstSearchAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<FloodfillAlgorithm>("FloodfillAlgorithm", "{}"));
        algorithms_.push_back(
            std::make_shared<ETFloodfillAlgorithm>("ETFloodfillAlgorithm", R"({"T": 3.5})"));
        algorithms_.push_back(std::make_shared<LeftWallAlgorithm>("LeftWallAlgorithm", "{}"));
        algorithms_.push_back(
            std::make_shared<PartitionCentralBaseAlgorithm>("PartitionCentralBaseAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<PartitionCentralModifiedAlgorithm>(
            "PartitionCentralModifiedAlgorithm", "{}"));
        algorithms_.push_back(std::make_shared<RightWallAlgorithm>("RightWallAlgorithm", "{}"));

        setupRegisteredAlgorithms();
    }

    std::shared_ptr<Algorithm> AlgorithmsRegistrator::getAlgorithm(std::string name)
    {
        auto algorithmIter
            = std::find_if(algorithms_.begin(), algorithms_.end(), [&name](auto& algorithm) {
                  return name == algorithm->getName();
              });

        if (algorithmIter != algorithms_.end())
        {
            return *algorithmIter;
        }
        else
        {
            return std::make_shared<Algorithm>("DefaultAlgorithm");
        }
    }

    std::vector<std::string> AlgorithmsRegistrator::getNamesOfRegisteredAlgorithms()
    {
        std::vector<std::string> names;

        for (auto& algorithm : algorithms_)
        {
            names.push_back(algorithm->getName());
        }

        return names;
    }

    void AlgorithmsRegistrator::setupRegisteredAlgorithms()
    {
        for (auto& algorithm : algorithms_)
        {
            algorithm->setMicromouse(micromouse_);
        }
    }

}   // namespace algorithms
}   // namespace application
