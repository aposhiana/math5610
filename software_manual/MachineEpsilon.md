### Module: MachineEpsilon
To use any of the functions in this module, include the correct header file at the top of your file as follows:
```
#include "MachineEpsilon.hpp"
```

#### Routine: `getMachineEpsilon`
**Description/Purpose:** Find the smallest positive number (or machine epsilon) that your computer and compiler is capable of storing using single precision float.

**Input:** No parameters

**Output:** Single precision machine epsilon as a float

**Example usage:** This example shows calling the function and assigning the return value to the variable `epsilon`:
```
float epsilon = getMachineEpsilon();
std::cout << epsilon << std::endl;
```

Output from lines above:
```
1.4013e-45
```

#### Routine: `getDoubleMachineEpsilon`
**Description/Purpose:** Find the smallest positive number (or machine epsilon) that your computer and compiler is capable of storing using double precision float.

**Input:** No parameters

**Output:** Double precision machine epsilon as a double

**Example usage:** This example shows calling the function and assigning the return value to the variable `epsilon`:
```
double epsilon = getDoubleMachineEpsilon();
std::cout << epsilon << std::endl;
```
Output from lines above:
```
4.94066e-324
```