**Routine Name:** rayleighEigenSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "EigenvalueSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to approximately compute an eigenvalue for a given square matrix using the Rayleigh Quotient iteration method. Currently this routine will find a random eigenvalue for the matrix as a random initial v vector is selected.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `tol` : double value representing the tolerance for the accuracy of the eigenvalue
3. `maxiter` : unsigned int value for the maximum number of iterations to do before stopping solver

**Output:** A double precision value representing the eigenvalue found for the matrix A

**Usage/Example:** The example below shows creating a random symmetric and positive definite matrix, printing it, then using the routine to find an eigenvalue of the matrix. The eigenvalue found is then printed.
```
std::cout << "A_eig" << std::endl;
Array<double>* A_eig = getRandomSPDArray(3);
A_eig->print();
double A_eig_rayleigh = rayleighEigenSolve(*A_eig, 0.000001, 1000);
std::cout << "eigenvalue found with Rayleigh Quotient Iteration: " << A_eig_rayleigh << std::endl;
```

Output from lines above:
```
A_eig
12.7763 22.4189 13.4044 
22.4189 48.4419 34.3634 
13.4044 34.3634 27.032 
eigenvalue found with Rayleigh Quotient Iteration: 83.323
```

**Implementation/Code:**
See [EigenvalueSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/EigenvalueSolvers.cpp)
```
double rayleighEigenSolve(Array<double>& A, double tol, unsigned int maxiter) {
    unsigned int n = A.rowDim();
    double** A_raw_member = A.getRawArray();

    // Make B a copy of A
    double** B_raw_member = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        B_raw_member[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            B_raw_member[i][j] = A_raw_member[i][j];
        }
    }
    DenseArray<double>* B = new DenseArray<double>(B_raw_member, n);

    // Initialize empty L and U
    DenseArray<double>* L = new DenseArray<double>(n);
    DenseArray<double>* U = new DenseArray<double>(n);
    // Initialize v randomly
    Vector<double>* v = new Vector<double>(n);
    v->makeRandom();
    double* v_raw_member = v->getRawArray()[0];
    // Initialize lambda
    double* y = rawMatVecProduct(A_raw_member, v_raw_member, n, n);
    double lambda = rawDot(v_raw_member, y, n);

    double error = 10 * tol;
    unsigned int k = 0;
    while (error > tol && k < maxiter) {
        // Get new, shifted B
        for (unsigned int i = 0; i < n; i++) {
            B->set(i, i, A(i, i) - lambda);
        }
        lu(*B, *L, *U); // Get new L and U
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
