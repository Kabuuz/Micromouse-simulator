cmake_minimum_required(VERSION 3.5)

project(MicroMouseSimulator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GOOGLETEST_VERSION "1.10.0")

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES MicroMouseSimulator_en_GB.ts)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

add_subdirectory(src)

add_executable(MicroMouseSimulator
    src/main.cpp
    ${TS_FILES}
)
target_include_directories(MicroMouseSimulator PUBLIC ${PROJECT_SOURCE_DIR}/include ${JSONCPP_INCLUDE_DIRS})

target_link_libraries(MicroMouseSimulator PUBLIC ${JSONCPP_LIBRARIES})
target_link_libraries(MicroMouseSimulator PUBLIC applicationlib)
target_link_libraries(MicroMouseSimulator PUBLIC simulationlib)
target_link_libraries(MicroMouseSimulator PUBLIC guilib)

#sudo apt-get install libjsoncpp-dev
#sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json
target_link_libraries(MicroMouseSimulator PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
