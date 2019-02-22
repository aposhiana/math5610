**Routine Name:** l2NormAbsoluteError

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "VectorNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take two Vector\<double\>objects and return the absolute error between them using the L-2 Norm.

**Input:**
1. `x` : a Vector of doubles
2. `y` : a Vector of doubles

**Output:** A `double` representing the absolute error between the two input Vector objects.

**Usage/Example:** The example below shows creating two random 2D vectors then printing the result of l2NormAbsoluteError when using these vectors as arguments.
```
std::cout << "random vec y: " << std::endl;
Vector<double>* y = new Vector<double>(2);
y->makeRandom();
y->print();

std::cout << "random vec yHat: " << std::endl;
Vector<double>* yHat = new Vector<double>(2);
yHat->makeRandom();
yHat->print();

std::cout << "l2NormAbsoluteError: " << std::endl;
std::cout << l2NormAbsoluteError(*y, *yHat) << std::endl;
```

Output from lines above:
```
random vec y: 
0.916321
0.606735
random vec yHat: 
0.390218
0.39075
l2NormAbsoluteError: 
0.568712
```

**Implementation/Code:**
See [VectorNorms.cpp](../src/lib/VectorNorms.cpp)

**Last Modified:** February/2019
