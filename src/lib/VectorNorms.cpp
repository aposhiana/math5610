#include <cmath>
#include <functional>

#include "VectorNorms.hpp"
#include "ArrayUtils.hpp"

// Get the L1-norm for a vector
double l1Norm(Vector<double>& v) {
    double norm = 0;
    for (unsigned int i = 0; i < v.rowDim(); i++) {
        norm += abs(v(i));
    }
    return norm;
}

// Get the L2-norm for a vector
double l2Norm(Vector<double>& v) {
    double sum = 0;
    for (unsigned int i = 0; i < v.rowDim(); i++) {
        sum += v(i) * v(i);
    }
    return sqrt(sum);
}

// Get the infinity-norm for a vector
double infNorm(Vector<double>& v) {
    // -1 will always be less than the abs of any element
    double max = -1;
    for (unsigned int i = 0; i < v.rowDim(); i++) {
        double absValElement = abs(v(i));
        if (absValElement > max) {
            max = absValElement;
        }
    }
    return max;
}

// Get the absolute error between two scalars
double absoluteError(const double x, const double y) {
    return abs(x - y);
}

// Get the relative error between two scalars
double relativeError(const double x, const double y) {
    return absoluteError(x, y) / x;
}

// Get the error between two vectors
double vectorError(Vector<double>& x,
                Vector<double>& y,
                std::function<double(const double, const double)> scalarError,
                std::function<double(Vector<double>&)> norm) {
    assertSameDim(x, y);
    const unsigned int DIM = x.rowDim();
    Vector<double>* errorVector = new Vector<double>(DIM, true);
    for (unsigned int i = 0; i < DIM; i++) {
        errorVector->set(i, scalarError(x(i), y(i)));
    }
    return norm(*errorVector);
}

// Get the absolute error between two vectors when L2-norm is used
double l2NormAbsoluteError(Vector<double>& x, Vector<double>& y) {
    std::function<double(const double, const double)> scalarError = absoluteError;
    std::function<double(Vector<double>&)> norm = l2Norm;
    return vectorError(x, y, scalarError, norm);
}

// Get the absolute error between two vectors when L1-norm is used
double l1NormAbsoluteError(Vector<double>& x, Vector<double>& y) {
    std::function<double(const double, const double)> scalarError = absoluteError;
    std::function<double(Vector<double>&)> norm = l1Norm;
    return vectorError(x, y, scalarError, norm);
}

// Get the absolute error between two vectors when infinity-norm is used
double infNormAbsoluteError(Vector<double>& x, Vector<double>& y) {
    std::function<double(const double, const double)> scalarError = absoluteError;
    std::function<double(Vector<double>&)> norm = infNorm;
    return vectorError(x, y, scalarError, norm);
}
