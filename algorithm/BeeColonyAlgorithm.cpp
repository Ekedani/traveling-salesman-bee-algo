#include "BeeColonyAlgorithm.h"

void BeeColonyAlgorithm::generateSolutionsList() {
    for (int i = 0; i < SOLUTIONS_NUM; ++i) {
        solutionsList.emplace_back(SolutionTSP{});
        solutionsList[i].greedyAlgorithm(distanceMatrix, CITIES_NUM, randomMachine());
    }
}

void BeeColonyAlgorithm::sortSolutions() {
    std::sort(solutionsList.begin(), solutionsList.end(), [](const SolutionTSP &a, const SolutionTSP &b) {
        return a.pathLength < b.pathLength;
    });
}
