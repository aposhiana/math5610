**Routine Name:** relativeError

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "VectorNorms.hpp"
```

**Description/Purpose:** The purpose of this function is to take two doubles and return their relative error.

**Input:**
1. `x` : double
2. `y` : double

**Output:** A `double` representing the relative error between x and y.

**Usage/Example:** The example below shows assigning the value returned from the routine to the variable `relErr`, then printing `relErr`.
```
double relErr = relativeError(2.3, 2.5);
std::cout << "Relative error: " << relErr << std::endl;
```

Output from lines above:
```
Relative error: 0.0869565
```

**Implementation/Code:**
See [VectorNorms.cpp](https://github.com/aposhiana/math5610/blob/master/src/lib/VectorNorms.cpp)
```
double relativeError(const double x, const double y) {
    return absoluteError(x, y) / x;
}
```

**Last Modified:** February/2019
