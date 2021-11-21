#include "SolutionTSP.h"
#include <random>
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

    void generateSolutionsList() {
        for (int i = 0; i < SOLUTIONS_NUM; ++i) {
            solutionsList.emplace_back(SolutionTSP{});
            solutionsList[i].generateRandomSolution(CITIES_NUM, randomMachine());
            solutionsList[i].calculateSolutionWeight(distanceMatrix);
        }
    }

public:
    BeeColonyAlgorithm(int CITIES_NUM, int **distanceMatrix) {
        this->CITIES_NUM = CITIES_NUM;
        this->SOLUTIONS_NUM = 10;
        this->distanceMatrix = distanceMatrix;
        randomMachine.seed(time(nullptr));
        generateSolutionsList();
        sortSolutions();
        for (auto solution : solutionsList) {
            cout << solution.pathLength << '\n';
        }
        cout << "Processing...";
        bestSolution = solutionsList[0];
    }

    SolutionTSP solve() {
        for (int i = 0; i < 10000; ++i) {
            for (int j = 0; j < 10; ++j) {
                sendBees(j);
            }
            sortSolutions();
        }
        for (auto solution : solutionsList) {
            cout << solution.pathLength << '\n';
        }
        return bestSolution;
    }

    void sortSolutions() {
        std::sort(solutionsList.begin(), solutionsList.end(), [](const SolutionTSP &a, const SolutionTSP &b) {
            return a.pathLength < b.pathLength;
        });
    }

    void sendBees(int index){
        SolutionTSP bestNeighbor;
        bestNeighbor.pathLength = INT_MAX;
        for (int i = 0; i < FORAGER_NUM; ++i) {
            auto curNeighbor = solutionsList[index].generateNeighborSolution(randomMachine());
            curNeighbor.calculateSolutionWeight(distanceMatrix);
            if(curNeighbor.pathLength < bestNeighbor.pathLength){
                bestNeighbor = curNeighbor;
            }
        }
        if(bestNeighbor.pathLength < solutionsList[index].pathLength){
            solutionsList[index] = bestNeighbor;
        }
        if(solutionsList[index].pathLength < bestSolution.pathLength){
            bestSolution = solutionsList[index];
        }
    }
};