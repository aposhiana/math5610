#ifndef _VECTOR_NORMS_HPP_
#define _VECTOR_NORMS_HPP_

double absoluteError(const double x, const double y);
double relativeError(const double x, const double y);
double oneNorm(const Vector<double>* v);
double twoNorm(const Vector<double>* v);
double infNorm(const Vector<double>* v);

#endif