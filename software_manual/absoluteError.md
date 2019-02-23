**Routine Name:** absoluteError

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "VectorNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take two doubles and return their absolute error.

**Input:**
1. `x` : double
2. `y` : double

**Output:** A `double` representing the absolute error between x and y.

**Usage/Example:** The example below shows assigning the value returned from the routine to the variable `absErr`, then printing `absErr`.
```
double absErr = absoluteError(2.3, 2.5);
std::cout << "Absolute error: " << absErr << std::endl;
```

Output from lines above:
```
Absolute error: 0.2
```

**Implementation/Code:**
See [VectorNorms.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/VectorNorms.cpp)
```
double absoluteError(const double x, const double y) {
    return abs(x - y);
}
```

**Last Modified:** February/2019
