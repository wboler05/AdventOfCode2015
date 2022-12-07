cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2015)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(part1 part1.cpp)
#add_executable(part1 part1.cpp day5.cpp)
#add_executable(part2 part2.cpp day5.cpp)