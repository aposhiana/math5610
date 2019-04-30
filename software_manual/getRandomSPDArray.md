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

**Usage/Example:** The example below shows using the routine to generate two SPD matrices, storing the matrices, then printing the matrices.
```
std::cout << "SPD_0: " << std::endl;
Array<double>* SPD_0 = getRandomSPDArray(10);
SPD_0->print();

std::cout << "SPD_1: " << std::endl;
Array<double>* SPD_1 = getRandomSPDArray(3);
SPD_1->print();
```

Output from lines above:
```
SPD_0: 
65.9553 76.7293 25.9813 1.62426 63.0469 18.2129 68.6218 18.9617 5.51316 37.1734 
76.7293 109.422 67.4883 3.01938 85.1327 41.3524 104.286 29.2715 12.7021 50.3935 
25.9813 67.4883 84.0626 9.11434 68.804 65.9524 94.3563 25.3357 27.2934 40.1536 
1.62426 3.01938 9.11434 64.284 48.6559 83.7491 37.8296 10.4888 68.1964 47.3344 
63.0469 85.1327 68.804 48.6559 172.752 146.082 185.448 50.3062 90.267 109.332 
18.2129 41.3524 65.9524 83.7491 146.082 205.64 178.638 96.4791 160.856 146.066 
68.6218 104.286 94.3563 37.8296 185.448 178.638 336.644 205.336 181.322 165.593 
18.9617 29.2715 25.3357 10.4888 50.3062 96.4791 205.336 213.74 163.133 125.729 
5.51316 12.7021 27.2934 68.1964 90.267 160.856 181.322 163.133 238.89 173.979 
37.1734 50.3935 40.1536 47.3344 109.332 146.066 165.593 125.729 173.979 222.498
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
