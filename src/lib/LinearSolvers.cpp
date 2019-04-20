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
