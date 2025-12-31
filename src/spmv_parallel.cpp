#include <omp.h>

#include "spmv.h"

void spmv_parallel(const CSRMatrix& A, const double* x, double* y) {
#pragma omp parallel for
    for (int i = 0; i < A.num_rows; i++) {
        double sum = 0.0;

        int start_index = A.row_ptr[i];
        int end_index = A.row_ptr[i + 1];

        for (int k = start_index; k < end_index; k++) {
            double val = A.values[k];
            int col = A.col_indices[k];

            sum += val * x[col];
        }

        y[i] = sum;
    }
}