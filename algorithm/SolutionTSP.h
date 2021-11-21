#include <vector>
#include <ostream>

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
};
