**Routine Name:** solveNormalEquation

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute an approximate solution to the least squares problem using the Cholesky algorithm.

**Input:**
1. `A` : Array of doubles of dimensionality m x n
2. `b` : Vector of doubles of dimensionality m x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the least squares solution to the normal equation.

**Usage/Example:** The example below shows creating and printing a random 20 x 2 coefficient matrix and a correponding 20-dimensional b vector. The routine then is used to compute the approximate solution and the result is printed.

```
std::cout << "Random skinny matrix A_cnes: " << std::endl;
Array<double>* A_cnes = new DenseArray<double>(20, 2);
A_cnes->makeRandom(1.0, 10.0);
A_cnes->print();

std::cout << "Random vector b_cnes: " << std::endl;
Vector<double>* b_cnes = new Vector<double>(20);
b_cnes->makeRandom(1.0, 10.0);
b_cnes->print();

std::cout << "Least squares solution to A_cnes * x_cnes = b_nes" << std::endl;
Vector<double> x_cnes = solveNormalEquation(*A_cnes, *b_cnes);
x_cnes.print();
```

Output from lines above:
```
Random skinny matrix A_cnes: 
9.00985 8.704 
3.78072 9.9417 
8.00773 3.79882 
1.96372 6.66792 
1.78903 9.0274 
8.27321 8.98396 
9.31722 8.66039 
4.45092 4.57257 
4.24476 3.82774 
2.57821 2.26205 
5.18397 9.34018 
8.99638 8.52554 
9.50482 5.75061 
3.74137 7.30897 
4.1159 4.66586 
1.56087 3.12575 
3.36986 4.34159 
3.06745 1.37759 
7.14041 4.03117 
7.04551 7.92944 
Random vector b_cnes: 
3.05857
5.31872
6.9134
2.37578
3.97911
1.36432
5.94835
7.22387
4.19206
7.52656
8.48592
8.37604
6.86674
7.48229
6.90158
6.37157
3.2329
9.64295
3.68054
6.3488
Least squares solution to A_cnes * x_cnes = b_nes
0.478117
0.380605
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& solveNormalEquation(Array<double>& A, Vector<double>& b) {
    Array<double>* AT = transpose(&A);
    Array<double>* B = matmul(AT, &A);
    Array<double>* y = matmul(AT, &b);
    cholesky(*B); // After this, B really should be named G
    Array<double>* GT = transpose(B);
    Vector<double> z = forwardsub(*B, *y);
    return backsub(*GT, z);
}
```

**Last Modified:** April/2019
