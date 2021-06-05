#include <QDebug>
#include <application/algorithms/CenterLeftAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    CenterLeftAlgorithm::CenterLeftAlgorithm(std::string name, std::string parametersString) :
        Algorithm(name, parametersString)
    {}

    void CenterLeftAlgorithm::runStep()
    {
        if (!micromouse_->checkFrontWall())
        {
            micromouse_->moveForward();
        }
        else
        {
            if (!micromouse_->checkLeftWall())
            {
                micromouse_->turnLeft();
                micromouse_->moveForward();
            }
            else if (!micromouse_->checkRightWall())
            {
                micromouse_->turnRight();
                micromouse_->moveForward();
            }
            else
            {
                micromouse_->turnLeft();
            }
        }
    }

}   // namespace algorithms
}   // namespace application
