#ifndef APPLICATION_ALGORITHM_ALGORITHM_HPP
#define APPLICATION_ALGORITHM_ALGORITHM_HPP

#include <json/json.h>
#include <simulation/algorithm/IAlgorithm.hpp>
#include <simulation/maze/MazeWrapper.hpp>
#include <simulation/robot/Micromouse.hpp>

namespace application
{
namespace algorithms
{
    class Algorithm : public simulation::IAlgorithm
    {
      public:
        Algorithm(std::string name, std::string parametersString = "{}");
        virtual ~Algorithm() = default;
        virtual void runStep() override;
        virtual void reset() override;
        virtual void setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse);
        std::string& getName();
        void setParameters(Json::Value parameters);
        std::string getDefaultParamsString();

      protected:
        std::string name_;
        std::shared_ptr<simulation::Micromouse> micromouse_;
        Json::Value parameters_;
        std::string parametersString_;
    };
}   // namespace algorithms
}   // namespace application

#endif   // APPLICATION_ALGORITHM_ALGORITHM_HPP
