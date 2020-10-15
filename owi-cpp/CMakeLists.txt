cmake_minimum_required(VERSION 3.14)
project(owi)

set(CMAKE_CXX_STANDARD 20)
set( CMAKE_VERBOSE_MAKEFILE on )

find_library(GDIPLUS_LIBRARY NAMES libgdiplus gdiplus)

add_executable(owi main.cpp)
target_link_libraries(owi rpcrt4.lib)
target_link_libraries(owi gdiplus)