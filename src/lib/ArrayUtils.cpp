#include <cstdlib>

#include "ArrayUtils.hpp"
#include "Utils.hpp"


// Get a raw 2D array with random values
double** makeRandomRawArray(const unsigned int rowDim, const unsigned int colDim,
                const double min, const double max) {
    // Assert min < max
    assertProperMinMax(min, max);
    // Allocate rows
    double** a = new double*[rowDim];
    for (unsigned int i = 0; i < rowDim; i++) {
        // Allocate column
        a[i] = new double[colDim];
        for (unsigned int j = 0; j < colDim; j++) {
            // Set element
            a[i][j] = getRandDouble(min, max);
        }
    }
    return a;
}


// Asserts Arrays have the same dimensionality
void assertSameDim(Array<double>& a, Array<double>& b) {
    if (a.colDim() != b.colDim() || a.rowDim() != b.rowDim()) {
        std::cout << "Arrays of different dimensionality" << std::endl;
        throw std::exception();
    }
}

// Internal method that returns a pointer to a new empty initialized
// Vector matching the specified dimesions if colDim == 1 and
// otherwise returns a pointer to a DenseArray instance matching
// the specified dimensions
Array<double>* getResultArray(const unsigned int rowDim, const unsigned int colDim) {
    Array<double>* newArray;
    if (colDim == 1) {
        newArray = new Vector<double>(rowDim, true);
    }
    else {
        newArray = new DenseArray<double>(rowDim, colDim, true);
    }
    return newArray;
}

// Add two arrays of same dimension element-wise and return a Vector<double>*
// if colDim is 1 otherwise return a DenseArray
// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* add(Array<double>* a, Array<double>* b) {
    assertSameDim(*a, *b);
    Array<double>* newArray = getResultArray(a->rowDim(), a->colDim());
    for (unsigned int i = 0; i < a->rowDim(); i++) {
        for (unsigned int j = 0; j < a->colDim(); j++) {
            newArray->set(i, j, (*a)(i, j) + (*b)(i, j));
        }
    }
    return newArray;
}

// TODO return SparseArray if sparse flag is true (default to false)
Array<double>* multiply(const double scalar, Array<double>* a) {
    Array<double>* newArray = getResultArray(a->rowDim(), a->colDim());
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
    Array<double>* newArray = getResultArray(a->rowDim(), a->colDim());
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

// Compute the dot product of two vectors of the same length
double dot(Vector<double>& a, Vector<double>& b) {
    assertSameDim(a, b);
    double result = 0;
    for (unsigned int i = 0; i < a.rowDim(); i++) {
        result += a(i) * b(i);
    }
    return result;
}

// Compute the cross product of two 3D vectors
Vector<double>& cross(Vector<double>& a, Vector<double>& b) {
    if (a.rowDim() != 3 || b.rowDim() != 3) {
        std::cout << "Vectors must be 3-dimensional for cross product" << std::endl;
        throw std::exception();
    }
    Vector<double>* result = new Vector<double>(3, true);
    result->set(0, a(1) * b(2) - b(1) * a(2));
    result->set(1, a(2) * b(0) - b(2) * a(0));
    result->set(2, a(0) * b(1) - b(0) * a(1));
    return *result;
}

// Get the transpose of an Array of doubles as a DenseArray of doubles
DenseArray<double>* transpose(Array<double>* a) {
    const unsigned int OLD_ROW_DIM = a->rowDim();
    const unsigned int OLD_COL_DIM = a->colDim();
    const unsigned int NEW_ROW_DIM = OLD_COL_DIM;
    const unsigned int NEW_COL_DIM = OLD_ROW_DIM;

    DenseArray<double>* aT = new DenseArray<double>(NEW_ROW_DIM, NEW_COL_DIM, true);
    for (unsigned int i = 0; i < NEW_ROW_DIM; i++) {
        for (unsigned int j = 0; j < NEW_COL_DIM; j++) {
            aT->set(i, j, (*a)(j, i));
        }
    }
    return aT;
}
