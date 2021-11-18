#include <ctime>
#include <cstdlib>

using namespace std;

class DistanceMatrixGenerator {
private:
    // Generation parameters
    static const int LOWER_BOUND = 5;
    static const int HIGHER_BOUND = 150;
public:
    static int **generateDistanceMatrix(const int VERTICES_NUM);
};
