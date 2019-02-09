#ifndef _ARRAY_UTILS_HPP_
#define _ARRAY_UTILS_HPP_

#include "Array.hpp"

double** makeRandomArray(const unsigned int rowDim, const unsigned int colDim,
                const double minVal=0.0, const double maxVal=1.0);

Array<double>* add(Array<double>* a, Array<double>* b);
Array<double>* multipy(double scalar, Array<double>* a);

#endif
