#include "SolutionTSP.h"

void SolutionTSP::generateRandomSolution(int CITIES_NUM, int RANDOM_SEED) {
    srand(RANDOM_SEED);
    for (int i = 0; i < CITIES_NUM; ++i) {
        solution.emplace_back(i);
    }
    for (int i = 0; i < solution.size(); i++) {
        int r = i + rand() % (solution.size() - i);
        swap(solution[i], solution[r]);
    }
}

SolutionTSP SolutionTSP::generateNeighborSolution(int RANDOM_SEED) const {
    auto neighborSolution = SolutionTSP{};
    neighborSolution.solution = solution;
    srand(RANDOM_SEED);
    int changedIndex = rand() % solution.size();
    int neighborIndex = changedIndex == solution.size() - 1 ? 0 : changedIndex + 1;
    swap(neighborSolution.solution[changedIndex], neighborSolution.solution[neighborIndex]);
    return neighborSolution;
}

int SolutionTSP::calculateSolutionWeight(vector<int> &solutionToCalc, int **distanceMatrix) {
    int weight = 0;
    for (int i = 0; i < solutionToCalc.size() - 1; ++i) {
        weight += distanceMatrix[solutionToCalc[i]][solutionToCalc[i + 1]];
    }
    // Get back to the start of the path
    weight += distanceMatrix[solutionToCalc[solutionToCalc.size()]][0];
    return weight;
}

int SolutionTSP::calculateSolutionWeight(int **distanceMatrix) {
    int weight = 0;
    for (int i = 0; i < solution.size() - 1; ++i) {
        weight += distanceMatrix[solution[i]][solution[i + 1]];
    }
    // Get back to the start of the path
    weight += distanceMatrix[solution[solution.size() - 1]][0];
    pathLength = weight;
    return weight;
}

std::ostream &operator<<(ostream &os, const SolutionTSP &tsp) {
    os << "Solution:";
    for (int i = 0; i < tsp.solution.size(); ++i) {
        if (i % 60 == 0) {
            os << '\n';
        }
        os << tsp.solution[i] << " => ";
    }
    os << tsp.solution[0] << '\n';
    return os;
}

void SolutionTSP::greedyAlgorithm(int **distanceMatrix, int CITIES_NUM, int RANDOM_SEED) {
    srand(RANDOM_SEED);
    set<int> visited;
    int start = rand() % CITIES_NUM;
    solution.push_back(start);
    visited.insert(start);
    for (int i = 0; i < CITIES_NUM - 1; ++i) {
        auto curCity = solution[solution.size() - 1];
        auto localBest = INT_MAX;
        auto localBestIndex = INT_MAX;
        for (int j = 0; j < CITIES_NUM; ++j) {
            if (distanceMatrix[curCity][j] == 0) {
                continue;
            }
            if (distanceMatrix[curCity][j] < localBest && !visited.contains(j)) {
                localBest = distanceMatrix[curCity][j];
                localBestIndex = j;
            }
        }
        solution.push_back(localBestIndex);
        visited.insert(localBestIndex);
    }
    this->calculateSolutionWeight(distanceMatrix);
}


