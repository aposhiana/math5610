#include <cstdlib>

#include "ArrayUtils.hpp"
#include "Vector.hpp"
#include "DenseArray.hpp"

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
    if (a->colDim() != b->colDim() || a->rowDim() != b->rowDim()) {
        std::cout << "Cannot multiply Arrays of different dimensionality" << std::endl;
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
            newArray->set(i, j, (*a)(i, j) * (*b)(i, j));
        }
    }
    return newArray;
}