cmake_minimum_required(VERSION 3.20)
project(l3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

add_executable(l3 main.cpp menu.cpp menu.h safe_input.cpp safe_input.h multithread_pi.cpp multithread_pi.h)
