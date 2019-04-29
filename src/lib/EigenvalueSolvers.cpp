

#include "EigenvalueSolvers.hpp"
#include "LinearSolvers.hpp"
#include "VectorNorms.hpp"
#include "ArrayUtils.hpp"
#include "Utils.hpp"

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