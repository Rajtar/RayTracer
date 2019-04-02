cmake_minimum_required(VERSION 3.13)
project(renderer)

set(CMAKE_CXX_STANDARD 17)

add_executable(renderer src/main.cpp src/geometry/Vector3.cpp src/geometry/Vector3.h src/geometry/Ray.cpp src/geometry/Ray.h src/geometry/Sphere.cpp src/geometry/Sphere.h src/geometry/Plane.cpp src/geometry/Plane.h src/image/bitmap_image.hpp src/image/BitmapImage.cpp src/image/BitmapImage.h src/LightIntensity.cpp src/LightIntensity.h src/image/Image.h src/image/Image.cpp src/camera/Camera.cpp src/camera/Camera.h src/camera/PerspectiveCamera.cpp src/camera/PerspectiveCamera.h src/geometry/Primitive.h src/Scene.cpp src/Scene.h src/static/Settings.hpp)