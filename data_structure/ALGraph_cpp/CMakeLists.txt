cmake_minimum_required(VERSION 3.7)
project(ALGraph_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ALGraph.cpp
        ALGraph.hpp
        configs.hpp
        main.cpp)

add_executable(ALGraph_cpp ${SOURCE_FILES})