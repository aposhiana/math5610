#ifndef _LINEAR_SOLVERS_
#define _LINEAR_SOLVERS_

#include "Vector.hpp"
#include "DenseArray.hpp"

Vector<double>& solveLinearDiagonalSystem(Array<double>& A, Vector<double>& b);
Vector<double>& backsub(Array<double>& A, Array<double>& b);
Vector<double>& backsub(Array<double>& AB);
Vector<double>& forwardsub(Array<double>& A, Array<double>& b);
void rowReduce(DenseArray<double>& A, Vector<double>& b);
void rowReduce(DenseArray<double>& AB);
Vector<double>& solveLinearSystem(DenseArray<double>& A, Vector<double>& b);
Vector<double>& solveLinearSystem(DenseArray<double>& AB);
void lu(DenseArray<double>& A, DenseArray<double>& L, DenseArray<double>& U);
Vector<double>& luSolve(DenseArray<double>& L,
                DenseArray<double>& U, Vector<double>& b);
Vector<double>& qrSolve(DenseArray<double>& Q,
                DenseArray<double>& R, Vector<double>& b);
void cholesky(Array<double>& A);
Vector<double>& solveNormalEquation(Array<double>& A, Vector<double>& b);
void squareClassicalGramSchmidt(DenseArray<double>& A, DenseArray<double>& Q,
                DenseArray<double>& R);
void squareModifiedGramSchmidt(DenseArray<double>& A, DenseArray<double>& Q,
                DenseArray<double>& R);
Vector<double>& jacobiSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter);
Vector<double>& gaussSeidelSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter);
Array<double>* steepestDescentSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter);
Vector<double>* cg(Array<double>& A, Vector<double>& b, double tol);

#endif
