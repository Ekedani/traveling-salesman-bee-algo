#include "BeeColonyAlgorithm.h"

void BeeColonyAlgorithm::generateSolutionsList() {
    if(startIsGreedy){
        for (int i = 0; i < SOLUTIONS_NUM; ++i) {
            solutionsList.emplace_back(SolutionTSP{});
            solutionsList[i].greedyAlgorithm(distanceMatrix, CITIES_NUM, randomMachine());
        }
    }
    else{
        for (int i = 0; i < SOLUTIONS_NUM; ++i) {
            solutionsList.emplace_back(SolutionTSP{});
            solutionsList[i].generateRandomSolution(CITIES_NUM, randomMachine());
            solutionsList[i].calculateSolutionWeight(distanceMatrix);
        }
    }

}

void BeeColonyAlgorithm::sortSolutions() {
    std::sort(solutionsList.begin(), solutionsList.end(), [](const SolutionTSP &a, const SolutionTSP &b) {
        return a.pathLength < b.pathLength;
    });
}

float BeeColonyAlgorithm::generateProbability() {
    float result = static_cast <float> (randomMachine()) / static_cast <float> (std::mt19937::max());
    return result;
}
