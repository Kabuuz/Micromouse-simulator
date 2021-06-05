#ifndef SIMULATION_ROBOT_HPP_
#define SIMULATION_ROBOT_HPP_

#include <QObject>
#include <QString>
#include <simulation/Coordinates.hpp>
#include <simulation/Direction.hpp>

namespace simulation
{
class Robot : public QObject
{
    Q_OBJECT

  public:
    Robot();
    Robot(Coordinates coordinates, Direction direction);

    Coordinates& getCoordinates();
    void setCoordinates(Coordinates coordinates);
    Direction& getDirection();
    void setDirection(Direction direction);
    void turnLeft();
    void turnRight();
    void moveForward();

  signals:
    void signalOnTurningRight(const std::string& text);
    void signalOnTurningLeft(const std::string& text);
    void signalOnMovingForward(const std::string& text);

  private:
    Coordinates coordinates_;
    Direction direction_;
    QString prefix_;
};

}   // namespace simulation

#endif   // SIMULATION_ROBOT_HPP_
