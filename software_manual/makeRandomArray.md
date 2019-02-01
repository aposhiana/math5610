**Routine Name:** makeRandomArray

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

**Usage/Example:** This example shows creating an array using makeRandomArray, then using it to generate a `DenseArray<double>` object, then using the DenseArray print function to examine the random array generated:
```
const unsigned int ROWS = 5;
const unsigned int COLS = 10;
double** rawArray = makeRandomArray(ROWS, COLS);
DenseArray<double>* myArray = new DenseArray<double>(rawArray, ROWS, COLS);
myArray->print();
```

Output from lines above:
```
0.285376 0.311628 0.535702 0.539658 0.0357081 0.145803 0.51696 0.542986 0.959374 0.198643 
0.593339 0.24125 0.696061 0.698755 0.968462 0.945681 0.0530085 0.913187 0.937257 0.486612 
0.49613 0.450134 0.40278 0.524897 0.950626 0.178426 0.805538 0.674145 0.350498 0.812597 
0.322044 0.586428 0.0979698 0.577705 0.495407 0.303969 0.80632 0.822696 0.0437873 0.933255 
0.220479 0.593832 0.537695 0.0383735 0.943417 0.00325946 0.781673 0.584945 0.170185 0.305615 
```

**Implementation/Code:**
See [ArrayUtils.cpp]()

**Last Modified:** February/2019
