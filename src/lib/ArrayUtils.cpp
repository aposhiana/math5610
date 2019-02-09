#include <cstdlib>

#include "ArrayUtils.hpp"
#include "Vector.hpp"
#include "DenseArray.hpp"

// TODO: move this to DenseArray class?
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

// Add two arrays of same dimension element-wise and return a Vector<double>*
// if colDim is 1 otherwise return a DenseArray
// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* add(Array<double>* a, Array<double>* b) {
    if (a->colDim() != b->colDim() || a->rowDim() != b->rowDim()) {
        std::cout << "Cannot add Arrays of different dimensionality" << std::endl;
        throw std::exception();
    }
    Array<double>* newArray;
    if (a->colDim() == 1) {
        newArray = new Vector<double>(a->rowDim());
    }
    else {
        newArray = new DenseArray<double>(a->rowDim(), a->colDim());
    }

    for (unsigned int i = 0; i < a->rowDim(); i++) {
        for (unsigned int j = 0; j < a->colDim(); j++) {
            newArray->set(i, j, (*a)(i, j) + (*b)(i, j));
        }
    }
    return newArray;
}


// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* multipy(double scalar, Array<double>* a) {
    Array<double>* newArray;
    if (a->colDim() == 1) {
        newArray = new Vector<double>(a->rowDim());
    }
    else {
        newArray = new DenseArray<double>(a->rowDim(), a->colDim());
    }

    for (unsigned int i = 0; i < a->rowDim(); i++) {
        for (unsigned int j = 0; j < a->colDim(); j++) {
            newArray->set(i, j, (*a)(i, j) * scalar);
        }
    }
    return newArray;
}
