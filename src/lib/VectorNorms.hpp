#ifndef _VECTOR_NORMS_HPP_
#define _VECTOR_NORMS_HPP_

#include "Vector.hpp"

double absoluteError(const double x, const double y);
double relativeError(const double x, const double y);
double l1Norm(Vector<double>& v);
double l2Norm(Vector<double>& v);
double infNorm(Vector<double>& v);
double vectorError(Vector<double>& x,
                Vector<double>& y,
                std::function<double(const double, const double)> scalarError,
                std::function<double(Vector<double>&)> norm);
double l2NormAbsoluteError(Vector<double>& x, Vector<double>& y);
double l1NormAbsoluteError(Vector<double>& x, Vector<double>& y);
double infNormAbsoluteError(Vector<double>& x, Vector<double>& y);

#endif