**Routine Name:** cross

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to compute the cross product of two 3D vectors.

**Input:**
1. `a` : a Vector of doubles
2. `b` : a Vector of doubles

**Output:** A vector of doubles representing the result of the cross product.

**Usage/Example:** The example below shows creating two random vectors, printing them, then computing and printing their cross product.
```
Vector<double>* vc1 = new Vector<double>(3);
vc1->makeRandom();
std::cout << "Vector 1 for cross product:" << std::endl;
vc1->print();

Vector<double>* vc2 = new Vector<double>(3);
vc2->makeRandom();
std::cout << "Vector 2 for cross product:" << std::endl;
vc2->print();

Vector<double> crossProductResult = cross(*vc1, *vc2);
std::cout << "Cross product:" << std::endl;
crossProductResult.print();
```

Output from lines above:
```
Vector 1 for cross product:
0.0100793
0.402976
0.812716
Vector 2 for cross product:
0.317736
0.196254
0.432708
Cross product:
0.0148725
0.253868
-0.126062
```

**Implementation/Code:**
See [ArrayUtils.cpp](../src/lib/ArrayUtils.cpp)
```
Vector<double>& cross(Vector<double>& a, Vector<double>& b) {
    if (a.rowDim() != 3 || b.rowDim() != 3) {
        std::cout << "Vectors must be 3-dimensional for cross product" << std::endl;
        throw std::exception();
    }
    Vector<double>* result = new Vector<double>(3, true);
    result->set(0, a(1) * b(2) - b(1) * a(2));
    result->set(1, a(2) * b(0) - b(2) * a(0));
    result->set(2, a(0) * b(1) - b(0) * a(1));
    return *result;
}
```

**Last Modified:** February/2019
