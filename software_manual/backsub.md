**Routine Name:** backsub

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to solve a linear system of equations with a square, upper triangular matrix. `backsub` is overloaded with one signature allowing a separate upper triangular matrix and b vector to be passed and another signature allowing an augmented coefficient matrix in reduced-row echelon form to be passed. The results of both signatures is the solution vector.

**Input:**
*Signature 1:*
1. `A` : an Array of doubles of dimensionality n x n in upper triangular form
2. `b` : an Array of doubles of dimensionality n x 1
*Signature 2:*
1. `AB` : an Array of doubles of dimensionality n x (n + 1) in reduced-row echelon form

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system.

**Usage/Example:** The example below shows creating a random upper triangular matrix and b vector, printing them, then using the routine to find the solution, then printing the solution. Then, a random n x (n + 1) matrix in augmented, reduced-row echelon form is created, printed, then passed to the routine to find the corresponding solution. The solution to this second system is also printed.
```
std::cout << "b for linear systems:  " << std::endl;
Vector<double>* b_ls = new Vector<double>(5);
b_ls->makeRandom(1, 10);
b_ls->print();

std::cout << "A for upper triangular linear system:  " << std::endl;
DenseArray<double>* A_utls = new DenseArray<double>(5);
A_utls->makeRandomUpperTriangular(1.0, 10.0);
A_utls->print();

std::cout << "x found for upper triangular system:  " << std::endl;
Vector<double> x_utls = backsub(*A_utls, *b_ls);
x_utls.print();

std::cout << "Random reduced row echelon coefficient matrix: " << std::endl;
DenseArray<double>* AB_0 = new DenseArray<double>(3, 4);
AB_0->makeRandomAugmentedEchelon(1.0, 10.0);
AB_0->print();

std::cout << "x found for random augmented reduced row echelon system:  " << std::endl;
Vector<double> x_rarre = backsub(*AB_0);
x_rarre.print();
```

Output from lines above:
```
b for linear systems:  
5.90804
6.87247
5.78029
2.49173
8.93167
A for upper triangular linear system:  
5.25826 4.67456 2.7089 3.46148 8.7139 
0 3.76656 3.91444 8.31905 9.39167 
0 0 8.11877 6.08071 4.59643 
0 0 0 7.49359 5.63984 
0 0 0 0 8.67052 
x found for upper triangular system:  
-0.311903
-0.24446
0.460391
-0.442775
1.03012
Random reduced row echelon coefficient matrix: 
9.54881 3.00172 9.73377 6.42128 
0 7.78201 2.2255 5.35295 
0 0 3.04027 5.90006 
x found for random augmented reduced row echelon system:  
-1.34753
0.13288
1.94064
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& backsub(Array<double>& A, Array<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
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

Vector<double>& backsub(Array<double>& AB) {
    assertLinearSystem(AB);
    unsigned int n = AB.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    // Note that column n of AB is b
    double x_n = AB(lastIndex, n) / AB(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += AB(i, j) * (*x)(j);
        }
        double x_i = (AB(i, n) - sum) / AB(i, i);
        x->set(i, x_i);
    }
    return *x;
}
```

**Last Modified:** April/2019
