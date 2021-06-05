#ifndef SIMULATION_COORDINATES_HPP_
#define SIMULATION_COORDINATES_HPP_

#include <string>

namespace simulation
{
class Coordinates
{
  public:
    Coordinates();
    Coordinates(int x, int y);

    int& getX();
    int& getY();
    void setX(int x);
    void setY(int y);

    friend bool operator==(Coordinates& lhs, Coordinates& rhs);

  private:
    int x_;
    int y_;
};

inline std::string to_string(Coordinates& coordinates)
{
    std::string text
        = "x: " + std::to_string(coordinates.getX()) + ", y: " + std::to_string(coordinates.getY());

    return text;
}

}   // namespace simulation

#endif   // SIMULATION_COORDINATES_HPP_
