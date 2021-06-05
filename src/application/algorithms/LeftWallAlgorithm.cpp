#include <QDebug>
#include <application/algorithms/LeftWallAlgorithm.hpp>

namespace application
{
namespace algorithms
{
    LeftWallAlgorithm::LeftWallAlgorithm(std::string name,std::string parametersString) :
        Algorithm(name,parametersString)
    {}

    void LeftWallAlgorithm::runStep()
    {
        if (micromouse_->checkLeftWall())
        {
            if (micromouse_->checkFrontWall())
            {
                micromouse_->turnRight();
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
            micromouse_->turnLeft();
            micromouse_->moveForward();
        }
    }

}   // namespace algorithms
}   // namespace application
