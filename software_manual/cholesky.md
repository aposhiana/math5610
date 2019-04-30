**Routine Name:** cholesky

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute the Cholesky factor for a symmetric, positive definite (SPD) matrix. This method overwrites the matrix A passed by reference with its Cholesky factor. The routine will fail if the matrix passed is not SPD.

**Input:**
1. `A` : Array of doubles

**Output:** None

**Usage/Example:** The example below shows creating a random SPD matrix, printing it, passing it `cholesky`, then printing it again showing the computed Cholesky factor for the SPD matrix.
```
std::cout << "SPD_1: " << std::endl;
Array<double>* SPD_1 = getRandomSPDArray(3);
SPD_1->print();

std::cout << "cholesky(SPD_1):  " << std::endl;
cholesky(*SPD_1);
SPD_1->print();
```

Output from lines above:
```
40.878 29.9492 48.3366 
29.9492 88.9145 43.8201 
48.3366 43.8201 71.2667 
cholesky(SPD_1):  
6.39359 0 0 
4.68425 8.18366 0 
7.56017 1.02721 3.61322 
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
void cholesky(Array<double>& A) {
    std::string errorMessage = "Matrix is not positive definite";
    unsigned int n = A.rowDim();
    unsigned int lastIndex = n - 1;
    for (unsigned int k = 0; k < (n - 1); k++) {
        double previousDiagVal = A(k, k);
        if (previousDiagVal < 0) {
            std::cout << errorMessage << std::endl;
            throw std::exception();
        }
        A.set(k, k, sqrt(previousDiagVal));
        for (unsigned int i = k + 1; i < n; i++) {
            A.set(i, k, A(i, k) / A(k, k));
        }
        for (unsigned int j = k + 1; j < n; j++) {
            for (unsigned int i = j; i < n; i++) {
                A.set(i, j, A(i, j) - A(i, k) * A(j, k));
            }
        }
    }
    double lastValSquared = A(lastIndex, lastIndex);
    if (lastValSquared < 0) {
        std::cout << errorMessage << std::endl;
        throw std::exception();
    }
    A.set(lastIndex, lastIndex, sqrt(lastValSquared));
    // Set upper part of matrix to zeros
    for (unsigned int i = 0; i < (n - 1); i++) {
        for (unsigned int j = i + 1; j < n; j++) {
            A.set(i, j, 0.0);
        }
    }
}
```

**Last Modified:** April/2019
