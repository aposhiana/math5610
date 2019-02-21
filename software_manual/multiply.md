**Routine Name:** multiply

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** This is an overloaded function. The first use of `multiply` is to multiply an Array object by a scalar. The second use of `multiply` is to multiply two Array objects elementwise (i.e. the Hadamard product). In both cases, the resulting Array is returned as a new Array. Note that if two Array objects are passed, then they must be of the same dimensionality, otherwise an exception will be thrown.

**Input:**
1. A double or a pointer to an Array of doubles
2. A pointer to an Array of doubles

**Output:** A pointer to an Array of doubles

**Usage/Example:** The example below shows multiplying a vector by a scalar and printing the returned vector, then multiplying two vectors together elementwise and printing that returned vector.
```
std::cout << "Test multiply by a scalar:" << std::endl;
const double SCALAR_CONST = 0.5;
DenseArray<double>* toScale = new DenseArray<double>(5, 5);
toScale->makeRandom();
std::cout << "Array to be scaled:" << std::endl;
toScale->print();

// Multiply array by scalar
Array<double>* scaledArray = multiply(SCALAR_CONST, toScale);

std::cout << "Array scaled by " << SCALAR_CONST << ":" << std::endl;
scaledArray->print();

std::cout << "Test elementwise multiplication of Vectors:" << std::endl;
Array<double>* vecToMult1 = new Vector<double>(4);
vecToMult1->setAll(3);
Array<double>* vecToMult2 = new Vector<double>(4);
vecToMult2->setAll(7);

// Elementwise multiply two arrays
Array<double>* vecProduct = multiply(vecToMult1, vecToMult2);

vecProduct->print();
```

Output from lines above:
```
Test multiply by a scalar:
Array to be scaled:
0.511361 0.439794 0.615418 0.322499 0.242159 
0.967718 0.437061 0.678504 0.617304 0.0255087 
0.725143 0.473234 0.639555 0.00720982 0.175527 
0.0746027 0.847045 0.278218 0.0142751 0.921693 
0.899001 0.512843 0.344937 0.348687 0.379236 
Array scaled by 0.5:
0.25568 0.219897 0.307709 0.16125 0.12108 
0.483859 0.21853 0.339252 0.308652 0.0127544 
0.362571 0.236617 0.319778 0.00360491 0.0877633 
0.0373013 0.423522 0.139109 0.00713755 0.460847 
0.449501 0.256421 0.172468 0.174343 0.189618 
Test elementwise multiplication of Vectors:
21
21
21
21
```

**Implementation/Code:**
See [ArrayUtils.cpp](../src/lib/ArrayUtils.cpp)

**Last Modified:** February/2019
