**Routine Name:** squareClassicalGramSchmidt

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this function is to compute the QR factorization for a given square matrix. Aribitrary Q and R matrices of the same dimensionality as A are passed by reference and the routine updates them to be the Q and R matrices respectively from the factorization.

**Input:**
1. `A` : a DenseArray of doubles of dimensionality n x n
2. `Q` : a DenseArray of doubles of dimensionality n x n
3. `R` : a DenseArray of doubles of dimensionality n x n

**Output:** None. The routine updates the Q and R matrices passed by reference.

**Usage/Example:** The example below shows creating a random matrix, printing it, then creating arbitrary matrices Q and R, then performing Gram-Schmidt with the routine. The resulting Q and R matrices are then printed.
```
std::cout << "A_gs1 for Gram-Schmidt" << std::endl;
DenseArray<double>* A_gs1 = new DenseArray<double>(5, 5);
A_gs1->makeRandom(1.0, 10.0);
A_gs1->print();

DenseArray<double>* Q_c_gs1 = new DenseArray<double>(5, 5, true);
DenseArray<double>* R_c_gs1 = new DenseArray<double>(5, 5, true);
squareClassicalGramSchmidt(*A_gs1, *Q_c_gs1, *R_c_gs1);
std::cout << "Q_c_gs1 from Classical Gram Schmidt" << std::endl;
Q_c_gs1->print();
std::cout << "R_c_gs1 from Classical Gram Schmidt" << std::endl;
R_c_gs1->print();
```

Output from lines above:
```
A_gs1 for Gram-Schmidt
1.05033 6.78277 2.7045 4.43182 3.10835 
4.10858 5.117 2.95153 7.43899 6.8611 
9.98356 7.27243 8.5063 6.73243 8.25434 
6.75969 2.35753 6.94778 6.59697 7.95173 
9.31632 9.46228 5.07635 7.09901 3.81605 
Q_c_gs1 from Classical Gram Schmidt
0.0664098 0.817991 0.527539 -0.109907 -0.19001 
0.259776 0.242038 -0.0764747 0.817011 0.44786 
0.631236 -0.124734 0.224922 -0.456267 0.572025 
0.427399 -0.438921 0.509805 0.321965 -0.510995 
0.589048 0.253176 -0.636682 -0.0925831 -0.418316 
R_c_gs1 from Classical Gram Schmidt
15.8159 12.9517 12.2755 13.4777 12.8456 
0 7.24049 0.101292 3.48769 0.649601 
0 0 3.42426 2.12669 4.59588 
0 0 0 3.98561 3.70465 
0 0 0 0 1.54427 
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
void squareClassicalGramSchmidt(DenseArray<double>& A, DenseArray<double>& Q,
                DenseArray<double>& R) {
    assertSameDim(A, Q);
    assertSameDim(Q, R);
    unsigned int n = A.colDim();
    if (n != A.rowDim()) {
        std::cout << "Matrix is not square" << std::endl;
        throw std::exception();
    }
    R.makeIdentity(); // Make lower part of R zeros
    // Don't use unsigned int for j and i because j - 1 condition
    // for i loop can be negative
    for (int j = 0; j < n; j++) {
        // Set q_j to a_j
        for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
            Q.set(rowIdx, j, A(rowIdx, j));
        }
        for (int i = 0; i < j; i++) {
            // Set r_ij to dot(a_j, q_i)
            double r_ij = 0;
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                r_ij += A(rowIdx, j) * Q(rowIdx, i);
            }
            R.set(i, j, r_ij);
            // Set q_j to q_j - r_ij * q_i
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                Q.set(rowIdx, j, Q(rowIdx, j) - (r_ij * Q(rowIdx, i)));
            }
        }
        // Set r_jj to the l2 norm of q_j
        double q_j_norm = 0;
        for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
            q_j_norm += Q(rowIdx, j) * Q(rowIdx, j);
        }
        q_j_norm = sqrt(q_j_norm);
        double r_jj = q_j_norm;
        R.set(j, j, r_jj);

        // Set q_j to q_j / r_jj
        for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
            Q.set(rowIdx, j, Q(rowIdx, j) / r_jj);
        }
    }
}
```

**Last Modified:** April/2019
