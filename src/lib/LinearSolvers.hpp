#ifndef _LINEAR_SOLVERS_
#define _LINEAR_SOLVERS_

#include "Vector.hpp"
#include "DenseArray.hpp"

Vector<double>& solveLinearDiagonalSystem(Array<double>& A, Vector<double>& b);
Vector<double>& backsub(DenseArray<double>& A, Vector<double>& b);

#endif