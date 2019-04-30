**Routine Name:** jacobiSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute and return an approximate solution to a linear system of equations using the iterative Jacobi method.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `b` : Vector of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating and printing a random diagonally dominant matrix and its corresponding b vector. This system of equations is then passed to the `jacobiSolve` routine to find the approximate solution which is then printed.
```
std::cout << "A_iterative for Iterative methods: " << std::endl;
DenseArray<double>* A_iterative = new DenseArray<double>(10, 10);
A_iterative->makeRandomDD(1.0, 30.0);
A_iterative->print();

std::cout << "b_iterative for Iterative methods: " << std::endl;
Vector<double>* b_iterative = new Vector<double>(10);
b_iterative->makeRandom(1.0, 10.0);
b_iterative->print();

Vector<double> x_iterative_ji = jacobiSolve(*A_iterative, *b_iterative, 10000);
std::cout << "x_iterative_ji found using Jacobi: " << std::endl;
x_iterative_ji.print();
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
x_iterative_ji found using Jacobi: 
0.134981
0.143866
0.049206
-0.00717388
0.246592
0.133538
0.225319
0.0395125
0.129126
-0.0167717
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>& jacobiSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    double* x = new double[n];
    // Randomly initialize x values
    for (unsigned int i = 0; i < n; i++) {
        x[i] = getRandDouble(-10, 10);
    }
    double* x_next = new double[n];

    for (unsigned int k = 0; k < maxiter; k++) {
        for (unsigned int i = 0; i < n; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A(i, j) * x[j];
                }
            }
            x_next[i] = (b(i) - sum) / A(i, i);
        }
        // Switch pointers. x must become x_next
        // and x_next can become anything as long as it has
        // distinct memory locations from x
        double* tempPtr = x;
        x = x_next;
        x_next = tempPtr;
        tempPtr = nullptr;
    }
    double** x_array = new double*[1];
    x_array[0] = x;
    Vector<double>* xVector = new Vector<double>(x_array, n);
    return *xVector;
}
```

**Last Modified:** April/2019
