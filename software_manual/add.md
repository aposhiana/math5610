**Routine Name:** add

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to take two pointers to Array objects, create a new Array for the elementwise sum of these Arrays, then return the pointer to the sum Array object. If the Arrays have only one column, then the returned pointer will be to Vector of doubles; otherwise a pointer to a DenseArray of doubles will be returned. Note that the two Array objects must be of the same dimensionality, otherwise an exception will be thrown.

**Input:**
1. `a` : a pointer to an Array of doubles
2. `b` : a pointer to an Array of doubles

**Output:** A pointer to an Array of doubles

**Usage/Example:** The example below shows creating, then adding two random vectors together, then printing the returned sum vector. Then, two matrices are created, added together, and the resulting sum matrix is printed.
```
std::cout << "Vector 1 to be added: " << std::endl;
Vector<double>* vtba1 = new Vector<double>(5);
vtba1->makeRandom(0, 9.6);
vtba1->print();

std::cout << "Vector 2 to be added: " << std::endl;
Vector<double>* vtba2 = new Vector<double>(5);
vtba2->makeRandom(0, 4.5);
vtba2->print();

std::cout << "Vector sum: " << std::endl;
Array<double>* vectorSum = add(vtba1, vtba2);
vectorSum->print();

std::cout << "Matrix 1 to be added: " << std::endl;
DenseArray<double>* mtba1 = new DenseArray<double>(3, 2);
mtba1->makeRandom(1.0, 4.3);
mtba1->print();

std::cout << "Matrix 2 to be added: " << std::endl;
DenseArray<double>* mtba2 = new DenseArray<double>(3, 2);
mtba2->makeRandom(0, 5.5);
mtba2->print();

std::cout << "Matrix sum: " << std::endl;
Array<double>* matrixSum = add(mtba1, mtba2);
matrixSum->print();
```

Output from lines above:
```
Vector 1 to be added: 
4.11999
9.4613
1.5935
7.54009
6.308
Vector 2 to be added: 
2.71158
1.97098
1.81883
0.56599
4.10176
Vector sum: 
6.83157
11.4323
3.41233
8.10608
10.4098
Matrix 1 to be added: 
3.00712 2.11775 
3.34903 3.29502 
3.0738 4.06497 
Matrix 2 to be added: 
5.37194 3.69908 
3.95449 1.16019 
1.82669 0.249536 
Matrix sum: 
8.37906 5.81683 
7.30353 4.45522 
4.90049 4.3145 
```

**Implementation/Code:**
See [ArrayUtils.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/ArrayUtils.cpp)
```
Array<double>* add(Array<double>* a, Array<double>* b) {
    assertSameDim(*a, *b);
    Array<double>* newArray = getResultArray(a->rowDim(), a->colDim());
    for (unsigned int i = 0; i < a->rowDim(); i++) {
        for (unsigned int j = 0; j < a->colDim(); j++) {
            newArray->set(i, j, (*a)(i, j) + (*b)(i, j));
        }
    }
    return newArray;
}
```

**Last Modified:** February/2019
