#include "helpers/DistanceMatrixGenerator.h"
#include "helpers/FileManager.h"
#include "algorithm/BeeColonyAlgorithm.h"
#include <iostream>

int main() {
    const int CITIES_NUM = 300;
    const int BEES_NUM = 200;
    const float SCOUT_PERCENT = 0.1;
    const int SOLUTIONS_NUM = 300;
    const int ITERATIONS_NUM = 250;

    char choice;
    cout << "Would you like to generate random distances or input them from the file? (R/F)\n";
    cin >> choice;
    int **distanceMatrix;
    if (choice == 'R' || choice == 'r') {
        distanceMatrix = DistanceMatrixGenerator::generateDistanceMatrix(CITIES_NUM);
        FileManager::saveMatrix(distanceMatrix, CITIES_NUM);
    } else {
        distanceMatrix = FileManager::readMatrix().first;
    }
    cout << "You can see your matrix in the DistanceMatrix.txt file\n";

    auto something = BeeColonyAlgorithm(distanceMatrix, CITIES_NUM, BEES_NUM, SCOUT_PERCENT, SOLUTIONS_NUM,
                                        ITERATIONS_NUM);
    something.solve();
    return 0;
}
