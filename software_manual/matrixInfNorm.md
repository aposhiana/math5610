**Routine Name:** matrixInfNorm

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "MatrixNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take an Array of doubles and return its infinity-norm as a double.

**Input:**
1. An Array object of doubles

**Output:** A `double` representing the infinity-norm of the input matrix.

**Usage/Example:** The example below shows creating a random Array and then printing its infinity-norm.
```
DenseArray<double>* normishArray = new DenseArray<double>(3, 2);
normishArray->makeRandom();
std::cout << "Matrix to be normed: " << std::endl;
normishArray->print();
std::cout << "Matrix infinity-norm: " << std::endl;
std::cout << matrixInfNorm(*normishArray) << std::endl;
```

Output from lines above:
```
Matrix to be normed:
0.340845 0.587686 
0.233252 0.268417 
0.291312 0.0755311 
Matrix infinity-norm: 
0.928531
```

**Implementation/Code:**
See [MatrixNorms.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/MatrixNorms.cpp)
```
double matrixInfNorm(Array<double>& a) {
    // -1 will always be less than any sum
    double maxRowL1Norm = -1;
    for (unsigned int i = 0; i < a.rowDim(); i++) {
        double rowL1Norm = 0;
        for (unsigned int j = 0; j < a.colDim(); j++) {
            rowL1Norm += abs(a(i, j));
        }
        if (rowL1Norm > maxRowL1Norm) {
            maxRowL1Norm = rowL1Norm;
        }
    }
    return maxRowL1Norm;
}

```

**Last Modified:** February/2019
