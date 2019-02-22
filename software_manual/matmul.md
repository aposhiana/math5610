**Routine Name:** matmul

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to take two pointers to Array objects, create a new Array for the product of these Arrays found by performing matrix multiplication, then return the pointer to the sum Array object.

**Input:**
1. `a` : a pointer to an Array of doubles
2. `b` : a pointer to an Array of doubles

**Output:** A pointer to an Array of doubles

**Usage/Example:** The example below shows instantiating two random Array objects, `ar1` and `ar2`, printing them, then calculating and printing the result of the `ar1` applied to `ar2`.
```
DenseArray<double>* ar1 = new DenseArray<double>(3, 2);
std::cout << "ar1:  " << std::endl;
ar1->makeRandom();
ar1->print();

DenseArray<double>* ar2 = new DenseArray<double>(2, 4);
std::cout << "ar2:  " << std::endl;
ar2->makeRandom();
ar2->print();

std::cout << "product:  " << std::endl;
Array<double>* product = matmul(ar1, ar2);
product->print();
```

Output from lines above:
```
ar1:  
0.719912 0.562211 
0.0728133 0.772749 
0.598174 0.50994 
ar2:  
0.563553 0.629004 0.67505 0.562745 
0.0475535 0.232085 0.6449 0.834371 
product:  
0.432443 0.583308 0.848546 0.874219 
0.0777811 0.225143 0.547499 0.685735 
0.361352 0.494603 0.732658 0.762098 
```

**Implementation/Code:**
See [ArrayUtils.cpp](../src/lib/ArrayUtils.cpp)

**Last Modified:** February/2019
