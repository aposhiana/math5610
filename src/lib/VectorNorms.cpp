#include <cstdlib>

#include "VectorNorms.hpp"

double absoluteError(const double x, const double y) {
    return abs(x - y);
}

double relativeError(const double x, const double y) {
    return absoluteError(x, y) / x;
}
