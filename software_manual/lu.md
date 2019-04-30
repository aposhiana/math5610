**Routine Name:** lu

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to factorize the passed square matrix into its LU Decomposition. Aribitrary L and U matrices of the same dimensionality as A are passed by reference and the routine updates them to be the L and U matrices respectively from the factorization. Scaled partial pivoting is used in the factorization.

**Input:**
1. `A` : a DenseArray of doubles of dimensionality n x n
2. `L` : a DenseArray of doubles of dimensionality n x n
3. `U` : a DenseArray of doubles of dimensionality n x n

**Output:** None. The routine updates the L and U matrices passed by reference.

**Usage/Example:** The example below shows creating a random augmented coefficient matrix, printing it, finding the solution to the linear system using the routine, then printing the solution. Then, a random matrix and b vector are created, printed, and solved using the other signature of the routine. The solution to this system is also printed.
```
std::cout << "Diagonally dominant coefficient matrix  A_4 to be factorized: " << std::endl;
DenseArray<double>* A_4 = new DenseArray<double>(4, 4);
A_4->makeRandomDD(1.0, 10.0);
A_4->print();

DenseArray<double>* L_4 = new DenseArray<double>(4, 4);
DenseArray<double>* U_4 = new DenseArray<double>(4, 4);
lu(*A_4, *L_4, *U_4);

std::cout << "L from A_4 " << std::endl;
L_4->print();
std::cout << "U from A_4 " << std::endl;
U_4->print();
```

Output from lines above:
```
Diagonally dominant coefficient matrix  A_4 to be factorized: 
9.96091 3.29527 2.241 4.28352 
5.21036 8.50652 1.6363 1.28021 
1.49272 2.35297 9.44699 5.43542 
2.89544 1.17753 5.74822 9.95964
L from A_4 
1 0 0 0 
0.52308 1 0 0 
0.149857 0.274096 1 0 
0.29068 0.0323845 0.56565 1 
U from A_4 
9.96091 3.29527 2.241 4.28352 
0 6.78283 0.464075 -0.960413 
0 0 8.98396 5.05675 
0 0 0 5.88526
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
void lu(DenseArray<double>& A, DenseArray<double>& L, DenseArray<double>& U) {
    if (A.rowDim() != A.colDim()) {
        std::cout << "Matrix A is not square" << std::endl;
        throw std::exception();
    }
    assertSameDim(A, L);
    assertSameDim(A, U);
    unsigned int n = A.rowDim();
    // Initialize L and U to anything. Does not need to be identity.
    L.makeIdentity();
    U.makeIdentity();
    // Make U a copy of A
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            U.set(i, j, A(i, j));
        }
    }
    // Set s to the absolute maximum row values
    Vector<double>* s = new Vector<double>(n, true);
    for (unsigned int i = 0; i < n; i++) {
        double rowMaxAbs = -1; // Initialize to be impossibly low
        for (unsigned int j = 0; j < n; j++) {
            double valAbs = std::fabs(A(i, j));
            if (valAbs > rowMaxAbs) {
                rowMaxAbs = valAbs;
            }
        }
        s->set(i, rowMaxAbs);
    }
    // Initialize row index map
    unsigned int* rowMap = new unsigned int[n];
    for (unsigned int i = 0; i < n; i++) {
        rowMap[i] = i;
    }
    // Find permuted L and U
    for (unsigned int k = 0; k < n; k++) {
        // Choose pivot using scaled partial pivoting
        unsigned int q;
        double relMaxPivotAbs = -1; // Initialize to be impossibly low
        for (unsigned int i = k; i < n; i++) {
            // Examine the proper row desired at rowMap[i]
            double relPivotAbs = std::fabs(U(rowMap[i], k)) / (*s)(rowMap[i]);
            if (relPivotAbs > relMaxPivotAbs) {
                relMaxPivotAbs = relPivotAbs;
                q = i;
            }
        }
        // Exchange row indices in rowMap
        unsigned int temp = rowMap[k];
        rowMap[k] = rowMap[q]; // not just q because q is not permuted
        rowMap[q] = temp;

        double pivot = U(rowMap[k], k);
        for (unsigned int i = k + 1; i < n; i++) {
            double l = U(rowMap[i], k) / pivot;
            L.set(rowMap[i], k, l);
            U.set(rowMap[i], k, 0.0); // Fill zeros in lower part of U
            for (unsigned int j = k + 1; j < n; j++) {
                double oldVal = U(rowMap[i], j);
                U.set(rowMap[i], j, oldVal - l * U(rowMap[k], j));
            }
        }
    }
    // Copy L
    double** L_copy = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        L_copy[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            L_copy[i][j] = L(i, j);
        }
    }
    // Copy U
    double** U_copy = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        U_copy[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            U_copy[i][j] = U(i, j);
        }
    }
    // Put L and U in proper order and set trivial L values
    for (unsigned int i = 0; i < n; i++) {
        unsigned int oldRow = rowMap[i];
        for (unsigned int j = 0; j < n; j++) {
            if (j < i) {
                L.set(i, j, L_copy[oldRow][j]);
            }
            else if (j == i) {
                L.set(i, j, 1.0);
            }
            else {
                L.set(i, j, 0.0);
            }
            U.set(i, j, U_copy[oldRow][j]);
        }
    }
    // Clean up dynamically allocated raw arrays
    delete[] rowMap;
    for (unsigned int i = 0; i < n; i++) {
        delete[] L_copy[i];
        delete[] U_copy[i];
    }
    delete[] L_copy;
    delete[] U_copy;
}
```

**Last Modified:** April/2019
