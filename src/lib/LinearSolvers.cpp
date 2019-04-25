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

void rowReduce(DenseArray<double>& A, Vector<double>& b) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(A, b);
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
            double oldBVal = b(i);
            b.set(i, oldBVal - l * b(pivotIdx));
        }
    }
}

void rowReduce(DenseArray<double>& AB) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(AB);
    unsigned int n = AB.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = AB(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = AB(i, pivotIdx) / pivot;
            AB.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < (n + 1); j++) {
                double oldVal = AB(i, j);
                AB.set(i, j, oldVal - l * AB(pivotIdx, j));
            }
        }
    }
}

// Changes A to U and whatever is passed to L to L
void lu(DenseArray<double>& A, DenseArray<double>& L) {
    assertSameDim(A, L);
    // TODO: Add scaled partial pivoting
    L.makeIdentity();
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            L.set(i, pivotIdx, l);
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
        }
    }
}

Vector<double>& solveLinearSystem(DenseArray<double>& A, Vector<double>& b) {
    rowReduce(A, b);
    return backsub(A, b);
}

Vector<double>& solveLinearSystem(DenseArray<double>& AB) {
    rowReduce(AB);
    return backsub(AB);
}

Vector<double>& luSolve(DenseArray<double>& L,
                DenseArray<double>& U, Vector<double>& b) {
    Vector<double> y = forwardsub(L, b);
    return backsub(U, y);
}
