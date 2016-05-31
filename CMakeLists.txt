cmake_minimum_required(VERSION 3.3)
project(Village)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp classes/Map.cpp classes/Map.h classes/Elevation.cpp classes/Point.cpp classes/Point.h)
add_executable(Village ${SOURCE_FILES})