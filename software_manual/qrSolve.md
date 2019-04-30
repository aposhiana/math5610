**Routine Name:** qrSolve

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

**Usage/Example:** The example below shows creating and printing a random diagonally dominant matrix and a corresponding b vector to form a system of equations. The matrix is then factorized into Q and R using the `squareModifiedGramSchmidt` routine. The Q and R matrices together with the b vector are then passed to `qrSolve` which finds the solution to the linear system of equations. The solution is then printed.

```
std::cout << "Diagonally dominant coefficient matrix  A_4 to be factorized: " << std::endl;
DenseArray<double>* A_4 = new DenseArray<double>(6, 6);
A_4->makeRandomDD(1.0, 100.0);
A_4->print();

std::cout << "b_4: " << std::endl;
Vector<double>* b_4 = new Vector<double>(6);
b_4->makeRandom(1.0, 5000.0);
b_4->print();

DenseArray<double>* Q_4 = new DenseArray<double>(6, 6, true);
DenseArray<double>* R_4 = new DenseArray<double>(6, 6, true);
squareModifiedGramSchmidt(*A_4, *Q_4, *R_4);
std::cout << "Q_4 from Modified Gram Schmidt" << std::endl;
Q_4->print();
std::cout << "R_4 from Modified Gram Schmidt" << std::endl;
R_4->print();

Vector<double> x_4_qr = qrSolve(*Q_4, *R_4, *b_4);

std::cout << "x_4 found with QR: " << std::endl;
x_4_qr.print();
```

Output from lines above:
```
Diagonally dominant coefficient matrix  A_4 to be factorized: 
99.3843 50.8895 6.3816 1.97297 35.9012 3.31576 
1.00417 99.9993 1.03081 93.481 1.00773 3.47521 
6.50062 17.29 99.7685 7.85632 5.01629 63.0003 
2.16062 25.294 58.1439 99.7897 10.1126 2.59532 
5.50635 1.18054 6.5196 48.6872 98.85 36.8761 
1.1465 1.86458 1.77663 44.5831 48.6883 99.178 
b_4: 
3997.34
1718.5
1091.87
4425.14
2361.57
308.452 
Q_4 from Modified Gram Schmidt
0.995996 -0.0227364 -0.0666578 -0.020173 -0.0504622 0.0088225 
0.0100634 0.962609 -0.230838 -0.0898801 0.108244 0.0141747 
0.0651471 0.133634 0.85268 -0.39336 0.279852 0.13336 
0.021653 0.2336 0.460429 0.607494 -0.565608 -0.209776 
0.0551829 -0.017122 0.0555121 0.512134 0.745607 -0.418771 
0.0114898 0.0121018 0.0114295 0.453268 0.177702 0.873247 
R_4 from Modified Gram Schmidt
99.7838 53.4527 14.5052 8.77732 42.3276 10.6724 
0 103.325 27.6719 114.007 2.08314 12.864 
0 0 111.561 34.1468 12.3516 57.0715 
0 0 0 94.2319 76.0486 40.2553 
0 0 0 0 76.3367 61.4908 
0 0 0 0 0 79.1 
x_4 found with QR: 
43.9102
-16.5029
19.1536
35.93
9.48533
-18.2384
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& qrSolve(DenseArray<double>& Q,
                DenseArray<double>& R, Vector<double>& b) {
    Array<double>* QT = transpose(&Q);
    Array<double>* c = matmul(QT, &b);
    return backsub(R, *c);
}
```

**Last Modified:** April/2019
