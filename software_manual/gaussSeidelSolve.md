**Routine Name:** gaussSeidelSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute and return an approximate solution to a linear system of equations using the iterative Gauss-Seidel method.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `b` : Vector of doubles of dimensionality n x 1
3. `tol` : double precision scalar used to stop before the maximum number of iterations if the relative norm of the residual is less than this tolerance.
4. `maxiter` : unsigned int representing the maximum number of iterations

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating and printing a random diagonally dominant matrix and its corresponding b vector. This system of equations is then passed to the `gaussSeidelSolve` routine to find the approximate solution which is then printed.
```
std::cout << "A_iterative for Iterative methods: " << std::endl;
DenseArray<double>* A_iterative = new DenseArray<double>(10, 10);
A_iterative->makeRandomDD(1.0, 30.0);
A_iterative->print();

std::cout << "b_iterative for Iterative methods: " << std::endl;
Vector<double>* b_iterative = new Vector<double>(10);
b_iterative->makeRandom(1.0, 10.0);
b_iterative->print();

Vector<double> x_iterative_gs = gaussSeidelSolve(*A_iterative, *b_iterative, 0, 100);
std::cout << "x_iterative_gs found using Gauss-Seidel: " << std::endl;
x_iterative_gs.print();
```

Output from lines above:
```
A_iterative for Iterative methods: 
29.9991 17.524 1.21238 1.03758 3.51751 1.01701 2.42751 1.00033 1.04397 1.21872 
2.71836 29.9464 1.0442 1.03837 9.75567 1.16513 1.82476 1.1738 3.78631 7.41332 
1.28348 1.02508 29.9885 7.83248 1.55777 12.7686 1.18412 1.09503 1.04271 2.16186 
1.15117 1.26494 8.70755 29.9986 6.80339 1.01018 1.14528 6.40501 1.00545 2.50552 
3.76276 1.00024 1.00015 1.08357 29.9999 1.00875 1.00037 17.6912 1.0145 2.43799 
1.63463 1.0016 13.4218 1.5414 1.10031 29.9973 4.27633 4.60758 1.19448 1.21745 
1.54575 4.09169 1.01563 11.8684 1.78925 1.08415 29.9955 1.11553 1.01948 6.46192 
1.39027 18.9632 1.06548 1.04438 3.11209 1.0001 1.04771 30 1.3754 1.00083 
21.384 1.0207 1.15569 1.14984 1.00252 1.05502 1.00662 1.2212 29.9983 1.0018 
1.46673 1.00104 1.00007 1.00316 1.07814 2.6902 1.00577 19.7186 1.03529 29.9997 
b_iterative for Iterative methods: 
8.14701
7.92322
4.05841
2.78245
9.0605
6.39101
7.99433
5.26431
7.42212
1.46569
x_iterative_gs found using Gauss-Seidel: 
0.131986
0.140872
0.046214
-0.0101691
0.243597
0.130543
0.222323
0.0365175
0.12613
-0.0197674
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& gaussSeidelSolve(Array<double>& A, Vector<double>& b,
                double tol, unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    double bNorm = l2Norm(b);
    Vector<double>* x = new Vector<double>(n);
    Vector<double>* r = new Vector<double>(n, true);
    r->makeZeros();
    x->makeRandom(-10.0, 10.0); // Random initial x
    bool stop = false;
    unsigned int k = 0;
    while (!stop && k < maxiter) {
        for (unsigned int i = 0; i < n; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A(i, j) * (*x)(j);
                }
            }
            r->set(i, b(i) - sum);
            x->set(i, ((*r)(i) / A(i, i)));
        }
        double resNorm = l2Norm(*r);
        if (resNorm <= tol * bNorm) {
            stop = true;
        }
        k++;
    }
    return *x;
}
```

**Last Modified:** April/2019
