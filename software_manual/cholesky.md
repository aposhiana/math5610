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
SPD_0: 
512793 4.2916e+06 39265.8 1.29861e+06 2.8315e+06 3.50094e+06 4.4896e+06 4.6635e+06 1.8036e+06 6.85274e+06 
4.2916e+06 3.91127e+07 1.01134e+07 1.31035e+07 3.82276e+07 3.049e+07 5.20258e+07 5.53712e+07 1.60411e+07 6.39736e+07 
39265.8 1.01134e+07 5.46019e+07 1.28507e+07 5.3971e+07 3.90397e+07 5.95583e+07 9.19207e+07 1.21802e+07 5.75631e+07 
1.29861e+06 1.31035e+07 1.28507e+07 1.40953e+07 2.03298e+07 3.30736e+07 4.28597e+07 3.59743e+07 1.11655e+07 4.87463e+07 
2.8315e+06 3.82276e+07 5.3971e+07 2.03298e+07 9.31364e+07 5.42858e+07 1.01546e+08 1.41415e+08 2.31367e+07 9.42778e+07 
3.50094e+06 3.049e+07 3.90397e+07 3.30736e+07 5.42858e+07 2.05743e+08 1.29326e+08 2.30835e+08 1.2796e+08 1.7105e+08 
4.4896e+06 5.20258e+07 5.95583e+07 4.28597e+07 1.01546e+08 1.29326e+08 2.68043e+08 2.70992e+08 8.06228e+07 1.69133e+08 
4.6635e+06 5.53712e+07 9.19207e+07 3.59743e+07 1.41415e+08 2.30835e+08 2.70992e+08 4.32256e+08 1.6304e+08 2.2195e+08 
1.8036e+06 1.60411e+07 1.21802e+07 1.11655e+07 2.31367e+07 1.2796e+08 8.06228e+07 1.6304e+08 1.60286e+08 9.27365e+07 
6.85274e+06 6.39736e+07 5.75631e+07 4.87463e+07 9.42778e+07 1.7105e+08 1.69133e+08 2.2195e+08 9.27365e+07 2.52416e+08 
cholesky(SPD_0):  
716.096 0 0 0 0 0 0 0 0 0 
5993.06 1787.73 0 0 0 0 0 0 0 0 
54.8332 5473.29 4964.07 0 0 0 0 0 0 0 
1813.46 1250.38 1190.06 2797.66 0 0 0 0 0 0 
3954.08 8127.97 1866.92 276.818 2806.38 0 0 0 0 0 
4888.93 665.842 7076.3 5345.14 5292.27 8645.52 0 0 0 0 
6269.56 8084.02 3015.35 6360.14 1303.9 3592.4 9961.69 0 0 0 
6512.4 9141.2 8366.36 992.914 9075.93 9295.85 7979.92 1684.36 0 0 
2518.66 529.509 1842.02 1338.2 1804.67 9895.9 861.574 5825.64 3551.28 0 
9569.59 3704.44 7405.8 6414.97 3822.56 1720.37 491.201 1681.26 2901.94 4696.6 
SPD_1: 
3.67732e+06 9.09719e+06 4.03164e+06 
9.09719e+06 4.47393e+07 3.36482e+07 
4.03164e+06 3.36482e+07 8.50943e+07 
cholesky(SPD_1):  
1917.63 0 0 
4743.97 4715.3 0 
2102.41 5020.78 7447.55 
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
