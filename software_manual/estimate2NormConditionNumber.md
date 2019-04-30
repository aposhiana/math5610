**Routine Name:** estimate2NormConditionNumber

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "MatrixNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to estimate the condition number in the 2-norm for the given square matrix by computing the absolute value of the eigenvalue with the largest magnitude divided by the eigenvalue with the smallest magnitude.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `tol` : double value representing the tolerance for the accuracy of the eigenvalue
3. `maxiter` : unsigned int value for the maximum number of iterations to do before stopping solver

**Output:** A `double` representing the estimate of the condition number in the 2-norm for the matrix.

**Usage/Example:** The example below shows creating a Hilbert matrix with n = 4, then using the routine to estimate its condition number. The result is then printed.
```
std::cout << "Hilbert 4" << std::endl;
DenseArray<double>* hil4 = new DenseArray<double>(4);
hil4->makeHilbert();
double hil4Kappa = estimate2NormConditionNumber(*hil4, 0.000001, 10000);
std::cout << "hil4Kappa: " << hil4Kappa << std::endl;
```

Output from lines above:
```
Hilbert 4
hil4Kappa: 14837.3
```

**Implementation/Code:**
See [MatrixNorms.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/MatrixNorms.cpp)
```
double estimate2NormConditionNumber(Array<double>& A, double tol, unsigned int maxiter) {
    double largest = powerEigenSolve(A, tol, maxiter);
    double smallest = inverseEigenSolve(A, 0, tol, maxiter);
    return std::fabs(largest / smallest);
}

```

**Last Modified:** April/2019
