#include "helpers/DistanceMatrixGenerator.h"
#include "helpers/FileManager.h"

int main() {
    auto test = DistanceMatrixGenerator::generateDistanceMatrix(300);
    FileManager::saveMatrix(test, 300);
    test = FileManager::readMatrix().first;
    return 0;
}
