#include <cmath>

#include "VectorNorms.hpp"
#include "Vector.hpp"

double absoluteError(const double x, const double y) {
    return abs(x - y);
}

double relativeError(const double x, const double y) {
    return absoluteError(x, y) / x;
}

double oneNorm(const Vector<double>* v) {
    double norm = 0;
    for (unsigned int i = 0; i < v->rowDim(); i++) {
        norm += abs(v(i));
    }
    return norm;
}

double twoNorm(const Vector<double>* v) {
    double sum = 0;
    for (unsigned int i = 0; i < v->rowDim(); i++) {
        sum += v(i) * v(i);
    }
    return sqrt(sum);
}

double infNorm(const Vector<double>* v) {
    // -1 will always be less than the abs of any element
    double max = -1;
    for (unsigned int i = 0; i < v->rowDim(); i++) {
        double absValElement = abs(v(i));
        if (absValElement > max) {
            max = absValElement;
        }
    }
    return max;
}
