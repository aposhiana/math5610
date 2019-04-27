#include <cmath>
#include <string>
#include <exception>

#include "LinearSolvers.hpp"
#include "ArrayUtils.hpp"

Vector<double>& solveLinearDiagonalSystem(Array<double>& A, Vector<double>& b) {
    assertLinearSystem(A, b);
    Vector<double>* x = new Vector<double>(b.rowDim(), true);
    for (unsigned int i = 0; i < x->rowDim(); i++) {
        double x_i = b(i) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& backsub(Array<double>& A, Array<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    double x_n = b(lastIndex, 0) / A(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i, 0) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& backsub(Array<double>& AB) {
    assertLinearSystem(AB);
    unsigned int n = AB.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    unsigned int lastIndex = n - 1;
    // Note that column n of AB is b
    double x_n = AB(lastIndex, n) / AB(lastIndex, lastIndex);
    x->set(lastIndex, x_n);
    // Note that the loop ends when i is negative
    for (int i = lastIndex - 1; i >= 0; i--) {
        double sum = 0.0;
        for (unsigned int j = i + 1; j < n; j++) {
            sum += AB(i, j) * (*x)(j);
        }
        double x_i = (AB(i, n) - sum) / AB(i, i);
        x->set(i, x_i);
    }
    return *x;
}

Vector<double>& forwardsub(Array<double>& A, Array<double>& b) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n, true);
    for (unsigned int i = 0; i < n; i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < i; j++) {
            sum += A(i, j) * (*x)(j);
        }
        double x_i = (b(i, 0) - sum) / A(i, i);
        x->set(i, x_i);
    }
    return *x;
}

void rowReduce(DenseArray<double>& A, Vector<double>& b) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(A, b);
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
            double oldBVal = b(i);
            b.set(i, oldBVal - l * b(pivotIdx));
        }
    }
}

void rowReduce(DenseArray<double>& AB) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(AB);
    unsigned int n = AB.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = AB(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = AB(i, pivotIdx) / pivot;
            AB.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < (n + 1); j++) {
                double oldVal = AB(i, j);
                AB.set(i, j, oldVal - l * AB(pivotIdx, j));
            }
        }
    }
}

// Changes A to U and whatever is passed to L to L
void lu(DenseArray<double>& A, DenseArray<double>& L) {
    assertSameDim(A, L);
    // TODO: Add scaled partial pivoting
    L.makeIdentity();
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            L.set(i, pivotIdx, l);
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
        }
    }
}

// Get Q and R for A using classical Gram-Schmidt
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
        for (int i = 0; i < (j - 1); i++) {
            // Set r_ij to dot(a_j, q_i)
            double r_ij = 0;
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                r_ij += A(rowIdx, j) * Q(rowIdx, i);
            }
            R.set(i, j, r_ij);
            // Set q_j to q_j - r_ij * q_i
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                Q.set(rowIdx, j, Q(rowIdx, j) - r_ij * Q(rowIdx, i));
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

// Get Q and R for A using modified Gram-Schmidt
void squareModifiedGramSchmidt(DenseArray<double>& A, DenseArray<double>& Q,
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
        for (int i = 0; i < (j - 1); i++) {
            // Set r_ij to dot(q_j, q_i)
            double r_ij = 0;
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                r_ij += Q(rowIdx, j) * Q(rowIdx, i);
            }
            R.set(i, j, r_ij);
            // Set q_j to q_j - r_ij * q_i
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                Q.set(rowIdx, j, Q(rowIdx, j) - r_ij * Q(rowIdx, i));
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

Vector<double>& solveLinearSystem(DenseArray<double>& A, Vector<double>& b) {
    rowReduce(A, b);
    return backsub(A, b);
}

Vector<double>& solveLinearSystem(DenseArray<double>& AB) {
    rowReduce(AB);
    return backsub(AB);
}

Vector<double>& luSolve(DenseArray<double>& L,
                DenseArray<double>& U, Vector<double>& b) {
    Vector<double> y = forwardsub(L, b);
    return backsub(U, y);
}

Vector<double>& qrSolve(DenseArray<double>& Q,
                DenseArray<double>& R, Vector<double>& b) {
    // std::cout << "qrSolve: " << std::endl; 
    Array<double>* QT = transpose(&Q);
    // std::cout << "QT: " << std::endl;
    // QT->print();
    Array<double>* c = matmul(QT, &b);
    // std::cout << "c: " << std::endl;
    // c->print();
    return backsub(R, *c);
}

// Takes a PD matrix A and changes it to be the Cholesky factor
void cholesky(Array<double>& A) {
    std::string errorMessage = "Matrix is not positive definite";
    unsigned int n = A.rowDim();
    unsigned int lastIndex = n - 1;
    for (unsigned int k = 0; k < (n - 1); k++) {
        double diagonalValueSquared = A(k, k);
        if (diagonalValueSquared < 0) {
            std::cout << errorMessage << std::endl;
            throw std::exception();
        }
        A.set(k, k, sqrt(diagonalValueSquared));
        for (unsigned int i = k + 1; i < n; i++) {
            A.set(i, k, A(i, k) / A(k, k));
        }
        for (unsigned int j = k + 1; j < n; j++) {
            for (unsigned int i = j; i < n; i++) {
                A.set(i, j, A(i, j) - A(i, k) * A(j, k));
            }
        }
    }
    double lastValSquared = A(lastIndex, lastIndex);
    if (lastValSquared < 0) {
        std::cout << errorMessage << std::endl;
        throw std::exception();
    }
    A.set(lastIndex, lastIndex, sqrt(lastValSquared));
    // Set upper part of matrix to zeros
    for (unsigned int i = 0; i < (n - 1); i++) {
        for (unsigned int j = i + 1; j < n; j++) {
            A.set(i, j, 0.0);
        }
    }
}

// Solve a least squares problem using the normal equation
Vector<double>& solveNormalEquation(Array<double>& A, Vector<double>& b) {
    Array<double>* AT = transpose(&A);
    Array<double>* B = matmul(AT, &A);
    Array<double>* y = matmul(AT, &b);
    cholesky(*B); // After this, B really should be named G
    Array<double>* GT = transpose(B);
    Vector<double> z = forwardsub(*B, *y);
    return backsub(*GT, z);
}

// Solve the linear system using Jacobi iteration
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
    Vector<double>* xVector = new Vector<double>(x, n);
    return *xVector;
}

// Solve the linear system iteratively using Gauss Seidel
Vector<double>& gaussSeidelSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n);
    x->makeRandom(-10.0, 10.0); // Random initial x
    for (unsigned int k = 0; k < maxiter; k++) {
        for (unsigned int i = 0; i < n; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A(i, j) * (*x)(j);
                }
            }
            x->set(i, (b(i) - sum) / A(i, i));
        }
    }
    return *x;
}
