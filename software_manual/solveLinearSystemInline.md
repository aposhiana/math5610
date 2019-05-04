**Routine Name:** solveLinearSystemInline

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this overloaded function is to solve a linear system of equations by performing row reduction on the coefficient matrix then performing backsubstitution. Unlike `solveLinearSystem`, `solveLinearSystemInline` does not use the `rowReduce` and `backsub` routines, but rather does these operations in-line. The routine outputs the solution to the system of equations as a vector.

**Input:**
1. `A` : an Array of doubles of dimensionality n x n
2. `b` : an Array of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating a random coefficient matrix and b vector, printing them, finding the solution to the linear system using the routine, then printing the solution.
```
    std::cout << "Diagonally dominant coefficient matrix  A_3 to be solved: " << std::endl;
    DenseArray<double>* A_3 = new DenseArray<double>(3, 3);
    A_3->makeRandomDD(1.0, 10.0);
    A_3->print();

    std::cout << "b_3: " << std::endl;
    Vector<double>* b_3 = new Vector<double>(3);
    b_3->makeRandom(1.0, 10.0);
    b_3->print();

    std::cout << "x found for A_3 system:  " << std::endl;
    Vector<double> x_a3 = solveLinearSystemInline(*A_3, *b_3);
    x_a3.print();
```

Output from lines above:
```
    Diagonally dominant coefficient matrix  A_3 to be solved: 
    9.81712 7.15914 1.05711 
    7.10768 9.97901 2.8692 
    2.79929 6.74427 9.89667 
    b_3: 
    8.69537
    1.42704
    1.52729
    x found for A_3 system:  
    1.73375
    -1.23778
    0.507437
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& solveLinearSystemInline(DenseArray<double>& A, Vector<double>& b) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(A, b);
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
            double oldBVal = b(i);
            b.set(i, oldBVal - l * b(pivotIdx));
        }
    }
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    double x_n = b(lastIndex, 0) / A(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i, 0) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}
```

**Last Modified:** May/2019
