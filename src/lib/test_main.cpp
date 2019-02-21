#include <iostream>
#include <ctime>

#include "MachineEpsilon.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"
#include "ArrayUtils.hpp"
#include "VectorNorms.hpp"
#include "MatrixNorms.hpp"

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

    DenseArray<int> b = DenseArray<int>(3, 3);
    b.makeIdentity();
    std::cout << "identity: " << std::endl;
    b.print();

    unsigned int vecRows = 8;
    Array<double>* vec = new Vector<double>(vecRows);
    vec->makeOnes();

    std::cout << "vector: " << std::endl;
    vec->print();
    std::cout << "vector rows: " << std::endl;
    std::cout << static_cast<double>(vec->rowDim()) << std::endl;

    Array<double>* vec2 = new Vector<double>(vecRows);
    vec2->setAll(11);

    std::cout << "Test add: " << std::endl;
    Array<double>* sum = add(vec, vec2);
    sum->print();

    std::cout << "colDim: " << std::endl;
    std::cout << vec2->colDim() << std::endl;


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

    DenseArray<double>* ar2 = new DenseArray<double>(2, 4);
    std::cout << "ar2:  " << std::endl;
    ar2->makeRandom();
    ar2->print();
    std::cout << "product:  " << std::endl;
    Array<double>* product = matmul(normishArray, ar2);
    product->print();

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

    return 0;
}
