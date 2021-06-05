#include <QDebug>
#include <application/algorithms/RightWallAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    RightWallAlgorithm::RightWallAlgorithm(std::string name, std::string parametersString) :
        Algorithm(name, parametersString)
    {}

    void RightWallAlgorithm::runStep()
    {
        if (micromouse_->checkRightWall())
        {
            if (micromouse_->checkFrontWall())
            {
                micromouse_->turnLeft();
                if (!micromouse_->checkFrontWall())
                {
                    micromouse_->moveForward();
                }
            }
            else
            {
                micromouse_->moveForward();
            }
        }
        else
        {
            micromouse_->turnRight();
            micromouse_->moveForward();
        }
    }

}   // namespace algorithms
}   // namespace application
