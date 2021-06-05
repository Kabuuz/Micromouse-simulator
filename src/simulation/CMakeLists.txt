cmake_minimum_required(VERSION 3.5)

add_library(simulationlib OBJECT)

target_sources(simulationlib
    PRIVATE
    ${HEADERS_DIR}/simulation/fwd.hpp
    ${HEADERS_DIR}/simulation/Coordinates.hpp
    ${HEADERS_DIR}/simulation/Direction.hpp
    ${HEADERS_DIR}/simulation/Simulation.hpp
    ${HEADERS_DIR}/simulation/SimulationSettings.hpp
    ${HEADERS_DIR}/simulation/SimulationState.hpp
    ${HEADERS_DIR}/simulation/Statistics.hpp

    ${HEADERS_DIR}/simulation/algorithm/IAlgorithm.hpp

    ${HEADERS_DIR}/simulation/maze/Cell.hpp
    ${HEADERS_DIR}/simulation/maze/MazeSettings.hpp
    ${HEADERS_DIR}/simulation/maze/MazeWrapper.hpp
    ${HEADERS_DIR}/simulation/maze/Wall.hpp
    ${HEADERS_DIR}/simulation/maze/WallState.hpp

    ${HEADERS_DIR}/simulation/robot/Micromouse.hpp
    ${HEADERS_DIR}/simulation/robot/Robot.hpp

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Coordinates.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Statistics.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/maze/Cell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/maze/MazeWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/maze/Wall.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/robot/Micromouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/robot/Robot.cpp)

target_include_directories(simulationlib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(simulationlib PRIVATE Qt5::Widgets)
