#include <cmath>
#include <string>
#include <exception>

#include "LinearSolvers.hpp"
#include "ArrayUtils.hpp"
#include "VectorNorms.hpp"

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

void rowReduce(DenseArray<double>& AB, bool isLinearSystem) {
    // TODO: Add scaled partial pivoting
    if (isLinearSystem) {
        assertLinearSystem(AB);
    }
    unsigned int n = AB.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = AB(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = AB(i, pivotIdx) / pivot;
            AB.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < AB.colDim(); j++) {
                double oldVal = AB(i, j);
                AB.set(i, j, oldVal - l * AB(pivotIdx, j));
            }
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

Vector<double>& solveLinearSystemInline(DenseArray<double>& A, Vector<double>& b) {
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

// Get the LU factorization for A. L and U passed must simply have correct
// dimensionality
void lu(DenseArray<double>& A, DenseArray<double>& L, DenseArray<double>& U) {
    if (A.rowDim() != A.colDim()) {
        std::cout << "Matrix A is not square" << std::endl;
        throw std::exception();
    }
    assertSameDim(A, L);
    assertSameDim(A, U);
    unsigned int n = A.rowDim();
    // Initialize L and U to anything. Does not need to be identity.
    L.makeIdentity();
    U.makeIdentity();
    // Make U a copy of A
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            U.set(i, j, A(i, j));
        }
    }
    // Set s to the absolute maximum row values
    Vector<double>* s = new Vector<double>(n, true);
    for (unsigned int i = 0; i < n; i++) {
        double rowMaxAbs = -1; // Initialize to be impossibly low
        for (unsigned int j = 0; j < n; j++) {
            double valAbs = std::fabs(A(i, j));
            if (valAbs > rowMaxAbs) {
                rowMaxAbs = valAbs;
            }
        }
        s->set(i, rowMaxAbs);
    }
    // Initialize row index map
    unsigned int* rowMap = new unsigned int[n];
    for (unsigned int i = 0; i < n; i++) {
        rowMap[i] = i;
    }
    // Find permuted L and U
    for (unsigned int k = 0; k < n; k++) {
        // Choose pivot using scaled partial pivoting
        unsigned int q;
        double relMaxPivotAbs = -1; // Initialize to be impossibly low
        for (unsigned int i = k; i < n; i++) {
            // Examine the proper row desired at rowMap[i]
            double relPivotAbs = std::fabs(U(rowMap[i], k)) / (*s)(rowMap[i]);
            if (relPivotAbs > relMaxPivotAbs) {
                relMaxPivotAbs = relPivotAbs;
                q = i;
            }
        }
        // Exchange row indices in rowMap
        unsigned int temp = rowMap[k];
        rowMap[k] = rowMap[q]; // not just q because q is not permuted
        rowMap[q] = temp;

        double pivot = U(rowMap[k], k);
        for (unsigned int i = k + 1; i < n; i++) {
            double l = U(rowMap[i], k) / pivot;
            L.set(rowMap[i], k, l);
            U.set(rowMap[i], k, 0.0); // Fill zeros in lower part of U
            for (unsigned int j = k + 1; j < n; j++) {
                double oldVal = U(rowMap[i], j);
                U.set(rowMap[i], j, oldVal - l * U(rowMap[k], j));
            }
        }
    }
    // Copy L
    double** L_copy = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        L_copy[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            L_copy[i][j] = L(i, j);
        }
    }
    // Copy U
    double** U_copy = new double*[n];
    for (unsigned int i = 0; i < n; i++) {
        U_copy[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) {
            U_copy[i][j] = U(i, j);
        }
    }
    // Put L and U in proper order and set trivial L values
    for (unsigned int i = 0; i < n; i++) {
        unsigned int oldRow = rowMap[i];
        for (unsigned int j = 0; j < n; j++) {
            if (j < i) {
                L.set(i, j, L_copy[oldRow][j]);
            }
            else if (j == i) {
                L.set(i, j, 1.0);
            }
            else {
                L.set(i, j, 0.0);
            }
            U.set(i, j, U_copy[oldRow][j]);
        }
    }
    // Clean up dynamically allocated raw arrays
    delete[] rowMap;
    for (unsigned int i = 0; i < n; i++) {
        delete[] L_copy[i];
        delete[] U_copy[i];
    }
    delete[] L_copy;
    delete[] U_copy;
}

