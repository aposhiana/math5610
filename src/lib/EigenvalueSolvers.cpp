

#include "EigenvalueSolvers.hpp"
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
        // std::cout << "k " << k << std::endl;
        // std::cout << "error " << error << std::endl;
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
