#include <QDebug>
#include <application/algorithms/CenterRightAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    CenterRightAlgorithm::CenterRightAlgorithm(std::string name, std::string parametersString) :
        Algorithm(name, parametersString)
    {}

    void CenterRightAlgorithm::runStep()
    {
        if (!micromouse_->checkFrontWall())
        {
            micromouse_->moveForward();
        }
        else
        {
            if (!micromouse_->checkRightWall())
            {
                micromouse_->turnRight();
                micromouse_->moveForward();
            }
            else if (!micromouse_->checkLeftWall())
            {
                micromouse_->turnLeft();
                micromouse_->moveForward();
            }
            else
            {
                micromouse_->turnRight();
            }
        }
    }

}   // namespace algorithms
}   // namespace application
