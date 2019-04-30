#include <cmath>

#include "MatrixNorms.hpp"
#include "EigenvalueSolvers.hpp"

// Get 1-norm of a matrix
double matrix1Norm(Array<double>& a) {
    // -1 will always be less than any sum
    double maxColL1Norm = -1;
    for (unsigned int j = 0; j < a.colDim(); j++) {
        double colL1Norm = 0;
        for (unsigned int i = 0; i < a.rowDim(); i++) {
            colL1Norm += std::fabs(a(i, j));
        }
        if (colL1Norm > maxColL1Norm) {
            maxColL1Norm = colL1Norm;
        }
    }
    return maxColL1Norm;
}

// Get infinity-norm of a matrix
double matrixInfNorm(Array<double>& a) {
    // -1 will always be less than any sum
    double maxRowL1Norm = -1;
    for (unsigned int i = 0; i < a.rowDim(); i++) {
        double rowL1Norm = 0;
        for (unsigned int j = 0; j < a.colDim(); j++) {
            rowL1Norm += std::fabs(a(i, j));
        }
        if (rowL1Norm > maxRowL1Norm) {
            maxRowL1Norm = rowL1Norm;
        }
    }
    return maxRowL1Norm;
}

double estimate2NormConditionNumber(Array<double>& A, double tol, unsigned int maxiter) {
    double largest = powerEigenSolve(A, tol, maxiter);
    double smallest = inverseEigenSolve(A, 0, tol, maxiter);
    return std::fabs(largest / smallest);
}