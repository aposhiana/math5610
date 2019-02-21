**Routine Name:** infNorm

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "VectorNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take a Vector of doubles and return its Infinity Norm as a vector.

**Input:**
1. A vector of doubles

**Output:** A `double` representing the Infinity Norm of the input vector.

**Usage/Example:** The example below shows creating a random 2D vector and then printing its Infinity Norm.
```
std::cout << "random vec y: " << std::endl;
Vector<double>* y = new Vector<double>(2);
y->makeRandom();
y->print();

std::cout << "y infNorm: " << std::endl;
std::cout << infNorm(*y) << std::endl;
```

Output from lines above:
```
random vec y: 
0.707422
0.636478
y infNorm: 
0.707422
```

**Implementation/Code:**
See [VectorNorms.cpp](../src/lib/VectorNorms.cpp)

**Last Modified:** February/2019
