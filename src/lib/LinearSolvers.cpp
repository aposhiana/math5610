#include <cstdlib>

#include "LinearSolvers.hpp"
#include "ArrayUtils.hpp"

Vector<double>& solveLinearDiagonalSystem(Array<double>& A, Vector<double>& b) {
    assertLinearSystem(A, b);
    Vector<double>* x = new Vector<double>(b.rowDim(), true);
    for (unsigned int i = 0; i < x->rowDim(); i++) {
        double x_i = b(i) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& backsub(DenseArray<double>& A, Vector<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    double x_n = b(lastIndex) / A(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& backsub(DenseArray<double>& AB) {
    assertLinearSystem(AB);
    unsigned int n = AB.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    // Note that column n of AB is b
    double x_n = AB(lastIndex, n) / AB(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += AB(i, j) * (*x)(j);
        }
        double x_i = (AB(i, n) - sum) / AB(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& forwardsub(DenseArray<double>& A, Vector<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    for (unsigned int i = 0; i < n; i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < i; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

// Vector<double>& forwardsub(DenseArray<double>& AB) {
//     assertLinearSystem(AB);
//     unsigned int n = AB.rowDim();
//     // Note that column n of AB is b
//     Vector<double>* x = new Vector<double>(n, true);
//     for (unsigned int i = 0; i < n; i++) {
//         double sum = 0.0;
//         for (unsigned int j = 0; j < i; j++) {
//             sum += AB(i, j) * (*x)(j);
//         }
//         double x_i = (AB(i, n) - sum) / AB(i, i);
//         x->set(i, x_i);
//     }
//     return *x;
// }
