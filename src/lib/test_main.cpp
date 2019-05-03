#include <iostream>
#include <ctime>

#include "MachineEpsilon.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"
#include "ArrayUtils.hpp"
#include "VectorNorms.hpp"
#include "MatrixNorms.hpp"
#include "LinearSolvers.hpp"
#include "EigenvalueSolvers.hpp"

int main() {
    // TODO: Set up real tests
    std::srand(std::time(nullptr));
    std::cout << "BEGINNING TESTS..." << std::endl;

    std::cout << "Single Machine Epsilon: " << getMachineEpsilon() << std::endl;
    std::cout << "Double Machine Epsilon: " << getDoubleMachineEpsilon() << std::endl;


    DenseArray<int> a = DenseArray<int>(2, 3);
    a.makeZeros();
    std::cout << "zeros: " << std::endl;
    a.print();

    DenseArray<double> identity_arr = DenseArray<double>(5);
    identity_arr.makeIdentity();
    std::cout << "identity: " << std::endl;
    identity_arr.print();

    unsigned int vecRows = 8;
    Array<double>* vec = new Vector<double>(vecRows);
    vec->makeOnes();

    std::cout << "vector: " << std::endl;
    vec->print();
    std::cout << "vector rows: " << std::endl;
    std::cout << static_cast<double>(vec->rowDim()) << std::endl;

    Array<double>* vec2 = new Vector<double>(vecRows);
    vec2->setAll(11);

    // Test add
    std::cout << "Vector 1 to be added: " << std::endl;
    Vector<double>* vtba1 = new Vector<double>(5);
    vtba1->makeRandom(0, 9.6);
    vtba1->print();

    std::cout << "Vector 2 to be added: " << std::endl;
    Vector<double>* vtba2 = new Vector<double>(5);
    vtba2->makeRandom(0, 4.5);
    vtba2->print();

    std::cout << "Vector sum: " << std::endl;
    Array<double>* vectorSum = add(vtba1, vtba2);
    vectorSum->print();

    std::cout << "Matrix 1 to be added: " << std::endl;
    DenseArray<double>* mtba1 = new DenseArray<double>(3, 2);
    mtba1->makeRandom(1.0, 4.3);
    mtba1->print();

    std::cout << "Matrix 2 to be added: " << std::endl;
    DenseArray<double>* mtba2 = new DenseArray<double>(3, 2);
    mtba2->makeRandom(0, 5.5);
    mtba2->print();

    std::cout << "Matrix sum: " << std::endl;
    Array<double>* matrixSum = add(mtba1, mtba2);
    matrixSum->print();


    std::cout << "Test multiply by a scalar:" << std::endl;
    const double SCALAR_CONST = 0.5;
    DenseArray<double>* toScale = new DenseArray<double>(5, 5);
    toScale->makeRandom();
    std::cout << "Array to be scaled:" << std::endl;
    toScale->print();
    // Multiply array by scalar
    Array<double>* scaledArray = multiply(SCALAR_CONST, toScale);
    std::cout << "Array scaled by " << SCALAR_CONST << ":" << std::endl;
    scaledArray->print();

    std::cout << "Test elementwise multiplication of Vectors:" << std::endl;
    Array<double>* vecToMult1 = new Vector<double>(4);
    vecToMult1->setAll(3);
    Array<double>* vecToMult2 = new Vector<double>(4);
    vecToMult2->setAll(7);
    // Elementwise multiply two arrays
    Array<double>* vecProduct = multiply(vecToMult1, vecToMult2);
    vecProduct->print();

    Array<double>* tArr = add(vec, vec2);
    tArr = multiply(5, tArr);
    tArr = multiply(vec2, tArr);
    std::cout << "test add and multiply: " << std::endl;
    tArr->print();

    // Using default min and max
    std::cout << "symmetric: " << std::endl;
    DenseArray<double>* sym = new DenseArray<double>(5, 5);
    sym->makeRandomSymmetric();
    sym->print();

    // Using other min and max
    std::cout << "symmetric non-default: " << std::endl;
    DenseArray<double>* symNonDef = new DenseArray<double>(5, 5);
    symNonDef->makeRandomSymmetric(4.5, 8.5);
    symNonDef->print();

    std::cout << "upper triangular: " << std::endl;
    DenseArray<double>* ut = new DenseArray<double>(3, 3);
    ut->makeRandomUpperTriangular();
    ut->print();

    std::cout << "lower triangular: " << std::endl;
    DenseArray<double>* lt = new DenseArray<double>(4, 4);
    lt->makeRandomLowerTriangular();
    lt->print();

    double absErr = absoluteError(2.3, 2.5);
    std::cout << "Absolute error: " << absErr << std::endl;

    double relErr = relativeError(2.3, 2.5);
    std::cout << "Relative error: " << relErr << std::endl;

    std::cout << "random vec y: " << std::endl;
    Vector<double>* y = new Vector<double>(2);
    y->makeRandom();
    y->print();

    std::cout << "random vec yHat: " << std::endl;
    Vector<double>* yHat = new Vector<double>(2);
    yHat->makeRandom();
    yHat->print();

    std::cout << "y l1Norm: " << std::endl;
    std::cout << l1Norm(*y) << std::endl;
    std::cout << "y l2Norm: " << std::endl;
    std::cout << l2Norm(*y) << std::endl;
    std::cout << "y infNorm: " << std::endl;
    std::cout << infNorm(*y) << std::endl;

    std::cout << "l1NormAbsoluteError: " << std::endl;
    std::cout << l1NormAbsoluteError(*y, *yHat) << std::endl;

    std::cout << "l2NormAbsoluteError: " << std::endl;
    std::cout << l2NormAbsoluteError(*y, *yHat) << std::endl;

    std::cout << "infNormAbsoluteError: " << std::endl;
    std::cout << infNormAbsoluteError(*y, *yHat) << std::endl;


    DenseArray<double>* normishArray = new DenseArray<double>(3, 2);
    normishArray->makeRandom();
    std::cout << "Matrix to be normed: " << std::endl;
    normishArray->print();
    std::cout << "Matrix 1-norm: " << std::endl;
    std::cout << matrix1Norm(*normishArray) << std::endl;
    std::cout << "Matrix infinity-norm: " << std::endl;
    std::cout << matrixInfNorm(*normishArray) << std::endl;

    Vector<double>* v1 = new Vector<double>(3);
    v1->makeRandom();
    std::cout << "Vector 1 for dot product:" << std::endl;
    v1->print();

    Vector<double>* v2 = new Vector<double>(3);
    v2->makeRandom();
    std::cout << "Vector 2 for dot product:" << std::endl;
    v2->print();

    std::cout << "Dot product: " << dot(*v1, *v2) << std::endl;

    Vector<double>* vc1 = new Vector<double>(3);
    vc1->makeRandom();
    std::cout << "Vector 1 for cross product:" << std::endl;
    vc1->print();

    Vector<double>* vc2 = new Vector<double>(3);
    vc2->makeRandom();
    std::cout << "Vector 2 for cross product:" << std::endl;
    vc2->print();

    Vector<double> crossProductResult = cross(*vc1, *vc2);
    std::cout << "Cross product:" << std::endl;
    crossProductResult.print();

    DenseArray<double>* ar1 = new DenseArray<double>(3, 2);
    std::cout << "ar1:  " << std::endl;
    ar1->makeRandom();
    ar1->print();

    DenseArray<double>* ar2 = new DenseArray<double>(2, 4);
    std::cout << "ar2:  " << std::endl;
    ar2->makeRandom();
    ar2->print();

    // Test matmul
    std::cout << "matmul(ar1, ar2):  " << std::endl;
    Array<double>* product = matmul(ar1, ar2);
    product->print();

    std::cout << "Vector 1 for outer product:  " << std::endl;
    Vector<double>* vfcp1 = new Vector<double>(5);
    vfcp1->makeRandom();
    vfcp1->print();

    std::cout << "Vector 2 for outer product:  " << std::endl;
    Vector<double>* vfcp2 = new Vector<double>(5);
    vfcp2->makeRandom();
    vfcp2->print();

    std::cout << "Outer product:  " << std::endl;
    Array<double>* outerProductResult = matmul(vfcp1, transpose(vfcp2));
    outerProductResult->print();


    std::cout << "Random DD Matrix:  " << std::endl;
    DenseArray<double>* ddA = new DenseArray<double>(5, 5);
    ddA->makeRandomDD(-5, 5);
    ddA->print();

    std::cout << "Another random DD Matrix:  " << std::endl;
    DenseArray<double>* ddA2 = new DenseArray<double>(5, 5);
    ddA2->makeRandomDD(-10, -2);
    ddA2->print();

    std::cout << "Yet another random DD Matrix:  " << std::endl;
    DenseArray<double>* ddA3 = new DenseArray<double>(5, 5);
    ddA3->makeRandomDD(1, 11);
    ddA3->print();

    std::cout << "Test random raw array:  " << std::endl;
    const unsigned int ROWS = 5;
    const unsigned int COLS = 10;
    double** rawArray = makeRandomRawArray(ROWS, COLS);
    DenseArray<double>* myArray = new DenseArray<double>(rawArray, ROWS, COLS);
    myArray->print();

    std::cout << "Matrix to be transposed:  " << std::endl;
    DenseArray<double>* mtbt = new DenseArray<double>(4, 2);
    mtbt->makeRandom(0, 9.5);
    mtbt->print();
    std::cout << "Transpose of matrix: " << std::endl;
    DenseArray<double>* mtbtT = transpose(mtbt);
    mtbtT->print();

    std::cout << "Vector to be transposed:  " << std::endl;
    Vector<double>* vtbt = new Vector<double>(4);
    vtbt->makeRandom(-4, 10.5);
    vtbt->print();
    std::cout << "Transpose of vector:  " << std::endl;
    DenseArray<double>* vtbtT = transpose(vtbt);
    vtbtT->print();

    std::cout << "b for linear systems:  " << std::endl;
    Vector<double>* b_ls = new Vector<double>(5);
    b_ls->makeRandom(1, 10);
    b_ls->print();

    std::cout << "A for diagonal linear system:  " << std::endl;
    Array<double>* A_dls = multiply(2.0, &identity_arr);
    A_dls->print();

    std::cout << "x found for diagonal system:  " << std::endl;
    Vector<double> x_dls = solveLinearDiagonalSystem(*A_dls, *b_ls);
    x_dls.print();

    std::cout << "A for upper triangular linear system:  " << std::endl;
    DenseArray<double>* A_utls = new DenseArray<double>(5);
    A_utls->makeRandomUpperTriangular(1.0, 10.0);
    A_utls->print();

    std::cout << "x found for upper triangular system:  " << std::endl;
    Vector<double> x_utls = backsub(*A_utls, *b_ls);
    x_utls.print();

    std::cout << "b for lower triangular system:  " << std::endl;
    Vector<double>* b_ls2 = new Vector<double>(3);
    b_ls2->makeRandom(1, 10);
    b_ls2->print();

    std::cout << "A for lower triangular linear system:  " << std::endl;
    DenseArray<double>* A_ltls = new DenseArray<double>(3);
    A_ltls->makeRandomLowerTriangular(1.0, 10.0);
    A_ltls->print();

    std::cout << "x found for lower triangular system:  " << std::endl;
    Vector<double> x_ltls = forwardsub(*A_ltls, *b_ls2);
    x_ltls.print();

    std::cout << "Random row echelon coefficient matrix: " << std::endl;
    DenseArray<double>* AB_0 = new DenseArray<double>(3, 4);
    AB_0->makeRandomAugmentedEchelon(1.0, 10.0);
    AB_0->print();

    std::cout << "x found for random augmented row echelon system:  " << std::endl;
    Vector<double> x_rarre = backsub(*AB_0);
    x_rarre.print();

    std::cout << "Random DD matrix A_dd0: " << std::endl;
    DenseArray<double>* A_dd0 = new DenseArray<double>(3, 3);
    A_dd0->makeRandomDD(1.0, 10.0);
    A_dd0->print();

    std::cout << "b_dd0 for A_dd0 system:  " << std::endl;
    Vector<double>* b_dd0 = new Vector<double>(3);
    b_dd0->makeRandom(1, 10);
    b_dd0->print();

    rowReduce(*A_dd0, *b_dd0);
    std::cout << "A_dd0 after rowReduce: " << std::endl;
    A_dd0->print();
    std::cout << "b_dd0 after rowReduce: " << std::endl;
    b_dd0->print();

    std::cout << "Random augmented coefficient matrix  AB_1 to be put in row echelon form: " << std::endl;
    DenseArray<double>* AB_1 = new DenseArray<double>(3, 4);
    AB_1->makeRandom(1.0, 10.0);
    AB_1->print();

    std::cout << "AB_1 after row reduction: " << std::endl;
    rowReduce(*AB_1);
    AB_1->print();

    std::cout << "Random augmented coefficient matrix  AB_2 to be solved: " << std::endl;
    DenseArray<double>* AB_2 = new DenseArray<double>(3, 4);
    AB_2->makeRandom(1.0, 10.0);
    AB_2->print();

    std::cout << "x found for AB_2 system:  " << std::endl;
    Vector<double> x_ab2 = solveLinearSystem(*AB_2);
    x_ab2.print();

    std::cout << "Diagonally dominant coefficient matrix  A_3 to be solved: " << std::endl;
    DenseArray<double>* A_3 = new DenseArray<double>(3, 3);
    A_3->makeRandomDD(1.0, 10.0);
    A_3->print();

    std::cout << "b_3: " << std::endl;
    Vector<double>* b_3 = new Vector<double>(3);
    b_3->makeRandom(1.0, 10.0);
    b_3->print();

    std::cout << "x found for A_3 system:  " << std::endl;
    Vector<double> x_a3 = solveLinearSystem(*A_3, *b_3);
    x_a3.print();

    std::cout << "Diagonally dominant coefficient matrix  A_4 to be factorized: " << std::endl;
    DenseArray<double>* A_4 = new DenseArray<double>(6, 6);
    A_4->makeRandomDD(1.0, 100.0);
    A_4->print();

    DenseArray<double>* Q_4 = new DenseArray<double>(6, 6, true);
    DenseArray<double>* R_4 = new DenseArray<double>(6, 6, true);
    squareModifiedGramSchmidt(*A_4, *Q_4, *R_4);
    std::cout << "Q_4 from Modified Gram Schmidt" << std::endl;
    Q_4->print();
    std::cout << "R_4 from Modified Gram Schmidt" << std::endl;
    R_4->print();

    std::cout << "b_4: " << std::endl;
    Vector<double>* b_4 = new Vector<double>(6);
    b_4->makeRandom(1.0, 5000.0);
    b_4->print();

    Vector<double> x_4_qr = qrSolve(*Q_4, *R_4, *b_4);

    std::cout << "Again: A_4 to be factorized: " << std::endl;
    A_4->print();
    std::cout << "Again: b_4: " << std::endl;
    b_4->print();

    DenseArray<double>* L_4 = new DenseArray<double>(6, 6);
    DenseArray<double>* U_4 = new DenseArray<double>(6, 6);
    lu(*A_4, *L_4, *U_4);
    std::cout << "L from A_4 " << std::endl;
    L_4->print();
    std::cout << "U from A_4 " << std::endl;
    U_4->print();

    std::cout << "x_4 found with LU: " << std::endl;
    Vector<double> x_4 = luSolve(*L_4, *U_4, *b_4);
    x_4.print();
    std::cout << "x_4 found with QR: " << std::endl;
    x_4_qr.print();

    std::cout << "A_randlu for LU" << std::endl;
    DenseArray<double>* A_randlu = new DenseArray<double>(4, 4);
    A_randlu->makeRandom();
    A_randlu->print();
    DenseArray<double>* L_randlu = new DenseArray<double>(4, 4);
    DenseArray<double>* U_randlu = new DenseArray<double>(4, 4);
    lu(*A_randlu, *L_randlu, *U_randlu);
    std::cout << "L from A_randlu " << std::endl;
    L_randlu->print();
    std::cout << "U from A_randlu " << std::endl;
    U_randlu->print();

    // std::cout << "SPD_large: " << std::endl;
    // Array<double>* SPD_large = getRandomSPDArray(110);
    // SPD_large->print();

    // std::cout << "cholesky(SPD_large):  " << std::endl;
    // cholesky(*SPD_large);
    // SPD_large->print();

    std::cout << "SPD_0: " << std::endl;
    Array<double>* SPD_0 = getRandomSPDArray(10);
    SPD_0->print();

    std::cout << "cholesky(SPD_0):  " << std::endl;
    cholesky(*SPD_0);
    SPD_0->print();

    std::cout << "SPD_1: " << std::endl;
    Array<double>* SPD_1 = getRandomSPDArray(3);
    SPD_1->print();

    std::cout << "cholesky(SPD_1):  " << std::endl;
    cholesky(*SPD_1);
    SPD_1->print();

    // Test that non-SPD matrix fails (note that the random matrix could be SPD - check)
    // std::cout << "test1: " << std::endl;
    // Array<double>* test1 = new DenseArray<double>(3, 3);
    // test1->makeRandom(1.0, 10.0);
    // test1->print();
    // std::cout << "cholesky(test1):  " << std::endl;
    // cholesky(*test1);
    // test1->print();

    std::cout << "Random skinny matrix A_cnes: " << std::endl;
    Array<double>* A_cnes = new DenseArray<double>(20, 2);
    A_cnes->makeRandom(1.0, 10.0);
    A_cnes->print();

    std::cout << "Random vector b_cnes: " << std::endl;
    Vector<double>* b_cnes = new Vector<double>(20);
    b_cnes->makeRandom(1.0, 10.0);
    b_cnes->print();

    std::cout << "Least squares solution to A_cnes * x_cnes = b_nes" << std::endl;
    Vector<double> x_cnes = solveNormalEquation(*A_cnes, *b_cnes);
    x_cnes.print();

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

    DenseArray<double>* Q_m_gs1 = new DenseArray<double>(5, 5, true);
    DenseArray<double>* R_m_gs1 = new DenseArray<double>(5, 5, true);
    squareModifiedGramSchmidt(*A_gs1, *Q_m_gs1, *R_m_gs1);
    std::cout << "Q_m_gs1 from Modified Gram Schmidt" << std::endl;
    Q_m_gs1->print();
    std::cout << "R_m_gs1 from Modified Gram Schmidt" << std::endl;
    R_m_gs1->print();

    // Large Iterative tests
    // std::cout << "A_iterative_large: " << std::endl;
    // DenseArray<double>* A_iterative_large = new DenseArray<double>(1000);
    // A_iterative_large->makeRandomSymmetricDD(-100.0, 100.0);
    // A_iterative_large->print();

    // std::cout << "b_iterative_large for Iterative methods: " << std::endl;
    // Vector<double>* b_iterative_large = new Vector<double>(1000);
    // b_iterative_large->makeRandom(-100.0, 100.0);
    // b_iterative_large->print();

    // Vector<double> x_ji_large = jacobiSolve(*A_iterative_large, *b_iterative_large, 0, 5000);
    // std::cout << "x_ji_large found using Jacobi: " << std::endl;
    // x_ji_large.print();

    // Vector<double> x_gs_large = gaussSeidelSolve(*A_iterative_large, *b_iterative_large, 0, 5000);
    // std::cout << "x_gs_large found using Gauss-Seidel: " << std::endl;
    // x_gs_large.print();


    // Small iterative tests
    std::cout << "A_iterative for Iterative methods: " << std::endl;
    DenseArray<double>* A_iterative = new DenseArray<double>(10, 10);
    A_iterative->makeRandomDD(1.0, 30.0);
    A_iterative->print();

    std::cout << "b_iterative for Iterative methods: " << std::endl;
    Vector<double>* b_iterative = new Vector<double>(10);
    b_iterative->makeRandom(1.0, 10.0);
    b_iterative->print();

    Vector<double> x_iterative_ji = jacobiSolve(*A_iterative, *b_iterative, 0, 10000);
    std::cout << "x_iterative_ji found using Jacobi: " << std::endl;
    x_iterative_ji.print();

    Vector<double> x_iterative_gs = gaussSeidelSolve(*A_iterative, *b_iterative, 0, 100);
    std::cout << "x_iterative_gs found using Gauss-Seidel: " << std::endl;
    x_iterative_gs.print();

    Array<double>* x_iterative_sd = steepestDescentSolve(*A_iterative, *b_iterative, 50);
    std::cout << "x_iterative_sd found using steepest descent: " << std::endl;
    x_iterative_sd->print();

    std::cout << "A_spd_cg for Iterative methods: " << std::endl;
    Array<double>* A_spd_cg = getRandomSPDArray(10);
    A_spd_cg->print();

    Vector<double>* x_spd_cg = cg(*A_spd_cg, *b_iterative, 0.1);
    std::cout << "x_spd_cg found using CG: " << std::endl;
    x_spd_cg->print();

    std::cout << "A_eig" << std::endl;
    Array<double>* A_eig = getRandomSPDArray(3);
    A_eig->print();
    double A_eig_lambda = powerEigenSolve(*A_eig, 0.0001, 10000);
    std::cout << "A_eig_lambda found using power method: " << A_eig_lambda << std::endl;
    double A_eig_smallest = inverseEigenSolve(*A_eig, 0, 0.000001, 10000);
    std::cout << "A_eig_smallest found using inverse iteration: " << A_eig_smallest << std::endl;
    double A_eig_rayleigh = rayleighEigenSolve(*A_eig, 0.000001, 1000);
    std::cout << "eigenvalue found with Rayleigh Quotient Iteration: " << A_eig_rayleigh << std::endl;

    std::cout << "Hilbert Matrix: " << std::endl;
    DenseArray<double>* A_hilbert = new DenseArray<double>(5);
    A_hilbert->makeHilbert();
    A_hilbert->print();

    double A_hilbert_lambda = powerEigenSolve(*A_hilbert, 0.0001, 10000);
    std::cout << "A_hilbert_lambda found using power method: " << A_hilbert_lambda << std::endl;
    double A_hilbert_smallest = inverseEigenSolve(*A_hilbert, 0, 0.000001, 10000);
    std::cout << "A_hilbert_smallest found using inverse iteration: " << A_hilbert_smallest << std::endl;
    double A_hilbert_rayleigh = rayleighEigenSolve(*A_hilbert, 0.000001, 1000);
    std::cout << "eigenvalue for hilbert found with Rayleigh Quotient Iteration: " << A_hilbert_rayleigh << std::endl;

    std::cout << "Symmetric Diagonally Dominant Matrix: " << std::endl;
    DenseArray<double>* A_sdd = new DenseArray<double>(4);
    A_sdd->makeRandomSymmetricDD();
    A_sdd->print();

    std::cout << "Wide DD Matrix A_wide_dd" << std::endl;
    DenseArray<double>* A_wide_dd = new DenseArray<double>(3, 6);
    A_wide_dd->makeRandomDDWide(1.0, 10.0);
    A_wide_dd->print();

    std::cout << "A_wide_dd in echelon form" << std::endl;
    rowReduce(*A_wide_dd, false);
    A_wide_dd->print();

    // Hilbert tests
    std::cout << "Hilbert 2" << std::endl;
    DenseArray<double>* hil2 = new DenseArray<double>(2);
    hil2->makeHilbert();
    double hil2Kappa = estimate2NormConditionNumber(*hil2, 0.000001, 10000);
    std::cout << "hil2Kappa: " << hil2Kappa << std::endl;

    std::cout << "Hilbert 4" << std::endl;
    DenseArray<double>* hil4 = new DenseArray<double>(4);
    hil4->makeHilbert();
    double hil4Kappa = estimate2NormConditionNumber(*hil4, 0.000001, 10000);
    std::cout << "hil4Kappa: " << hil4Kappa << std::endl;
    // hil4->print();
    // DenseArray<double>* Q_hil4 = new DenseArray<double>(4, 4, true);
    // DenseArray<double>* R_hil4 = new DenseArray<double>(4, 4, true);
    // squareClassicalGramSchmidt(*hil4, *Q_hil4, *R_hil4);
    // std::cout << "Q_hil4 from Classical Gram Schmidt" << std::endl;
    // Q_hil4->print();
    // std::cout << "R_hil4 from Classical Gram Schmidt" << std::endl;
    // R_hil4->print();
    // std::cout << "Q_hil4 * transpose(Q_hil4)" << std::endl;
    // Array<double>* QQThil4 = matmul(Q_hil4, transpose(Q_hil4));
    // QQThil4->print();

    std::cout << "Hilbert 6" << std::endl;
    DenseArray<double>* hil6 = new DenseArray<double>(6);
    hil6->makeHilbert();
    double hil6Kappa = estimate2NormConditionNumber(*hil6, 0.000001, 10000);
    std::cout << "hil6Kappa: " << hil6Kappa << std::endl;
    // hil6->print();
    // DenseArray<double>* Q_hil6 = new DenseArray<double>(6, 6, true);
    // DenseArray<double>* R_hil6 = new DenseArray<double>(6, 6, true);
    // squareClassicalGramSchmidt(*hil6, *Q_hil6, *R_hil6);
    // std::cout << "Q_hil6 from Classical Gram Schmidt" << std::endl;
    // Q_hil6->print();
    // std::cout << "R_hil6 from Classical Gram Schmidt" << std::endl;
    // R_hil6->print();
    // std::cout << "Q_hil6 * transpose(Q_hil6)" << std::endl;
    // Array<double>* QQThil6 = matmul(Q_hil6, transpose(Q_hil6));
    // QQThil6->print();

    std::cout << "Hilbert 8" << std::endl;
    DenseArray<double>* hil8 = new DenseArray<double>(8);
    hil8->makeHilbert();
    double hil8Kappa = estimate2NormConditionNumber(*hil8, 0.000001, 10000);
    std::cout << "hil8Kappa: " << hil8Kappa << std::endl;
    // hil8->print();
    // DenseArray<double>* Q_hil8 = new DenseArray<double>(8, 8, true);
    // DenseArray<double>* R_hil8 = new DenseArray<double>(8, 8, true);
    // squareClassicalGramSchmidt(*hil8, *Q_hil8, *R_hil8);
    // std::cout << "Q_hil8 from Classical Gram Schmidt" << std::endl;
    // Q_hil8->print();
    // std::cout << "R_hil8 from Classical Gram Schmidt" << std::endl;
    // R_hil8->print();
    // std::cout << "Q_hil8 * transpose(Q_hil8)" << std::endl;
    // Array<double>* QQThil8 = matmul(Q_hil8, transpose(Q_hil8));
    // QQThil8->print();

    std::cout << "Hilbert 10" << std::endl;
    DenseArray<double>* hil10 = new DenseArray<double>(10);
    hil10->makeHilbert();
    double hil10Kappa = estimate2NormConditionNumber(*hil10, 0.000001, 10000);
    std::cout << "hil10Kappa: " << hil10Kappa << std::endl;
    // hil10->print();
    // DenseArray<double>* Q_hil10 = new DenseArray<double>(10, 10, true);
    // DenseArray<double>* R_hil10 = new DenseArray<double>(10, 10, true);
    // squareClassicalGramSchmidt(*hil10, *Q_hil10, *R_hil10);
    // std::cout << "Q_hil10 from Classical Gram Schmidt" << std::endl;
    // Q_hil10->print();
    // std::cout << "R_hil10 from Classical Gram Schmidt" << std::endl;
    // R_hil10->print();
    // std::cout << "Q_hil10 * transpose(Q_hil10)" << std::endl;
    // Array<double>* QQThil10 = matmul(Q_hil10, transpose(Q_hil10));
    // QQThil10->print();

    std::cout << "Hilbert 12" << std::endl;
    DenseArray<double>* hil12 = new DenseArray<double>(12);
    hil12->makeHilbert();
    double hil12Kappa = estimate2NormConditionNumber(*hil12, 0.000001, 10000);
    std::cout << "hil12Kappa: " << hil12Kappa << std::endl;

    // Medium tests
    std::cout << "A_iterative_medium: " << std::endl;
    DenseArray<double>* A_iterative_medium = new DenseArray<double>(600);
    A_iterative_medium->makeRandomSymmetricDD(-10.0, 10.0);
    // Array<double>* A_iterative_medium = getRandomSPDArray(6);
    // A_iterative_medium->print();

    DenseArray<double>* L_itermed = new DenseArray<double>(600);
    DenseArray<double>* U_itermed = new DenseArray<double>(600);
    lu(*A_iterative_medium, *L_itermed, *U_itermed);
    // std::cout << "L_itermed " << std::endl;
    // L_4->print();
    // std::cout << "U_itermed " << std::endl;
    // U_4->print();

    std::cout << "b_iterative_medium for Iterative methods: " << std::endl;
    Vector<double>* b_iterative_medium = new Vector<double>(600);
    b_iterative_medium->makeRandom(-10.0, 10.0);
    // b_iterative_medium->print();

    std::cout << "x found with LU: " << std::endl;
    Vector<double> x_itermed = luSolve(*L_itermed, *U_itermed, *b_iterative_medium);
    x_itermed.print();

    std::cout << "Jacobi tol 0.01: " << std::endl;
    Vector<double> x_js001 = jacobiSolve(*A_iterative_medium, *b_iterative_medium, 0.01, 1000);
    x_js001.print();

    std::cout << "Gauss-Seidel tol 0.01: " << std::endl;
    Vector<double> x_gs001 = gaussSeidelSolve(*A_iterative_medium, *b_iterative_medium, 0.01, 1000);
    x_gs001.print();

    return 0;
}
