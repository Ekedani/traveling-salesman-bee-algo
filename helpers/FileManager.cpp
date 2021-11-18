#include "FileManager.h"

void FileManager::saveMatrix(int **distanceMatrix, int verticesNum) {
    ofstream file;
    file.open(R"(D:\Programming\traveling-salesman-bee-algo\helpers\DistanceMatrix.txt)");
    file << verticesNum << '\n';
    for (int i = 0; i < verticesNum; ++i) {
        for (int j = 0; j < verticesNum; ++j) {
            file << distanceMatrix[i][j] << ' ';
        }
        file << '\n';
    }
    file.close();
}

pair<int **, int> FileManager::readMatrix() {
    fstream file;
    file.open(R"(D:\Programming\traveling-salesman-bee-algo\helpers\DistanceMatrix.txt)");
    int verticesNum;
    file >> verticesNum;

    auto result = new int*[verticesNum];
    for (int i = 0; i < verticesNum; ++i) {
        result[i] = new int[verticesNum];
    }

    for (int i = 0; i < verticesNum; ++i) {
        for (int j = 0; j < verticesNum; ++j) {
            file >> result[i][j];
        }
    }

    file.close();
    return pair(result, verticesNum);
}
