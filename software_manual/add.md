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

**Usage/Example:** The example below shows adding two vectors together and printing the returned sum vector.
```
Array<double>* vec = new Vector<double>(vecRows);
vec->makeOnes();

Array<double>* vec2 = new Vector<double>(vecRows);
vec2->setAll(11);

Array<double>* sum = add(vec, vec2);
sum->print();
```

Output from lines above:
```
Test add: 
12
12
12
12
12
12
12
12
```

**Implementation/Code:**
See [ArrayUtils.cpp](../src/lib/ArrayUtils.cpp)
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
