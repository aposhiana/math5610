#ifndef _ARRAY_UTILS_HPP_
#define _ARRAY_UTILS_HPP_

#include "Array.hpp"

void assertSameDim(Array<double>& x, Array<double>& y);
Array<double>* add(Array<double>* a, Array<double>* b);
Array<double>* multiply(double scalar, Array<double>* a);
Array<double>* multiply(Array<double>* a, Array<double>* b);

#endif
