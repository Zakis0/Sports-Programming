cmake_minimum_required(VERSION 3.27)
project(Template)

set(CMAKE_CXX_STANDARD 20)

add_executable(Template main.cpp
        DebugFunctions.cpp
        DebugFunctions.h)
