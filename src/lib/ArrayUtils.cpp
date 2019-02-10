#include <cstdlib>

#include "ArrayUtils.hpp"
#include "Vector.hpp"
#include "DenseArray.hpp"

// Asserts Arrays have the same dimensionality
void assertSameDim(Array<double>& a, Array<double>& b) {
    if (a.colDim() != b.colDim() || a.rowDim() != b.rowDim()) {
        std::cout << "Arrays of different dimensionality" << std::endl;
        throw std::exception();
    }
}

// Add two arrays of same dimension element-wise and return a Vector<double>*
// if colDim is 1 otherwise return a DenseArray
// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* add(Array<double>* a, Array<double>* b) {
    assertSameDim(*a, *b);
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
Array<double>* multiply(double scalar, Array<double>* a) {
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

// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* multiply(Array<double>* a, Array<double>* b) {
    assertSameDim(*a, *b);
    Array<double>* newArray;
    if (a->colDim() == 1) {
        newArray = new Vector<double>(a->rowDim());
    }
    else {
        newArray = new DenseArray<double>(a->rowDim(), a->colDim());
    }

    for (unsigned int i = 0; i < a->rowDim(); i++) {
        for (unsigned int j = 0; j < a->colDim(); j++) {
            newArray->set(i, j, (*a)(i, j) * (*b)(i, j));
        }
    }
    return newArray;
}

// Returns the result of matrix multiplication of a on b
// TODO: Add sparse flag?
Array<double>* matmul(Array<double>* a, Array<double>* b) {
    if (a->colDim() != b->rowDim()) {
        std::cout << "Cannot multiply a of colDim " << a->colDim();
        std::cout << " with b of rowDim " << b->rowDim() << std::endl;
        throw std::exception();
    }
    const unsigned int M = a->rowDim();
    const unsigned int N = a->colDim();
    const unsigned int P = b->colDim();
    double** cRaw = new double*[M];
    for (unsigned int i = 0; i < M; i++) {
        cRaw[i] = new double[P];
    }

    // Set every element (i, j) in c
    for (unsigned int i = 0; i < M; i++) {
        for (unsigned int k = 0; k < N; k++) {
            // Row-only iteration in innermost loop for speed
            for (unsigned int j = 0; j < P; j++) {
                cRaw[i][j] += (*a)(i, k) * (*b)(k, j);
            }
        }
    }
    Array<double>* c = new DenseArray<double>(cRaw, M, P);
    return c;
}
