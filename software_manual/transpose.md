**Routine Name:** transpose

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to take a pointer to an Array of doubles, generate its transpose as a DenseArray of doubles and return the pointer to that transpose array.

**Input:**
1. `a` : a pointer to an Array of doubles

**Output:** A pointer to a DenseArray of doubles

**Usage/Example:** The example creating a random matrix, printing it, then printing its transpose, then creating a vector, printing it, then printing its transpose.
```
std::cout << "Matrix to be transposed:  " << std::endl;
DenseArray<double>* mtbt = new DenseArray<double>(4, 2);
mtbt->makeRandom(0, 9.5);
mtbt->print();
std::cout << "Transpose of matrix: " << std::endl;
DenseArray<double>* mtbtT = transpose(mtbt);
mtbtT->print();

std::cout << "Vector to be transposed:  " << std::endl;
Vector<double>* vtbt = new Vector<double>(4);
vtbt->makeRandom(-4, 10.5);
vtbt->print();
std::cout << "Transpose of vector:  " << std::endl;
DenseArray<double>* vtbtT = transpose(vtbt);
vtbtT->print();

```

Output from lines above:
```
Matrix to be transposed:  
9.13834 1.51839 
2.50612 6.77831 
8.57638 9.20652 
7.44328 3.28592 
Transpose of matrix: 
9.13834 2.50612 8.57638 7.44328 
1.51839 6.77831 9.20652 3.28592 
Vector to be transposed:  
0.61205
8.22195
3.2491
2.59823
Transpose of vector:  
0.61205 8.22195 3.2491 2.59823 
```

**Implementation/Code:**
See [ArrayUtils.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/ArrayUtils.cpp)
```
DenseArray<double>* transpose(Array<double>* a) {
    const unsigned int OLD_ROW_DIM = a->rowDim();
    const unsigned int OLD_COL_DIM = a->colDim();
    const unsigned int NEW_ROW_DIM = OLD_COL_DIM;
    const unsigned int NEW_COL_DIM = OLD_ROW_DIM;

    DenseArray<double>* aT = new DenseArray<double>(NEW_ROW_DIM, NEW_COL_DIM, true);
    for (unsigned int i = 0; i < NEW_ROW_DIM; i++) {
        for (unsigned int j = 0; j < NEW_COL_DIM; j++) {
            aT->set(i, j, (*a)(j, i));
        }
    }
    return aT;
}
```

**Last Modified:** February/2019
