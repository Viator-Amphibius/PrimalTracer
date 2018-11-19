cmake_minimum_required(VERSION 3.12)
project(Graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(Graphics main.cpp Vec3.h Vec3.cpp Color.cpp Color.h Camera.cpp Camera.h GeometricObject.cpp GeometricObject.h Ray.cpp Ray.h Sphere.cpp Sphere.h Triangle.cpp Triangle.h Matrix3.cpp Matrix3.h)