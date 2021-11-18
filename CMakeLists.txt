cmake_minimum_required(VERSION 3.16)
project(traveling_salesman_bee_algo)

set(CMAKE_CXX_STANDARD 20)

add_executable(traveling_salesman_bee_algo main.cpp helpers/DistanceMatrixGenerator.cpp helpers/DistanceMatrixGenerator.h helpers/FileManager.cpp helpers/FileManager.h)