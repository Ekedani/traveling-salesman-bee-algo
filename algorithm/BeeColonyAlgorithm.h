#include "SolutionTSP.h"
#include <random>
#include <fstream>
#include <ctime>
#include <utility>
#include <iostream>

using namespace std;

class BeeColonyAlgorithm {
private:
    //Algorithm parameters
    int BEE_NUM;
    int SCOUT_NUM;
    int FORAGER_NUM;
    int SOLUTIONS_NUM;
    int ITERATIONS_NUM;
    int CITIES_NUM;
    float MISTAKE_PROB;
    int **distanceMatrix;
    bool startIsGreedy;

    // Changing that parameter isn't necessary
    constexpr static const float PROB_RANDOM = 0.4;

    //Generator of random numbers
    mt19937 randomMachine;

    //Best solution at the moment
    SolutionTSP bestSolution;
    vector<SolutionTSP> solutionsList;

    //Initialize solutions to work with
    void generateSolutionsList();

    //We need it because some parts of this algorithm are based on probabilities
    float generateProbability();

    //Because we must use best existing solutions sometimes
    void sortSolutions();

    //Returns true if success
    bool sendScout(int &curBestIdx, set<int> &visitedSolutions);

    //Method that tries to improve solution
    void sendForagers(int index);

public:
    //Constructor with all parameters of the algorithm
    BeeColonyAlgorithm(int **distanceMatrix, int CITIES_NUM, int BEE_NUM, float SCOUT_PERCENT, int SOLUTIONS_NUM,
                       int ITERATIONS_NUM, float MISTAKE_PROB, bool startIsGreedy);

    //Method that runs algorithm and generates statistics
    SolutionTSP startAlgorithm();
};