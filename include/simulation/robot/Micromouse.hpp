#ifndef SIMULATION_MICROMOUSE_HPP_
#define SIMULATION_MICROMOUSE_HPP_

#include <QString>
#include <simulation/Statistics.hpp>
#include <simulation/fwd.hpp>
#include <simulation/maze/MazeWrapper.hpp>
#include <simulation/maze/WallState.hpp>
#include <simulation/robot/Robot.hpp>

namespace simulation
{
class Micromouse : public Robot
{
    Q_OBJECT

  public:
    Micromouse();
    WallState& checkWallState(Direction direction);
    void setWallState(Direction direction, WallState state);
    bool checkFrontWall();
    bool checkLeftWall();
    bool checkRightWall();
    void updateCurrentCells(Cell& cell);
    void reset();
    MazeWrapper& getMaze();
    VisitedArray& getVisitedArray();
    ValuesArray& getValuesArray();
    void turnLeft();
    void turnRight();
    void moveForward();

  signals:
    void stateChanged(Statistic statistic);

  private:
    void resetMaze();
    void resetPosition();
    void emitSignal(StatisticId id, int value);

    MazeWrapper maze_;
    VisitedArray visitedArray_;
    ValuesArray valuesArray_;
    QString prefix_;
};

}   // namespace simulation

#endif   // SIMULATION_MICROMOUSE_HPP_
