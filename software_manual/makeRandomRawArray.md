**Routine Name:** makeRandomRawArray

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "ArrayUtils.hpp"
```

**Description/Purpose:** The purpose of this function is to take row and column dimensions as parameters and return a 2D array with its elements set to random values between 0 and 1, or to values within another range as specified in the optional parameters passed to the function.

**Input:**
1. The row dimension for the matrix as an unsigned int.
2. The column dimension for the matrix as an unsigned int.
3. The minimum value as a double for the randomly genererated element values of the matrix. *This parameter is optional as it has a default value of 0.0.*
4. The maximum value as a double for the randomly genererated element values of the matrix. *This parameter is optional as it has a default value of 1.0.*

**Output:** A `double**`, or a pointer to a pointer to a double. This is a pointer to a dynamically allocated 2D array of doubles.

**Usage/Example:** The example below shows creating an array using makeRandomRawArray, using it to generate a `DenseArray<double>` object, then using the DenseArray print function to examine the random array generated. Note that in order to use `DenseArray<double>`, you must also have `#include "DenseArray.hpp"` at the top of your file.
```
const unsigned int ROWS = 5;
const unsigned int COLS = 10;
double** rawArray = makeRandomRawArray(ROWS, COLS);
DenseArray<double>* myArray = new DenseArray<double>(rawArray, ROWS, COLS);
myArray->print();
```

Output from lines above:
```
0.491514 0.875217 0.76747 0.860537 0.0535521 0.0505672 0.883368 0.767539 0.0289518 0.59302 
0.880328 0.678863 0.653947 0.883797 0.977863 0.951639 0.197883 0.825768 0.67595 0.686882 
0.430091 0.537408 0.220187 0.677213 0.92073 0.707707 0.426741 0.23151 0.993312 0.592504 
0.208672 0.151912 0.178928 0.244375 0.214975 0.0783916 0.527895 0.325154 0.861801 0.284715 
0.210722 0.600075 0.461867 0.605888 0.161792 0.24499 0.553436 0.602697 0.535197 0.0591219 
```

**Implementation/Code:**
See [ArrayUtils.cpp](../src/lib/ArrayUtils.cpp)

**Last Modified:** February/2019
