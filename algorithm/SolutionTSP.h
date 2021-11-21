#include <vector>
#include <ostream>
#include <iostream>
#include <set>

using namespace std;

struct SolutionTSP {
    vector<int> solution;
    int pathLength;

    void generateRandomSolution(int CITIES_NUM, int RANDOM_SEED);

    // Simply swaps two neighbor cities
    SolutionTSP generateNeighborSolution(int RANDOM_SEED) const;

    static int calculateSolutionWeight(vector<int> &solutionToCalc, int **distanceMatrix);

    int calculateSolutionWeight(int **distanceMatrix);

    friend std::ostream &operator<<(std::ostream &os, const SolutionTSP &tsp);

    void greedyAlgorithm(int** distanceMatrix, int CITIES_NUM, int RANDOM_SEED){
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
                if(distanceMatrix[curCity][j] == 0){
                    continue;
                }
                if(distanceMatrix[curCity][j] < localBest && !visited.contains(j)){
                    localBest = distanceMatrix[curCity][j];
                    localBestIndex = j;
                }
            }
            solution.push_back(localBestIndex);
            visited.insert(localBestIndex);
        }
        this->calculateSolutionWeight(distanceMatrix);
    }
};
