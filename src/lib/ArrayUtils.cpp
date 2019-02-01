#include <cstdlib>

#include "ArrayUtils.hpp"

double** makeRandomArray(const unsigned int rowDim, const unsigned int colDim,
                const double minVal, const double maxVal) {
    // Allocate rows
    double** a = new double*[rowDim];
    for (unsigned int i = 0; i < rowDim; i++) {
        // Allocate column
        a[i] = new double[colDim];
        for (unsigned int j = 0; j < colDim; j++) {
            // For generation of random value between minVal and maxVal
            double val1 = 0.0;
            if (minVal < 0) {
                val1 = (rand() / static_cast<double>(RAND_MAX)) * minVal;
            }
            double val2 = (rand() / static_cast<double>(RAND_MAX)) * maxVal;
            // Initialize array element with value
            a[i][j] = val1 + val2;
        }
    }
    return a;
}

// TODO: move this to DenseArray class?