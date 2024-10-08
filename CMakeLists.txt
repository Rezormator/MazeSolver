cmake_minimum_required(VERSION 3.28)
project(MazeBFS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,8388608")

add_executable(MazeBFS main.cpp
        Maze.h
        Maze.cpp
        Point.h
        Node.h
        Node.cpp
        Algorithms.h
        Algorithms.cpp
        AStarNode.h
        AStarNode.cpp
        Input.cpp
        Input.cpp)
