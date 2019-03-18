cmake_minimum_required(VERSION 3.13)
project(renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(renderer src/main.cpp src/Vector.cpp src/Vector.h src/Ray.cpp src/Ray.h)