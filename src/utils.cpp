#include "utils.h"

void testUtils() {
    cout << "Hello from testUtils" << endl;
}

CSRMatrix generateRandomCSR(int rows, int cols, double density){
    int size = rows * cols;
    int num_values = size * density;
    CSRMatrix matrix;
    matrix.num_values = num_values;
    matrix.num_cols = cols;
    matrix.num_rows = rows;
    matrix.values = generateDoubleVector(num_values);
    matrix.cols = generatendicesVector(num_values, cols);
    matrix.rows = generatendicesVector(num_values, rows);
    return matrix;
}

vector<double> generateDoubleVector(int size) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    
    default_random_engine generator(seed);
    
    uniform_real_distribution<double> distribution(0.0, 100.0);

    vector<double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = distribution(generator);
    }
    return vec;
}

vector<int> generatendicesVector(int size, int maxValue) {
    vector<int> indices(size);
    return indices;
}

void initializeResultsOutputFile();

void writeResultsToFile(double time, double density, int typeOfExecution, int rows, int cols);
