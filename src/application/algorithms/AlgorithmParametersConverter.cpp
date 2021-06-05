#include <QDebug>
#include <application/algorithms/AlgorithmParametersConverter.hpp>

namespace application
{
namespace algorithms
{
    Json::Value AlgorithmParametersConverter::convertParams(std::string toConvert,
                                                            std::string defaultParams,
                                                            bool& correctData)
    {
        Json::Value json;
        Json::Reader reader;

        correctData = reader.parse(toConvert, json);

        if (!correctData)
        {
            qDebug() << "Invalid algorithm params string";
            reader.parse(defaultParams, json);
        }

        return json;
    }

}   // namespace algorithms
}   // namespace application
