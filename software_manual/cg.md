**Routine Name:** cg

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute and return an approximate solution to a linear system of equations where the coefficient matrix is symmetric and positive definite (SPD) using the iterative conjugate gradient (CG) method.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `b` : Vector of doubles of dimensionality n x 1

**Output:** A vector of doubles of dimensionality n x 1 representing the solution to the linear system

**Usage/Example:** The example below shows creating and printing a random SPD matrix and its corresponding b vector. This system of equations is then passed to the `cg` routine to find the approximate solution which is then printed.
```
std::cout << "A_spd_cg for Iterative methods: " << std::endl;
Array<double>* A_spd_cg = getRandomSPDArray(10);
A_spd_cg->print();

std::cout << "b_iterative for Iterative methods: " << std::endl;
Vector<double>* b_iterative = new Vector<double>(10);
b_iterative->makeRandom(1.0, 10.0);
b_iterative->print();

Vector<double>* x_spd_cg = cg(*A_spd_cg, *b_iterative, 0.1);
std::cout << "x_spd_cg found using CG: " << std::endl;
x_spd_cg->print();
```

Output from lines above:
```
A_spd_cg for Iterative methods: 
45.0943 29.8973 36.0866 6.68759 54.4357 46.5107 30.8269 14.9365 33.9853 46.2333 
29.8973 25.2823 42.8754 27.4863 38.3555 33.2295 21.6515 27.5837 30.7372 36.3498 
36.0866 42.8754 131.5 96.5005 62.2381 60.8052 76.5602 100.773 61.3977 73.9341 
6.68759 27.4863 96.5005 112.277 44.1488 29.8855 53.8071 97.7148 64.1656 50.7342 
54.4357 38.3555 62.2381 44.1488 144.363 104.484 123.75 106.777 131.556 126.774 
46.5107 33.2295 60.8052 29.8855 104.484 127.82 143.616 121.521 135.275 105.73 
30.8269 21.6515 76.5602 53.8071 123.75 143.616 293.091 180.327 212.483 162.64 
14.9365 27.5837 100.773 97.7148 106.777 121.521 180.327 336.557 260.646 198.077 
33.9853 30.7372 61.3977 64.1656 131.556 135.275 212.483 260.646 265.857 214.081 
46.2333 36.3498 73.9341 50.7342 126.774 105.73 162.64 198.077 214.081 331.977 
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
x_spd_cg found using CG: 
-454.694
704.706
-29.248
-146.91
57.7687
-37.8032
47.5239
24.1414
-53.8365
2.14131
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
Vector<double>* cg(Array<double>& A, Vector<double>& b, double tol) {
    assertLinearSystem(A, b);
    unsigned int n = A.rowDim();

    // Use raw array members for compatability with faster operations
    double** A_raw_member = A.getRawArray();
    double* b_raw_member = b.getRawArray()[0];

    // Initialize x randomly
    double* x = new double[n];
    for (unsigned int i = 0; i < n; i++) {
        x[i] = getRandDouble(-10.0, 10.0);
    }

    // Compute initial r
    double* Ax_0 = rawMatVecProduct(A_raw_member, x, n, n);
    double* r = rawSubtract(b_raw_member, Ax_0, n);

    // Set initial p to r
    double* p = new double[n];
    copyBintoA(p, r, n);

    // Allocate memory for the following
    double* s = new double[n];

    // Initialize end condition variables
    double delta = rawDot(r, r, n);
    double endConditionValue = tol * tol * rawDot(b_raw_member, b_raw_member, n);

    while (delta > endConditionValue) {
        // Update s
        double* Ap = rawMatVecProduct(A_raw_member, p, n, n);
        copyBintoA(s, Ap, n);
        delete[] Ap;
        Ap = nullptr;
        // Compute alpha
        double alpha = delta / rawDot(p, s, n);
        // Update x
        for (unsigned int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
        }
        // Update r
        for (unsigned int i = 0; i < n; i++) {
            r[i] -= alpha * s[i];
        }
        double delta_next = rawDot(r, r, n);
        // Update p
        for (unsigned int i = 0; i < n; i++) {
            p[i] = r[i] + (delta_next / delta) * p[i];
        }
        delta = delta_next;
    }
    // Clean up memory
    delete[] r;
    delete[] p;
    delete[] s;
    delete[] Ax_0;
    r = nullptr;
    p = nullptr;
    s = nullptr;
    Ax_0 = nullptr;

    double** x_array = new double*[1];
    x_array[0] = x;
    Vector<double>* xVector = new Vector<double>(x_array, n);
    return new Vector<double>(x_array, n);
}
```

**Last Modified:** April/2019
