#ifndef APPLICATION_PAINT_PAINTING_SETTING_HPP
#define APPLICATION_PAINT_PAINTING_SETTING_HPP

namespace application
{
namespace paint
{
    constexpr unsigned int CELL_ROWS = 16;
    constexpr unsigned int CELL_COLUMNS = CELL_ROWS;
    constexpr unsigned int BACKGROUND_COLOR = 0xFFFFFFFF;
    constexpr unsigned int MICROMOUSE_MAZE_COLOR = 0xFFFF0000;
    constexpr unsigned int SIMULATION_MAZE_COLOR = 0xFF808080;
    constexpr unsigned int GRID_COLOR = 0xFFEEEEEE;
    constexpr unsigned int VISITED_CELL_COLOR = 0xFF99CCFF;
    constexpr unsigned int ROBOT_COLOR = 0xFF0000FF;
    constexpr unsigned int ROBOT_FRONT_COLOR = 0xFF00FF00;
    constexpr unsigned int TEXT_COLOR = 0xFF000000;
    constexpr unsigned int CELL_WIDTH = 20;
    constexpr unsigned int CELL_HEIGHT = CELL_WIDTH;
    constexpr float COEFFICIENT = 0.7;
    constexpr unsigned int ROBOT_SIZE = float(CELL_WIDTH) * COEFFICIENT;
    constexpr unsigned int ROBOT_FRONT_WIDTH = float(ROBOT_SIZE) * 0.3;
    constexpr unsigned int WALL_WIDTH = 4;
    constexpr unsigned int PAINTING_AREA_WIDTH
        = CELL_COLUMNS * (CELL_WIDTH + WALL_WIDTH) + WALL_WIDTH;
    constexpr unsigned int PAINTING_AREA_HEIGHT
        = CELL_ROWS * (CELL_HEIGHT + WALL_WIDTH) + WALL_WIDTH;
    constexpr unsigned int FONT_SIZE = 10;

}   // namespace paint
}   // namespace application

#endif   // APPLICATION_PAINT_PAINTING_SETTING_HPP