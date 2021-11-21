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

    void generateSolutionsList(){
        for (int i = 0; i < SOLUTIONS_NUM; ++i) {
            solutionsList.push_back(SolutionTSP{});
            solutionsList[i].generateRandomSolution(CITIES_NUM, randomMachine());
            cout << solutionsList[i];
            solutionsList[i].calculateSolutionWeight(distanceMatrix);
        }
    }

public:
    BeeColonyAlgorithm(int CITIES_NUM, int **distanceMatrix) {
        this->CITIES_NUM = CITIES_NUM;
        this->distanceMatrix = distanceMatrix;
        SOLUTIONS_NUM = 10;
        randomMachine.seed(time(nullptr));
        generateSolutionsList();
        //cout << solutionsList[30];
    }



};