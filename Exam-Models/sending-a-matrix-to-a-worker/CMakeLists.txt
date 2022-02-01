cmake_minimum_required(VERSION 3.21)
project(23_January_2021_MPI_Matrix_Sum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
include_directories(/usr/lib/x86_64-linux-gnu/openmpi/include)

add_executable(23_January_2021_MPI_Matrix_Sum main.cpp)
