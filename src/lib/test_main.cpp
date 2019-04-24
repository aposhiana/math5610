#include <iostream>
#include <ctime>

#include "MachineEpsilon.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"
#include "ArrayUtils.hpp"
#include "VectorNorms.hpp"
#include "MatrixNorms.hpp"
#include "LinearSolvers.hpp"

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
    std::cout << "product:  " << std::endl;
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

    std::cout << "Random reduced row echelon coefficient matrix: " << std::endl;
    DenseArray<double>* AB_0 = new DenseArray<double>(3, 4);
    AB_0->makeRandomAugmentedEchelon(1.0, 10.0);
    AB_0->print();

    std::cout << "x found for random augmented reduced row echelon system:  " << std::endl;
    Vector<double> x_rarre = backsub(*AB_0);
    x_rarre.print();

    return 0;
}
