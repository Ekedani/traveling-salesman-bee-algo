#include "DistanceMatrixGenerator.h"

int **DistanceMatrixGenerator::generateDistanceMatrix(const int VERTICES_NUM) {
    auto distanceMatrix = new int *[VERTICES_NUM];
    for (int i = 0; i < VERTICES_NUM; ++i) {
        distanceMatrix[i] = new int[VERTICES_NUM]{};
    }
    // Filling matrix
    srand(time(nullptr));
    for (int i = 0; i < VERTICES_NUM; ++i) {
        for (int j = i + 1; j < VERTICES_NUM; ++j) {
            distanceMatrix[i][j] = LOWER_BOUND + rand() % (HIGHER_BOUND - LOWER_BOUND + 1);
            // Symmetrical network
            distanceMatrix[j][i] = distanceMatrix[i][j];
        }
    }
    return distanceMatrix;
}
