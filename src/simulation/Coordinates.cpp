#include <simulation/Coordinates.hpp>

namespace simulation
{
Coordinates::Coordinates() : x_(0), y_(0) {}

Coordinates::Coordinates(int x, int y) : x_(x), y_(y) {}

int& Coordinates::getX()
{
    return x_;
}

int& Coordinates::getY()
{
    return y_;
}

void Coordinates::setX(int x)
{
    x_ = x;
}

void Coordinates::setY(int y)
{
    y_ = y;
}

bool operator==(Coordinates& lhs, Coordinates& rhs)
{
    return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()));
}

}   // namespace simulation
