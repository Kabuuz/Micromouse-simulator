#ifndef APPLICATION_ALGORITHM_ALGORITHMPARAMETERSCONVERTER_HPP
#define APPLICATION_ALGORITHM_ALGORITHMPARAMETERSCONVERTER_HPP

#include <json/json.h>
#include <map>
#include <string>

namespace application
{
namespace algorithms
{
    class AlgorithmParametersConverter
    {
      public:
        AlgorithmParametersConverter() = delete;
        static Json::Value convertParams(std::string toConvert, std::string defaultParams, bool& correctData);
    };

}   // namespace algorithms
}   // namespace application
#endif   // APPLICATION_ALGORITHM_ALGORITHMPARAMETERSCONVERTER_HPP
