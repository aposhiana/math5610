**Routine Name:** powerEigenSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "EigenvalueSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to approximately compute the eigenvalue with the largest magnitude for a given square matrix using the power iteration method.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `tol` : double value representing the tolerance for the accuracy of the eigenvalue
3. `maxiter` : unsigned int value for the maximum number of iterations to do before stopping solver

**Output:** A double precision value representing the eigenvalue of largest magnitude found for the matrix A

**Usage/Example:** The example below shows creating a random symmetric and positive definite matrix, printing it, then using the routine to find its dominant eigenvalue. The eigenvalue found is then printed.
```
std::cout << "A_eig" << std::endl;
Array<double>* A_eig = getRandomSPDArray(3);
A_eig->print();
double A_eig_lambda = powerEigenSolve(*A_eig, 0.0001, 10000);
std::cout << "A_eig_lambda found using power method: " << A_eig_lambda << std::endl;
```

Output from lines above:
```
A_eig
12.7763 22.4189 13.4044 
22.4189 48.4419 34.3634 
13.4044 34.3634 27.032 
A_eig_lambda found using power method: 83.323
```

**Implementation/Code:**
See [EigenvalueSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/EigenvalueSolvers.cpp)
```
double powerEigenSolve(Array<double>& A, double tol, unsigned int maxiter) {
    unsigned int n = A.rowDim();
    double** A_raw_member = A.getRawArray();
    double error = 10 * tol;
    double lambda = 0.0;

    // Randomly initialize v
    double* v = new double[n];
    for (unsigned int i = 0; i < n; i++) {
        v[0] = getRandDouble(-10, 10);
    }
    // Get initial y
    double* y = rawMatVecProduct(A_raw_member, v, n, n);

    unsigned int k = 0;
    while (error > tol && k < maxiter) {
        // Copute l2 norm of y
        double sum = 0;
        for (unsigned int i = 0; i < n; i++) {
            sum += y[i] * y[i];
        }
        double y_norm = sqrt(sum);
        // Update v
        for (unsigned int i = 0; i < n; i++) {
            v[i] = y[i] / y_norm;
        }
        // Update y
        delete[] y;
        y = rawMatVecProduct(A_raw_member, v, n, n);

        double lambda_next = rawDot(v, y, n);
        error = std::fabs(lambda_next - lambda);
        lambda = lambda_next;
        k++;
    }
    delete[] v;
    delete[] y;
    return lambda;
}
```

**Last Modified:** April/2019
