#ifndef _MATRIX_NORMS_HPP_
#define _MATRIX_NORMS_HPP_

#include "Array.hpp"

double matrix1Norm(Array<double>& a);
double matrixInfNorm(Array<double>& a);
double estimate2NormConditionNumber(Array<double>& A, double tol, unsigned int maxiter);

#endif