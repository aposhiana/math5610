**Routine Name:** getMachineEpsilon

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "MachineEpsilon.hpp"
```

**Description/Purpose:** Find the smallest positive number (or machine epsilon) that your computer and compiler is capable of storing using single precision float.

**Input:** No parameters

**Output:** Single precision machine epsilon as a float

**Usage/Example:** This example shows calling the function and assigning the return value to the variable `epsilon`:
```
float epsilon = getMachineEpsilon();
std::cout << epsilon << std::endl;
```

Output from lines above:
```
1.4013e-45
```

**Implementation/Code:**
See [MachineEpsilon.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/MachineEpsilon.cpp)
```
float getMachineEpsilon() {
    float epsilon = 1;
    float nextPossibleEpsilon = epsilon;
    while (nextPossibleEpsilon > 0) {
        epsilon = nextPossibleEpsilon;
        nextPossibleEpsilon /= 2;
    }
    return epsilon;
}
```

**Last Modified:** January/2019
