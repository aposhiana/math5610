**Routine Name:** inverseEigenJacobiSolve

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "EigenvalueSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to use the inverse iteration method to approximately compute the eigenvalue of the matrix with a magnitude closest to the alpha value passed. The `jacobiSolve` routine is used to solve the system of equations at each iteration in contrast to the `inverseEigenSolve` which utilizes the LU factorization with `luSolve` instead.

**Input:**
1. `A` : Array of doubles of dimensionality n x n
2. `alpha` : double value used as the shift parameter in the inverse iteration algorithm
3. `tol` : double value representing the tolerance for the accuracy of the eigenvalue
4. `maxiter` : unsigned int value for the maximum number of iterations to do before stopping solver

**Output:** A double precision value representing the eigenvalue closest in magnitude to alpha for the matrix A

**Usage/Example:** The example below shows creating a random diagonally dominant matrix, printing it, then using both the `inverseEigenSolve` as well as the `inverseEigenJacobiSolve` routines with an alpha of zero to find the eigenvalue with the smallest magnitude. The eigenvalue outputs for both routines are then printed for comparison.
```
    std::cout << "A_eig" << std::endl;
    DenseArray<double>* A_eig = new DenseArray<double>(10);
    A_eig->makeRandomDD(-50, 50);
    A_eig->print();

    double A_eig_smallest = inverseEigenSolve(*A_eig, 0, 0.000001, 10000);
    std::cout << "A_eig_smallest found using inverse iteration: " << A_eig_smallest << std::endl;
    double A_eig_smallest_jacobi = inverseEigenJacobiSolve(*A_eig, 0, 0.000001, 1000);
    std::cout << "JACOBI VERSION OF ABOVE: " << A_eig_smallest_jacobi << std::endl;
```

Output from lines above:
```
A_eig
49.9682 -2.00423 -4.02119 1.18456 -30.3778 -10.7419 0.0113967 0.436805 -1.09069 0.0951809 
0.403078 -49.9997 -0.0133258 -0.00458982 3.60306 38.537 0.0107785 7.3284 -0.0378835 -0.0610904 
0.00881484 5.67871 -49.9924 -3.99903 -11.9748 -6.60227 -19.3211 -0.0905076 2.19129 -0.120727 
7.87075 -9.715 0.920927 -49.9937 -1.50093 -0.224375 -0.0486429 0.203209 0.18963 29.3134 
10.3058 0.0206234 -0.0219472 -26.279 -49.9938 -11.689 0.0077431 -0.00154467 -1.63933 0.0207155 
-12.155 0.00182535 -9.1637 12.1002 -1.55488 49.934 -2.24988 -7.28584 -0.265092 5.14803 
10.292 -8.0992 19.5604 -6.97194 0.919467 -3.28058 49.9895 0.797361 -0.0431499 -0.00668013 
-35.3524 -1.32791 8.616 -0.22493 0.0127801 -0.433488 0.137246 49.9559 -0.717942 -3.10983 
-0.804766 8.79111 -19.8088 0.0838528 0.227876 0.0568067 -0.0104994 -17.7161 -49.9851 2.47855 
0.0393431 8.8058e-06 -5.10598 -1.9049e-06 -44.5803 5.41254e-06 -0.0753244 -0.000748714 0.198262 -50 
A_eig_smallest found using inverse iteration: -16.4099
JACOBI VERSION OF ABOVE: -16.4099
```

**Implementation/Code:**
See [EigenvalueSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/EigenvalueSolvers.cpp)
```
double inverseEigenJacobiSolve(Array<double>& A, double alpha, double tol,
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

    // Initializations
    Vector<double>* v = new Vector<double>(n);
    v->makeRandom();
    double* v_raw_member = v->getRawArray()[0];
    double error = 10 * tol;
    double lambda = 0.0;
    double* y = nullptr;

    unsigned int k = 0;
    while (error > tol && k < maxiter) {
        Vector<double> v_tilda = jacobiSolve(*B, *v, 1e-6, 1000);
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
