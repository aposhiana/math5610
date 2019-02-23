**Routine Name:** dot

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to compute the dot product of two vectors of the same length.

**Input:**
1. `a` : a Vector of doubles
2. `b` : a Vector of doubles

**Output:** The result of the dot product as a double.

**Usage/Example:** The example below shows creating two random vectors, printing them, then computing and printing their dot product.
```
Vector<double>* v1 = new Vector<double>(3);
v1->makeRandom();
std::cout << "Vector 1 for dot product:" << std::endl;
v1->print();

Vector<double>* v2 = new Vector<double>(3);
v2->makeRandom();
std::cout << "Vector 2 for dot product:" << std::endl;
v2->print();

std::cout << "Dot product: " << dot(*v1, *v2) << std::endl;
```

Output from lines above:
```
Vector 1 for dot product:
0.0738768
0.648028
0.407075
Vector 2 for dot product:
0.709332
0.750513
0.876676
Dot product: 0.89563
```

**Implementation/Code:**
See [ArrayUtils.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/ArrayUtils.cpp)
```
double dot(Vector<double>& a, Vector<double>& b) {
    assertSameDim(a, b);
    double result = 0;
    for (unsigned int i = 0; i < a.rowDim(); i++) {
        result += a(i) * b(i);
    }
    return result;
}
```

**Last Modified:** February/2019
