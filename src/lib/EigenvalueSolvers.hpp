#ifndef _EIGENVALUE_SOLVERS_
#define _EIGENVALUE_SOLVERS_

#include "Array.hpp"

double powerEigenSolve(Array<double>& A, double tol, unsigned int maxiter);
double inverseEigenSolve(Array<double>& A, double alpha, double tol,
                unsigned int maxiter);
double rayleighEigenSolve(Array<double>& A, double tol, unsigned int maxiter);

#endif
