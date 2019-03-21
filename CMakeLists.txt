cmake_minimum_required(VERSION 3.13)
project(renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(renderer src/main.cpp src/Vector3.cpp src/Vector3.h src/Ray.cpp src/Ray.h src/Sphere.cpp src/Sphere.h src/Plane.cpp src/Plane.h)