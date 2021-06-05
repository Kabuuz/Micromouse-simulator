#include <QPainter>
#include <application/paint/PaintingSettings.hpp>
#include <application/paint/RobotPainter.hpp>

namespace application
{
namespace paint
{
    RobotPainter::RobotPainter(simulation::Micromouse& micromouse) : micromouse_(micromouse) {}

    void RobotPainter::paint(QPainter* painter)
    {
        painter->setPen(pen_);

        simulation::Coordinates& coordinates = micromouse_.getCoordinates();
        int x = coordinates.getX();
        int y = coordinates.getY();

        int westWallRobotDistance = (CELL_WIDTH + 2 * WALL_WIDTH - ROBOT_SIZE) / 2;
        int northWallRobotDistance = (CELL_HEIGHT + 2 * WALL_WIDTH - ROBOT_SIZE) / 2;

        int xRobot = (x * (WALL_WIDTH + CELL_WIDTH)) + westWallRobotDistance;
        int yRobot = (y * (WALL_WIDTH + CELL_HEIGHT)) + northWallRobotDistance;

        painter->fillRect(QRect(xRobot, yRobot, ROBOT_SIZE, ROBOT_SIZE), bodyColorGradient_);

        // robot front
        simulation::Direction direction = micromouse_.getDirection();

        int frontWidth;
        int frontHeight;

        if (direction == simulation::Direction::North || direction == simulation::Direction::South)
        {
            frontWidth = ROBOT_SIZE;
            frontHeight = ROBOT_FRONT_WIDTH;
        }
        else
        {
            frontWidth = ROBOT_FRONT_WIDTH;
            frontHeight = ROBOT_SIZE;
        }

        int xRobotFront;
        int yRobotFront;

        if (direction == simulation::Direction::North || direction == simulation::Direction::West)
        {
            xRobotFront = xRobot;
            yRobotFront = yRobot;
        }
        else if (direction == simulation::Direction::East)
        {
            xRobotFront = xRobot + ROBOT_SIZE - frontWidth;
            yRobotFront = yRobot;
        }
        else if (direction == simulation::Direction::South)
        {
            xRobotFront = xRobot;
            yRobotFront = yRobot + ROBOT_SIZE - frontHeight;
        }

        painter->fillRect(QRect(xRobotFront, yRobotFront, frontWidth, frontHeight),
                          frontColorGradient_);
    }

    void RobotPainter::setColor(unsigned int color)
    {
        pen_.setColor(color);

        bodyColorGradient_ = QLinearGradient(0, 0, 0, 100);
        bodyColorGradient_.setColorAt(0.0, color);
        bodyColorGradient_.setColorAt(1.0, color);

        unsigned int frontColor = 0xFF000000 | ((color & 0x00FFFFFF) << 8);

        frontColorGradient_ = QLinearGradient(0, 0, 0, 100);
        frontColorGradient_.setColorAt(0.0, frontColor);
        frontColorGradient_.setColorAt(1.0, frontColor);
    }

    void RobotPainter::setWidth(unsigned int width)
    {
        pen_.setWidth(width);
    }

}   // namespace paint
}   // namespace application
