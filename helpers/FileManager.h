#include <utility>
#include <fstream>

using namespace std;

class FileManager {
public:
    static void saveMatrix(int **distanceMatrix, int verticesNum);

    static pair<int **, int> readMatrix();
};
