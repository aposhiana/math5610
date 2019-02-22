**Routine Name:** l2Norm

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "VectorNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take a Vector of doubles and return its L-2 Norm as a double.

**Input:**
1. A vector of doubles

**Output:** A `double` representing the L-2 Norm of the input vector.

**Usage/Example:** The example below shows creating a random 2D vector and then printing its L-2 Norm.
```
std::cout << "random vec y: " << std::endl;
Vector<double>* y = new Vector<double>(2);
y->makeRandom();
y->print();

std::cout << "y l2Norm: " << std::endl;
std::cout << l2Norm(*y) << std::endl;
```

Output from lines above:
```
random vec y: 
0.707422
0.636478
y l2Norm: 
0.951604
```

**Implementation/Code:**
See [VectorNorms.cpp](../src/lib/VectorNorms.cpp)

**Last Modified:** February/2019
