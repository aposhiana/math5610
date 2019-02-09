#ifndef _VECTOR_NORMS_HPP_
#define _VECTOR_NORMS_HPP_

double absoluteError(const double x, const double y);
double relativeError(const double x, const double y);
double oneNorm(Vector<double>* v);
double twoNorm(Vector<double>* v);
double infNorm(Vector<double>* v);

#endif