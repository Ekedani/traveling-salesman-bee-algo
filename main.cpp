#include "helpers/DistanceMatrixGenerator.h"
#include "helpers/FileManager.h"
#include "algorithm/BeeColonyAlgorithm.h"
#include <iostream>

int main() {
    const int VERTICES_NUM = 300;
    

    char choice;
    cout << "Would you like to generate random distances or input them from the file? (R/F)\n";
    cin >> choice;
    int **distanceMatrix;
    if (choice == 'R' || choice == 'r') {
        distanceMatrix = DistanceMatrixGenerator::generateDistanceMatrix(VERTICES_NUM);
        FileManager::saveMatrix(distanceMatrix, VERTICES_NUM);
    } else {
        distanceMatrix = FileManager::readMatrix().first;
    }
    cout << "You can see your matrix in the DistanceMatrix.txt file\n";

    auto something = BeeColonyAlgorithm(VERTICES_NUM, distanceMatrix);
    something.solve();
    return 0;
}
