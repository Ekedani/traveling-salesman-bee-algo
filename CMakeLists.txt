cmake_minimum_required(VERSION 3.16)
project(traveling_salesman_bee_algo)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(algorithm)
include_directories(helpers)

add_executable(traveling_salesman_bee_algo
        algorithm/BeeColonyAlgorithm.cpp
        algorithm/BeeColonyAlgorithm.h
        algorithm/SolutionTSP.cpp
        algorithm/SolutionTSP.h
        helpers/DistanceMatrix.txt
        helpers/DistanceMatrixGenerator.cpp
        helpers/DistanceMatrixGenerator.h
        helpers/FileManager.cpp
        helpers/FileManager.h
        helpers/LastRunStats.csv
        main.cpp)
