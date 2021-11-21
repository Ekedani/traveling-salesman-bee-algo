#include <random>
#include <utility>

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
    vector<int> bestSolution;
    int bestSolutionWeight;



    vector<int> generateRandomSolution(){

    }

public:
    /*BeeColonyAlgorithm() {

    }*/

};