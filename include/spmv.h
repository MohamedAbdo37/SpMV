#ifndef SPMV_H
#define SPMV_H

#include "utils.h"

void spmv_serial(const CSRMatrix& A, const double* x, double* y);

void spmv_parallel(const CSRMatrix& A, const double* x, double* y);

#endif