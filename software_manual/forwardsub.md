**Routine Name:** forwardsub

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to solve a linear system of equations with a square, lower triangular matrix.

**Input:**
1. `A` : an Array of doubles of dimensionality n x n in lower triangular form
2. `b` : an Array of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system.

**Usage/Example:** The example below shows creating a random lower triangular matrix and b vector, printing them, then using the routine to find the solution, then printing the solution.
```
std::cout << "b for lower triangular system:  " << std::endl;
Vector<double>* b_ls2 = new Vector<double>(3);
b_ls2->makeRandom(1, 10);
b_ls2->print();

std::cout << "A for lower triangular linear system:  " << std::endl;
DenseArray<double>* A_ltls = new DenseArray<double>(3);
A_ltls->makeRandomLowerTriangular(1.0, 10.0);
A_ltls->print();

std::cout << "x found for lower triangular system:  " << std::endl;
Vector<double> x_ltls = forwardsub(*A_ltls, *b_ls2);
x_ltls.print();
```

Output from lines above:
```
b for lower triangular system:  
2.95493
8.06455
2.80501
A for lower triangular linear system:  
1.1125 0 0 
7.96459 2.51124 0 
2.69732 2.91984 4.82572 
x found for lower triangular system:  
2.65612
-5.21272
2.25062
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& forwardsub(Array<double>& A, Array<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    for (unsigned int i = 0; i < n; i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < i; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i, 0) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}
```

**Last Modified:** April/2019
