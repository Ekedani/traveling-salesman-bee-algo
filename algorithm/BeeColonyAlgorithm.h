#include "SolutionTSP.h"
#include <random>
#include <fstream>
#include <ctime>
#include <utility>
#include <iostream>

using namespace std;

class BeeColonyAlgorithm {
private:
    //Bees parameters
    int BEE_NUM;
    int SCOUT_NUM;
    int FORAGER_NUM;

    int SOLUTIONS_NUM;
    int ITERATIONS_NUM;

    int CITIES_NUM;
    int **distanceMatrix;
    mt19937 randomMachine;

    float MISTAKE_PROB;
    // Changing that parameter isn't necessary
    constexpr static const float PROB_RANDOM = 0.4;

    //Best solution at the moment
    SolutionTSP bestSolution;
    vector<SolutionTSP> solutionsList;
    vector<int> uselessVisitsNums;
    bool startIsGreedy;

    //Initialize solutions to work with
    void generateSolutionsList();

    float generateProbability();

    void sortSolutions();

public:
    BeeColonyAlgorithm(int **distanceMatrix, int CITIES_NUM, int BEE_NUM, float SCOUT_PERCENT, int SOLUTIONS_NUM,
                       int ITERATIONS_NUM, float MISTAKE_PROB, bool startIsGreedy) {
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
        this->uselessVisitsNums = vector(CITIES_NUM, 0);
        sortSolutions();
        bestSolution = solutionsList[0];
    }

    SolutionTSP startAlgorithm() {
        ofstream stats;
        stats.open(R"(D:\Programming\traveling-salesman-bee-algo\helpers\LastRunStats.csv)");
        stats << "Iteration;Function Value\n" << 0 << ';' << bestSolution.pathLength << '\n';
        cout << "Start solution length: " << bestSolution.pathLength << '\n';
        for (int i = 0; i < ITERATIONS_NUM; ++i) {
            set<int> visitedSolutions;
            int localBestSolution = 0;
            int scoutsSent = 0;
            while (scoutsSent != SCOUT_NUM && scoutsSent != SOLUTIONS_NUM) {
                auto probRandom = generateProbability();
                if (probRandom < PROB_RANDOM) {
                    // Send to random solution
                    int idx = randomMachine() % SOLUTIONS_NUM;
                    if (visitedSolutions.contains(idx)) {
                        continue;
                    }
                    visitedSolutions.insert(idx);
                    sendBees(idx);
                } else {
                    if (visitedSolutions.contains(localBestSolution)) {
                        localBestSolution++;
                        continue;
                    }
                    visitedSolutions.insert(localBestSolution);
                    sendBees(localBestSolution);
                    localBestSolution++;
                }
                scoutsSent++;
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

    void sendBees(int index) {
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
            uselessVisitsNums[index] = 0;
        } else {
            uselessVisitsNums[index]++;
        }

        if (solutionsList[index].pathLength < bestSolution.pathLength) {
            bestSolution = solutionsList[index];
        }
    }
};