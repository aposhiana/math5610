**Routine Name:** solveLinearSystem

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this overloaded function is to solve a linear system of equations by performing row reduction on the coefficient matrix then performing backsubstitution. `solveLinearSystem` is an overloaded routine with one signature taking an square coefficient matrix and its corresponding b vector, and the second signature taking an augmented coefficient matrix. Both signatures output the solution to the system of equations as a vector.

**Input:**
*Signature 1:*
1. `A` : an Array of doubles of dimensionality n x n
2. `b` : an Array of doubles of dimensionality n x 1
*Signature 2:*
1. `AB` : an Array of doubles of dimensionality n x (n + 1)

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating a random augmented coefficient matrix, printing it, finding the solution to the linear system using the routine, then printing the solution. Then, a random matrix and b vector are created, printed, and solved using the other signature of the routine. The solution to this system is also printed.
```
std::cout << "Random augmented coefficient matrix  AB_2 to be solved: " << std::endl;
DenseArray<double>* AB_2 = new DenseArray<double>(3, 4);
AB_2->makeRandom(1.0, 10.0);
AB_2->print();

std::cout << "x found for AB_2 system:  " << std::endl;
Vector<double> x_ab2 = solveLinearSystem(*AB_2);
x_ab2.print();

std::cout << "Diagonally dominant coefficient matrix  A_3 to be solved: " << std::endl;
DenseArray<double>* A_3 = new DenseArray<double>(3, 3);
A_3->makeRandomDD(1.0, 10.0);
A_3->print();

std::cout << "b_3: " << std::endl;
Vector<double>* b_3 = new Vector<double>(3);
b_3->makeRandom(1.0, 10.0);
b_3->print();

std::cout << "x found for A_3 system:  " << std::endl;
Vector<double> x_a3 = solveLinearSystem(*A_3, *b_3);
x_a3.print();
```

Output from lines above:
```
Random augmented coefficient matrix  AB_2 to be solved: 
6.20173 3.04831 3.79265 9.30464 
4.57124 2.29372 9.87234 8.97016 
4.07058 1.15689 9.72689 1.55465 
x found for AB_2 system:  
-2.35125
7.52667
0.248598
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
Vector<double>& solveLinearSystem(DenseArray<double>& A, Vector<double>& b) {
    rowReduce(A, b);
    return backsub(A, b);
}

Vector<double>& solveLinearSystem(DenseArray<double>& AB) {
    rowReduce(AB);
    return backsub(AB);
}
```

**Last Modified:** April/2019
