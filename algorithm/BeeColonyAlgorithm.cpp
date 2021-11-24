#include "BeeColonyAlgorithm.h"

void BeeColonyAlgorithm::generateSolutionsList() {
    if (startIsGreedy) {
        for (int i = 0; i < SOLUTIONS_NUM; ++i) {
            solutionsList.emplace_back(SolutionTSP{});
            solutionsList[i].greedyAlgorithm(distanceMatrix, CITIES_NUM, randomMachine());
        }
    } else {
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

bool BeeColonyAlgorithm::sendScout(int &curBestIdx, set<int> &visitedSolutions) {
    auto random = generateProbability();
    if (random < PROB_RANDOM) {
        // Send to random unvisited solution
        int idx = randomMachine() % SOLUTIONS_NUM;
        if (visitedSolutions.contains(idx)) {
            return false;
        }
        visitedSolutions.insert(idx);
        sendForagers(idx);
    } else {
        // Send to best unvisited solution
        if (visitedSolutions.contains(curBestIdx)) {
            curBestIdx++;
            return false;
        }
        visitedSolutions.insert(curBestIdx);
        sendForagers(curBestIdx);
        curBestIdx++;
    }
    return true;
}

BeeColonyAlgorithm::BeeColonyAlgorithm(int **distanceMatrix, int CITIES_NUM, int BEE_NUM, float SCOUT_PERCENT,
                                       int SOLUTIONS_NUM, int ITERATIONS_NUM, float MISTAKE_PROB, bool startIsGreedy) {
    this->distanceMatrix = distanceMatrix;

    this->BEE_NUM = BEE_NUM;
    this->SCOUT_NUM = BEE_NUM * SCOUT_PERCENT;
    this->FORAGER_NUM = BEE_NUM - SCOUT_NUM;

    this->SOLUTIONS_NUM = SOLUTIONS_NUM;
    this->ITERATIONS_NUM = ITERATIONS_NUM;
    this->CITIES_NUM = CITIES_NUM;

    this->MISTAKE_PROB = MISTAKE_PROB;
    this->startIsGreedy = startIsGreedy;

    randomMachine.seed(time(nullptr));
    generateSolutionsList();
    sortSolutions();
    bestSolution = solutionsList[0];
}

void BeeColonyAlgorithm::sendForagers(int index) {
    SolutionTSP bestNeighbor;
    bestNeighbor.pathLength = INT_MAX;

    for (int i = 0; i < FORAGER_NUM; ++i) {
        auto curNeighbor = solutionsList[index].generateNeighborSolution(randomMachine());
        curNeighbor.calculateSolutionWeight(distanceMatrix);
        if (curNeighbor.pathLength < bestNeighbor.pathLength) {
            bestNeighbor = curNeighbor;
        }
    }

    if (bestNeighbor.pathLength < solutionsList[index].pathLength && MISTAKE_PROB < generateProbability()) {
        solutionsList[index] = bestNeighbor;
    }
    if (solutionsList[index].pathLength < bestSolution.pathLength) {
        bestSolution = solutionsList[index];
    }
}

SolutionTSP BeeColonyAlgorithm::startAlgorithm() {

    ofstream stats;
    stats.open(R"(D:\Programming\traveling-salesman-bee-algo\helpers\LastRunStats.csv)");
    stats << "Iteration;Function Value\n" << 0 << ';' << bestSolution.pathLength << '\n';
    cout << "Start solution length: " << bestSolution.pathLength << '\n';

    for (int i = 0; i < ITERATIONS_NUM; ++i) {
        set<int> visitedSolutions;
        int curBestIdx = 0;
        int scoutsSent = 0;
        while (scoutsSent != SCOUT_NUM && scoutsSent != SOLUTIONS_NUM) {
            if (sendScout(curBestIdx, visitedSolutions)) {
                scoutsSent++;
            }
        }
        sortSolutions();

        if ((i + 1) % 10 == 0 || i == ITERATIONS_NUM) {
            cout << "Best solution on iteration #" << i + 1 << ": " << bestSolution.pathLength << '\n';
            stats << i + 1 << ';' << bestSolution.pathLength << '\n';
        }
    }
    stats.close();
    return bestSolution;
}
