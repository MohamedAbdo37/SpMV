#include <chrono>
#include <iostream>
#include <vector>

#include "spmv.h"
#include "utils.h"

const int NUM_RUNS = 10;

double benchmarkSerial(const CSRMatrix& mat, const double* x, double* y) {
    // warm-up
    spmv_serial(mat, x, y);

    double total = 0.0;
    for (int i = 0; i < NUM_RUNS; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        spmv_serial(mat, x, y);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return (total / NUM_RUNS) / 1000.0;  // ms
}

double benchmarkParallel(const CSRMatrix& mat, const double* x, double* y) {
    // warm-up
    spmv_parallel(mat, x, y);

    double total = 0.0;
    for (int i = 0; i < NUM_RUNS; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        spmv_parallel(mat, x, y);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return (total / NUM_RUNS) / 1000.0;  // ms
}

int main() {
    std::vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};
    std::vector<double> densities = {0.01, 0.02, 0.05, 0.1, 0.15, 0.2};

    initializeResultsOutputFile();

    for (double density : densities) {
        std::cout << "================ Density: " << density * 100 << "% ================\n";

        for (int size : sizes) {
            std::cout << "--- Size: " << size << " x " << size << " ---\n";

            CSRMatrix matrix = generateRandomCSR(size, size, density);
            double* x = generateDoubleVector(size);
            double* y = new double[size];

            auto memoryStats = printCSRMatrix(matrix, density);

            double serialTime = benchmarkSerial(matrix, x, y);
            double parallelTime = benchmarkParallel(matrix, x, y);

            writeResultsToFile(
                serialTime, density, 0, size, size, memoryStats.first, memoryStats.second);
            writeResultsToFile(
                parallelTime, density, 1, size, size, memoryStats.first, memoryStats.second);

            std::cout << "Serial:   " << serialTime << " ms\n";
            std::cout << "Parallel: " << parallelTime << " ms\n";
            std::cout << "Speedup:  " << serialTime / parallelTime << "x\n";
            std::cout << "--------------------------------------------\n";

            freeCSR(matrix);
            delete[] x;
            delete[] y;
        }
    }

    return 0;
}
