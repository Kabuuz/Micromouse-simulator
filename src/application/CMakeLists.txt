cmake_minimum_required(VERSION 3.5)

add_library(applicationlib)

target_sources(applicationlib
    PRIVATE
    ${HEADERS_DIR}/application/Application.hpp

    ${HEADERS_DIR}/application/algorithms/Algorithm.hpp
    ${HEADERS_DIR}/application/algorithms/AlgorithmParametersConverter.hpp
    ${HEADERS_DIR}/application/algorithms/AlgorithmStateChecker.hpp
    ${HEADERS_DIR}/application/algorithms/AlgorithmsRegistrator.hpp
    ${HEADERS_DIR}/application/algorithms/CenterLeftAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/CenterRightAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/DeadEndExclusionAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/DeadZoneExclusionAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/DepthFirstSearchAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/ETFloodfillAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/FloodfillAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/LeftWallAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/Node.hpp
    ${HEADERS_DIR}/application/algorithms/Partition.hpp
    ${HEADERS_DIR}/application/algorithms/PartitionCentralBaseAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/PartitionCentralModifiedAlgorithm.hpp
    ${HEADERS_DIR}/application/algorithms/RightWallAlgorithm.hpp

    ${HEADERS_DIR}/application/handlers/AlgorithmChangeHandler.hpp
    ${HEADERS_DIR}/application/handlers/IHandler.hpp
    ${HEADERS_DIR}/application/handlers/HandlerRegistrator.hpp
    ${HEADERS_DIR}/application/handlers/MazeChangeHandler.hpp
    ${HEADERS_DIR}/application/handlers/PauseButtonActionHandler.hpp
    ${HEADERS_DIR}/application/handlers/ResetButtonActionHandler.hpp
    ${HEADERS_DIR}/application/handlers/SaveButtonActionHandler.hpp
    ${HEADERS_DIR}/application/handlers/ScanButtonActionHandler.hpp
    ${HEADERS_DIR}/application/handlers/SliderChangeHandler.hpp
    ${HEADERS_DIR}/application/handlers/StartButtonActionHandler.hpp
    ${HEADERS_DIR}/application/handlers/TextEditHandler.hpp
    ${HEADERS_DIR}/application/handlers/TimerActionHandler.hpp

    ${HEADERS_DIR}/application/maze/MazeBuilder.hpp
    ${HEADERS_DIR}/application/maze/MazeFileReader.hpp

    ${HEADERS_DIR}/application/paint/DataPainter.hpp
    ${HEADERS_DIR}/application/paint/GridPainter.hpp
    ${HEADERS_DIR}/application/paint/IPainter.hpp
    ${HEADERS_DIR}/application/paint/MazePainter.hpp
    ${HEADERS_DIR}/application/paint/PaintingWidgetHelper.hpp
    ${HEADERS_DIR}/application/paint/PaintingSettings.hpp
    ${HEADERS_DIR}/application/paint/PathPainter.hpp
    ${HEADERS_DIR}/application/paint/RobotPainter.hpp

    ${HEADERS_DIR}/application/updaters/StatisticLabelUpdater.hpp

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/Algorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/AlgorithmParametersConverter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/AlgorithmStateChecker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/AlgorithmsRegistrator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/CenterLeftAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/CenterRightAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/DeadEndExclusionAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/DeadZoneExclusionAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/DepthFirstSearchAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/ETFloodfillAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/FloodfillAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/LeftWallAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/Node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/PartitionCentralBaseAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/PartitionCentralModifiedAlgorithm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/RightWallAlgorithm.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/AlgorithmChangeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/HandlerRegistrator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/MazeChangeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/PauseButtonActionHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/ResetButtonActionHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/SaveButtonActionHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/ScanButtonActionHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/SliderChangeHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/StartButtonActionHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/TextEditHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/TimerActionHandler.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/maze/MazeBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/maze/MazeFileReader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/paint/DataPainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paint/GridPainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paint/MazePainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paint/PaintingWidgetHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paint/PathPainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/paint/RobotPainter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/updaters/StatisticLabelUpdater.cpp
)

target_include_directories(applicationlib PUBLIC ${PROJECT_SOURCE_DIR}/include ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(applicationlib PRIVATE ${JSONCPP_LIBRARIES})
target_include_directories(applicationlib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(applicationlib PRIVATE Qt5::Widgets)
