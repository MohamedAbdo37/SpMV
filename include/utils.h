#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using namespace std;

struct CSRMatrix {
    int num_non_zeros;
    int num_cols;
    int num_rows;

    double* values;
    int* col_indices;
    int* row_ptr;
};

const int SERIAL_EXEC = 0;
const int PARALLEL_EXEC = 1;

void freeCSR(CSRMatrix& mat);

CSRMatrix generateRandomCSR(int rows, int cols, double density);

double* generateDoubleVector(int size);

void initializeResultsOutputFile();

void writeResultsToFile(double time,
                        double density,
                        int typeOfExecution,
                        int rows,
                        int cols,
                        long long denseBytes,
                        long long csrBytes);
void testUtils();

pair<long long, long long> printCSRMatrix(CSRMatrix& matrix, double density);

double getValue(const CSRMatrix& A, int row, int col);

#endif