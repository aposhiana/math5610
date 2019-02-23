**Routine Name:** getDoubleMachineEpsilon

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "MachineEpsilon.hpp"
```

**Description/Purpose:** Find the smallest positive number (or machine epsilon) that your computer and compiler is capable of storing using double precision float.

**Input:** No parameters

**Output:** Double precision machine epsilon as a double

**Usage/Example:** This example shows calling the function and assigning the return value to the variable `epsilon`:
```
double epsilon = getDoubleMachineEpsilon();
std::cout << epsilon << std::endl;
```

Output from lines above:
```
4.94066e-324
```

**Implementation/Code:**
See [MachineEpsilon.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/MachineEpsilon.cpp)
```
double getDoubleMachineEpsilon() {
    double epsilon = 1;
    double nextPossibleEpsilon = epsilon;
    while (nextPossibleEpsilon > 0) {
        epsilon = nextPossibleEpsilon;
        nextPossibleEpsilon /= 2;
    }
    return epsilon;
}
```

**Last Modified:** January/2019
