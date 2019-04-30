**Routine Name:** inverseEigenSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "EigenvalueSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to use the inverse iteration method to approximately compute the eigenvalue of the matrix with a magnitude closest to the alpha value passed.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `alpha` : double value used as the shift parameter in the inverse iteration algorithm
3. `tol` : double value representing the tolerance for the accuracy of the eigenvalue
4. `maxiter` : unsigned int value for the maximum number of iterations to do before stopping solver

**Output:** A double precision value representing the eigenvalue closest in magnitude to alpha for the matrix A

**Usage/Example:** The example below shows creating a random symmetric and positive definite matrix, printing it, then using the routine with an alpha of zero to find its eigenvalue with the smallest magnitude. The eigenvalue found is then printed.
```
std::cout << "A_eig" << std::endl;
Array<double>* A_eig = getRandomSPDArray(3);
A_eig->print();
double A_eig_smallest = inverseEigenSolve(*A_eig, 0, 0.000001, 10000);
std::cout << "A_eig_smallest found using inverse iteration: " << A_eig_smallest << std::endl;
```

Output from lines above:
```
A_eig
12.7763 22.4189 13.4044 
22.4189 48.4419 34.3634 
13.4044 34.3634 27.032 
A_eig_smallest found using inverse iteration: 0.0157423
```

**Implementation/Code:**
See [EigenvalueSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/EigenvalueSolvers.cpp)
```
double inverseEigenSolve(Array<double>& A, double alpha, double tol,
                unsigned int maxiter) {
    unsigned int n = A.rowDim();
    double** A_raw_member = A.getRawArray();

    // Get B = A - alpha * I
    double** B_raw_member = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        B_raw_member[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            B_raw_member[i][j] = A_raw_member[i][j];
            if (j == i) {
                B_raw_member[i][j] -= alpha;
            }
        }
    }
    DenseArray<double>* B = new DenseArray<double>(B_raw_member, n);
    DenseArray<double>* L = new DenseArray<double>(n);
    DenseArray<double>* U = new DenseArray<double>(n);
    lu(*B, *L, *U);

    // Initializations
    Vector<double>* v = new Vector<double>(n);
    v->makeRandom();
    double* v_raw_member = v->getRawArray()[0];
    double error = 10 * tol;
    double lambda = 0.0;
    double* y = nullptr;

    unsigned int k = 0;
    while (error > tol && k < maxiter) {
        Vector<double> v_tilda = luSolve(*L, *U, *v);
        double v_tilda_norm = l2Norm(v_tilda);

        // Update v
        for (unsigned int i = 0; i < n; i++) {
            v->set(i, v_tilda(i) / v_tilda_norm);
        }

        // Get next lambda
        if (y != nullptr) {
            delete[] y;
        }
        y = rawMatVecProduct(A_raw_member, v_raw_member, n, n);
        double lambda_next = rawDot(v_raw_member, y, n);

        // Update error, lambda, and k
        error = std::fabs(lambda_next - lambda);
        lambda = lambda_next;
        k++;
    }
    delete v;
    delete[] y;
    return lambda;
}
```

**Last Modified:** April/2019
