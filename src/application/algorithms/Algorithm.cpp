#include <QDebug>
#include <application/algorithms/Algorithm.hpp>
#include <vector>

namespace application
{
namespace algorithms
{
    Algorithm::Algorithm(std::string name, std::string parametersString) :
        name_(name), parametersString_(parametersString)
    {}

    void Algorithm::runStep()
    {
        qDebug() << "Run Step in default algorithm";
    }

    void Algorithm::reset()
    {
        qDebug() << "Reset in default algorithm";
    }

    void Algorithm::setMicromouse(std::shared_ptr<simulation::Micromouse> micromouse)
    {
        micromouse_ = micromouse;
    }

    std::string& Algorithm::getName()
    {
        return name_;
    }

    void Algorithm::setParameters(Json::Value parameters)
    {
        parameters_ = parameters;
    }

    std::string Algorithm::getDefaultParamsString()
    {
        return parametersString_;
    }

}   // namespace algorithms
}   // namespace application
