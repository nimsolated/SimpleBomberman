cmake_minimum_required(VERSION 3.31)
project(Bomberman)

set(CMAKE_CXX_STANDARD 23)

add_executable(Bomberman src/main.cpp
        include/Maze.h
        src/Maze.cpp)