Vector<double>& luSolve(DenseArray<double>& L,
                DenseArray<double>& U, Vector<double>& b) {
    Vector<double> y = forwardsub(L, b);
    return backsub(U, y);
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
    R.makeZeros(); // Make lower part of R zeros
    // Don't use unsigned int for j and i because j - 1 condition
    // for i loop can be negative
    for (int j = 0; j < n; j++) {
        // Set q_j to a_j
        for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
            Q.set(rowIdx, j, A(rowIdx, j));
        }
        for (int i = 0; i < j; i++) {
            // Set r_ij to dot(q_j, q_i)
            double r_ij = 0;
            for (unsigned int rowIdx = 0; rowIdx < n; rowIdx++) {
                r_ij += Q(rowIdx, j) * Q(rowIdx, i);
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

Vector<double>& qrSolve(DenseArray<double>& Q,
                DenseArray<double>& R, Vector<double>& b) {
    Array<double>* QT = transpose(&Q);
    Array<double>* c = matmul(QT, &b);
    return backsub(R, *c);
}

// Takes a PD matrix A and changes it to be the Cholesky factor
void cholesky(Array<double>& A) {
    std::string errorMessage = "Matrix is not positive definite";
    unsigned int n = A.rowDim();
    unsigned int lastIndex = n - 1;
    for (unsigned int k = 0; k < (n - 1); k++) {
        double previousDiagVal = A(k, k);
        if (previousDiagVal < 0) {
            std::cout << errorMessage << std::endl;
            throw std::exception();
        }
        A.set(k, k, sqrt(previousDiagVal));
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
                double tol, unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    double* x = new double[n];
    // Randomly initialize x values
    for (unsigned int i = 0; i < n; i++) {
        x[i] = getRandDouble(-10, 10);
    }
    double* x_next = new double[n];
    // Use residual to estimate error and implement early stopping
    double* r = new double[n];

    bool stop = false;
    unsigned int k = 0;
    while (!stop && k < maxiter) {
        for (unsigned int i = 0; i < n; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A(i, j) * x[j];
                }
            }
            r[i] = (b(i) - (sum + A(i, i) * x[i]));
            x_next[i] = (b(i) - sum) / A(i, i);
        }
        // Compute norm of residual for possible early stopping
        double resNorm = 0.0;
        for (unsigned int i = 0; i < n; i++) {
            resNorm += r[i] * r[i];
        }
        resNorm = sqrt(resNorm);
        // Print norm of residual at current step
        // if (k % 1 == 0) {
        //     std::cout << "JI resNorm " << resNorm << std::endl;
        // }

        if (resNorm <= tol) {
            stop = true;
        }

        // Switch pointers. x must become x_next
        // and x_next can become anything as long as it has
        // distinct memory locations from x
        double* tempPtr = x;
        x = x_next;
        x_next = tempPtr;
        tempPtr = nullptr;
        k++;
    }
    // Report final k
    // std::cout << "Final number of iterations for Jacobi: " << k << std::endl;

    double** x_array = new double*[1];
    x_array[0] = x;
    Vector<double>* xVector = new Vector<double>(x_array, n);
    return *xVector;
}

// Solve the linear system iteratively using Gauss Seidel
Vector<double>& gaussSeidelSolve(Array<double>& A, Vector<double>& b,
                double tol, unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    Vector<double>* x = new Vector<double>(n);
    // Use residual to estimate error and implement early stopping
    Vector<double>* r = new Vector<double>(n, true);
    r->makeZeros(); // Initialize residual to something
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
            r->set(i, b(i) - (sum + A(i, i) * (*x)(i)));
            x->set(i, ((b(i) - sum) / A(i, i)));
        }
        // Compute norm of residual for possible early stopping
        double resNorm = l2Norm(*r);
        // Print norm of residual at current step
        // if (k % 1 == 0) {
        //     std::cout << "GS resNorm " << resNorm << std::endl;
        // }

        if (resNorm <= tol) {
            stop = true;
        }
        k++;
    }
    // Report final k
    // std::cout << "Final number of iterations for Gauss Seidel: " << k << std::endl;

    return *x;
}

// Solve the linear system iteratively using steepest descent
Array<double>* steepestDescentSolve(Array<double>& A, Vector<double>& b,
                unsigned int maxiter) {
    assertLinearSystem(A, b);
    unsigned int n = b.rowDim();
    // Get random initial x
    Array<double>* x = new Vector<double>(n);
    x->makeRandom(-10.0, 10.0);
    // Get first r
    Array<double>* r = subtract(&b, matmul(&A, x));
    // Used for properly deleting the last iteration x and r
    Array<double>* tempVectorPtr = nullptr;

    // TODO: redo this so it is not constantly allocating new memory
    // Either use raw arrays or reimplement matmul, add, multiply, and subtract
    // to have in-place options or ability to pass return Arrays
    for (unsigned int k = 0; k < maxiter; k++) {
        Array<double>* s = matmul(&A, r);
        double alpha = dot(*r, *r) / dot(*r, *s);
        tempVectorPtr = x;
        x = add(x, multiply(alpha, r));
        delete tempVectorPtr;
        tempVectorPtr = r;
        r = subtract(r, multiply(alpha, s));
        delete tempVectorPtr;
        tempVectorPtr = nullptr;
    }
    return x;
}

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
