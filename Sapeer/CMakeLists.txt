cmake_minimum_required(VERSION 3.10)

project(p VERSION 1.0
        DESCRIPTION "Involve class.hpp"
        LANGUAGES CXX)

set(SOURCE
    code/main.cpp
    code/gameTile.cpp
    code/gameWorld.cpp)
#file(GLOB SOURCES "src/*.cpp")


add_executable(${PROJECT_NAME} ${SOURCE})


target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)