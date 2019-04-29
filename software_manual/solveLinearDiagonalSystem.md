**Routine Name:** solveLinearDiagonalSystem

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to solve a linear system of equations with a diagonal coefficient matrix.

**Input:**
1. `A` : an diagonal Array of doubles of dimensionality n x n
2. `b` : a Vector of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating a random diagonal matrix and b vector, printing them, then using the routine to find the solution. The solition is then printed.
```
std::cout << "b for linear systems:  " << std::endl;
Vector<double>* b_ls = new Vector<double>(5);
b_ls->makeRandom(1, 10);
b_ls->print();

std::cout << "A for diagonal linear system:  " << std::endl;
Array<double>* A_dls = multiply(2.0, &identity_arr);
A_dls->print();

std::cout << "x found for diagonal system:  " << std::endl;
Vector<double> x_dls = solveLinearDiagonalSystem(*A_dls, *b_ls);
x_dls.print();
```

Output from lines above:
```
b for linear systems:  
5.90804
6.87247
5.78029
2.49173
8.93167
A for diagonal linear system:  
2 0 0 0 0 
0 2 0 0 0 
0 0 2 0 0 
0 0 0 2 0 
0 0 0 0 2 
x found for diagonal system:  
2.95402
3.43624
2.89014
1.24587
4.46584
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& solveLinearDiagonalSystem(Array<double>& A, Vector<double>& b) {
    assertLinearSystem(A, b);
    Vector<double>* x = new Vector<double>(b.rowDim(), true);
    for (unsigned int i = 0; i < x->rowDim(); i++) {
        double x_i = b(i) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}
```

**Last Modified:** April/2019
