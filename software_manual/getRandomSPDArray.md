**Routine Name:** getRandomSPDArray

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to generate a symmetric, positive definite (SPD) matrix of the dimensionality specified. Internally, this is done by generating a random Cholesky factor, then multiplying it by its transpose.

**Input:**
1. `dim` : unsigned int - the dimensionality for the Array to be returned.

**Output:** A pointer to an Array of doubles

**Usage/Example:** The example below shows using the routine to generate an SPD matrix, storing the matrix, then printing the matrix.
```
std::cout << "SPD_1: " << std::endl;
Array<double>* SPD_1 = getRandomSPDArray(3);
SPD_1->print();
```

Output from lines above:
```
SPD_1: 
4.63901 19.2474 15.0294 
19.2474 151.88 130.802 
15.0294 130.802 153.246
```

**Implementation/Code:**
See [ArrayUtils.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/ArrayUtils.cpp)
```
// Create and return a random SPD matrix
Array<double>* getRandomSPDArray(unsigned int dim) {
    DenseArray<double>* G = new DenseArray<double>(dim);
    G->makeRandomLowerTriangular(0.0, 10.0);
    DenseArray<double>* GT = transpose(G);
    return matmul(G, GT);
}
```

**Last Modified:** April/2019
