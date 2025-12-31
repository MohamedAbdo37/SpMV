#include "utils.h"

void testUtils() {
    cout << "Hello from testUtils" << endl;
}

CSRMatrix generateRandomCSR(int rows, int cols, double density) {
    vector<double> temp_values;
    vector<int> temp_cols;
    vector<int> temp_row_ptr;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    temp_row_ptr.push_back(0);

    for (int i = 0; i < rows; i++) {
        set<int> col_set;
        int nnz_this_row = max(1, (int)(cols * density));

        while (col_set.size() < (size_t)(nnz_this_row)) {
            col_set.insert(generator() % cols);
        }

        for (int c : col_set) {
            temp_cols.push_back(c);
            temp_values.push_back((double)(generator() % 1000) / 10.0);
        }

        temp_row_ptr.push_back(temp_values.size());
    }

    CSRMatrix mat;
    mat.num_rows = rows;
    mat.num_cols = cols;
    mat.num_non_zeros = temp_values.size();

    mat.values = new double[mat.num_non_zeros];
    mat.col_indices = new int[mat.num_non_zeros];
    mat.row_ptr = new int[mat.num_rows + 1];

    memcpy(mat.values, temp_values.data(), mat.num_non_zeros * sizeof(double));
    memcpy(mat.col_indices, temp_cols.data(), mat.num_non_zeros * sizeof(int));
    memcpy(mat.row_ptr, temp_row_ptr.data(), (mat.num_rows + 1) * sizeof(int));

    return mat;
}

void freeCSR(CSRMatrix& mat) {
    delete[] mat.values;
    delete[] mat.col_indices;
    delete[] mat.row_ptr;

    // Safety: set to nullptr
    mat.values = nullptr;
    mat.col_indices = nullptr;
    mat.row_ptr = nullptr;
}

pair<long long, long long> printCSRMatrix(CSRMatrix& matrix, double density) {
    int rows = matrix.num_rows;
    int cols = matrix.num_cols;

    long long full_count = (long long)rows * cols;
    int actual_nnz = matrix.num_non_zeros;

    long long dense_memory = full_count * sizeof(double);

    long long csr_memory =
        (actual_nnz * sizeof(double)) + (actual_nnz * sizeof(int)) + ((rows + 1) * sizeof(int));

    cout << "\n--- Comparison Report ---" << endl;
    cout << left << setw(25) << "Dense Memory (Est):" << (dense_memory / 1024) << " KB - "
         << (dense_memory / 1024) / 1024 << " MB" << endl;
    cout << left << setw(25) << "CSR Memory (Actual):" << (csr_memory / 1024) << " KB - "
         << (csr_memory / 1024) / 1024 << " MB" << endl;

    cout << "----------------------------------------" << endl;

    return {(dense_memory / 1024), (csr_memory / 1024)};
}

void initializeResultsOutputFile() {
    std::ofstream outFile("experiment_results.csv");

    if (outFile.is_open()) {
        outFile << "Rows,Cols,Density,ExecutionType,Time_ms,Dense_KB,CSR_KB\n";
        outFile.close();
        std::cout << "Results file initialized: experiment_results.csv" << std::endl;
    } else {
        std::cerr << "Error: Could not create results file!" << std::endl;
    }
}

void writeResultsToFile(double time,
                        double density,
                        int typeOfExecution,
                        int rows,
                        int cols,
                        long long denseBytes,
                        long long csrBytes) {
    std::ofstream outFile("experiment_results.csv", std::ios::app);

    if (outFile.is_open()) {
        std::string typeStr = (typeOfExecution == 0) ? "Serial" : "Parallel";

        long long denseKB = denseBytes / 1024;
        long long csrKB = csrBytes / 1024;

        outFile << rows << "," << cols << "," << density << "," << typeStr << "," << time << ","
                << denseKB << "," << csrKB << "\n";

        outFile.close();
    } else {
        std::cerr << "Error: Could not write to results file!" << std::endl;
    }
}

double getValue(const CSRMatrix& A, int row, int col) {
    if (row < 0 || row >= A.num_rows || col < 0 || col >= A.num_cols) {
        throw invalid_argument("Invalid row or column index.");
    }

    int start = A.row_ptr[row];
    int end = A.row_ptr[row + 1];

    for (int k = start; k < end; k++) {
        if (A.col_indices[k] == col) {
            return A.values[k];
        }
    }

    return 0.0;
}

double* generateDoubleVector(int size) {
    double* result = new double[size];

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    normal_distribution<double> distribution(0.0, 100.0);

    for (int i = 0; i < size; i++) {
        result[i] = distribution(generator);
    }

    return result;
}