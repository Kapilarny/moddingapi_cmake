cmake_minimum_required(VERSION 3.28)
project(moddingapi_cmake)

set(CMAKE_CXX_STANDARD 11)

add_library(moddingapi_cmake SHARED src/plugin.cpp)
