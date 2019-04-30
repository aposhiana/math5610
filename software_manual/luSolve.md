**Routine Name:** solveLinearDiagonalSystem

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute and return the solution to a linear system of equation using the LU factorization of the coefficient matrix and the corresponding b vector. This method requires that the LU factorization be done beforehand. This should be done with the `lu` method. See the docs for `lu` [here](./lu.md).

**Input:**
1. `L` : DenseArray of doubles of dimensionality n x n
2. `U` : DenseArray of doubles of dimensionality n x n
3. `b` : Vector of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system.

**Usage/Example:** The example below shows creating and printing a random 20 x 2 coefficient matrix and a correponding 20-dimensional b vector. The routine then is used to compute the approximate solution and the result is printed.

```
std::cout << "Diagonally dominant coefficient matrix  A_4 to be factorized: " << std::endl;
DenseArray<double>* A_4 = new DenseArray<double>(4, 4);
A_4->makeRandomDD(1.0, 10.0);
A_4->print();

std::cout << "b_4: " << std::endl;
Vector<double>* b_4 = new Vector<double>(4);
b_4->makeRandom(1.0, 10.0);
b_4->print();

DenseArray<double>* L_4 = new DenseArray<double>(4, 4);
DenseArray<double>* U_4 = new DenseArray<double>(4, 4);
lu(*A_4, *L_4, *U_4);

std::cout << "L from A_4 " << std::endl;
L_4->print();
std::cout << "U from A_4 " << std::endl;
U_4->print();

std::cout << "x_4 found with LU: " << std::endl;
Vector<double> x_4 = luSolve(*L_4, *U_4, *b_4);
x_4.print();
```

Output from lines above:
```
Diagonally dominant coefficient matrix  A_4 to be factorized: 
9.96091 3.29527 2.241 4.28352 
5.21036 8.50652 1.6363 1.28021 
1.49272 2.35297 9.44699 5.43542 
2.89544 1.17753 5.74822 9.95964
b_4: 
5.03083
3.98639
6.44668
1.31516
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
x_4 found with LU: 
0.516557
0.0612587
0.898478
-0.543923
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& luSolve(DenseArray<double>& L,
                DenseArray<double>& U, Vector<double>& b) {
    Vector<double> y = forwardsub(L, b);
    return backsub(U, y);
}
```

**Last Modified:** April/2019
