cmake_minimum_required(VERSION 3.5)

add_library(guilib)

target_sources(guilib
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include/gui/ControlGroupBox.hpp
    ${PROJECT_SOURCE_DIR}/include/gui/InformationGroupBox.hpp
    ${PROJECT_SOURCE_DIR}/include/gui/IPaintingWidgetHelper.hpp
    ${PROJECT_SOURCE_DIR}/include/gui/mainwindow.h
    ${PROJECT_SOURCE_DIR}/include/gui/PaintingWidget.hpp
    ${PROJECT_SOURCE_DIR}/include/gui/SettingsGroupBox.hpp
    ${PROJECT_SOURCE_DIR}/include/gui/StatisticsGroupBox.hpp

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlGroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InformationGroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/PaintingWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsGroupBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StatisticsGroupBox.cpp
)

target_include_directories(guilib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(guilib PRIVATE Qt5::Widgets)
