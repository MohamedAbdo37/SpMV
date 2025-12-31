#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct CSRMatrix
{
    int num_values;
    int num_cols;
    int num_rows;

    vector<double> values;
    vector<int> cols;
    vector<int> rows;
};


CSRMatrix generateRandomCSR(int rows, int cols, double density);

vector<int> generatendicesVector(int size, int maxValue);

vector<double> generateDoubleVector(int size);

void initializeResultsOutputFile();

void writeResultsToFile(double time, double density, int typeOfExecution, int rows, int cols);

// for testing 
void testUtils();

void printCSRMatrix(CSRMatrix matrix); 

#endif