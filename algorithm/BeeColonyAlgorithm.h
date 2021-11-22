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

    //Best solution at the moment
    SolutionTSP bestSolution;
    vector<SolutionTSP> solutionsList;
    bool startIsGreedy;

    //Initialize solutions to work with
    void generateSolutionsList();

    float generateProbability();

    void sortSolutions();

public:
    BeeColonyAlgorithm(int **distanceMatrix, int CITIES_NUM, int BEE_NUM, float SCOUT_PERCENT, int SOLUTIONS_NUM,
                       int ITERATIONS_NUM, bool startIsGreedy) {
        this->distanceMatrix = distanceMatrix;

        this->BEE_NUM = BEE_NUM;
        this->SCOUT_NUM = BEE_NUM * SCOUT_PERCENT;
        this->FORAGER_NUM = BEE_NUM - SCOUT_NUM;

        this->SOLUTIONS_NUM = SOLUTIONS_NUM;
        this->ITERATIONS_NUM = ITERATIONS_NUM;
        this->CITIES_NUM = CITIES_NUM;

        this->startIsGreedy = startIsGreedy;

        randomMachine.seed(time(nullptr));
        generateSolutionsList();
        sortSolutions();
        bestSolution = solutionsList[0];
    }

    SolutionTSP startAlgorithm() {
        ofstream stats;
        stats.open(R"(D:\Programming\traveling-salesman-bee-algo\helpers\LastRunStats.csv)");
        stats << "Iteration;Function Value\n";
        for (int i = 0; i < ITERATIONS_NUM; ++i) {
            if (i % 20 == 0 || i == ITERATIONS_NUM) {
                cout << "Best solution on iteration #" << i << ": " << bestSolution.pathLength << '\n';
                stats << i << ';' << bestSolution.pathLength << '\n';
            }
            for (int j = 0; j < SCOUT_NUM / 2; ++j) {
                sendBees(j);
            }
            for (int j = 0; j < SCOUT_NUM - SCOUT_NUM / 2; ++j) {
                sendBees(randomMachine() % SOLUTIONS_NUM);
            }
            sortSolutions();
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

        if (bestNeighbor.pathLength < solutionsList[index].pathLength) {
            solutionsList[index] = bestNeighbor;
        }

        if (solutionsList[index].pathLength < bestSolution.pathLength) {
            bestSolution = solutionsList[index];
        }
    }
};