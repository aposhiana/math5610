#ifndef _ARRAY_UTILS_HPP_
#define _ARRAY_UTILS_HPP_

#include "Array.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"

double** makeRandomRawArray(const unsigned int rowDim, const unsigned int colDim,
                const double min=0.0, const double max=1.0);
void assertSameDim(Array<double>& x, Array<double>& y);
void assertLinearSystem(Array<double>& A, Array<double>& b);
void assertLinearSystem(Array<double>& A);
Array<double>* add(Array<double>* a, Array<double>* b);
Array<double>* subtract(Array<double>* a, Array<double>* b);
Array<double>* multiply(const double scalar, Array<double>* a);
Array<double>* multiply(Array<double>* a, Array<double>* b);
Array<double>* matmul(Array<double>* a, Array<double>* b);
double dot(Array<double>& a, Array<double>& b);
Vector<double>& cross(Vector<double>& a, Vector<double>& b);
DenseArray<double>* transpose(Array<double>* a);
Array<double>* getRandomSPDArray(unsigned int dim);
double* rawMatVecProduct(const double *const * A, const double* v,
                const unsigned int m, const unsigned int n);
double* rawAdd(const double* a, const double* b, const unsigned int n);
double* rawSubtract(const double* a, const double* b, const unsigned int n);
double rawDot(const double* v, const double* w, const unsigned int n);
void copyBintoA(double* a, const double* b, const unsigned int n);

#endif
