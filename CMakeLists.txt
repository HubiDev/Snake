cmake_minimum_required(VERSION 3.10)

# CXX config
set(CMAKE_CXX_STANDARD 20)

# set the project name
project(Snake)

# add the executable
add_executable(Snake Snake/main.cpp Snake/Bait.cpp Snake/MenuScreen.cpp Snake/Part.cpp Snake/PointCounter.cpp Snake/Snake.cpp Snake/Trap.cpp)
include_directories(Snake)

# Find SFML

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(Snake sfml-graphics sfml-audio)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Snake/Resources/NotoSans-Regular.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Resources)