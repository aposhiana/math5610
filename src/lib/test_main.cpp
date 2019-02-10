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

    // unsigned int cRows = 5;
    // unsigned int cCols = 10;
    // double** cRawArray = makeRandomArray(cRows, cCols);
    // DenseArray<double>* c = new DenseArray<double>(cRawArray, cRows, cCols);
    // c->print();

    unsigned int vecRows = 8;
    Array<double>* vec = new Vector<double>(vecRows);
    vec->makeOnes();

    std::cout << "vector: " << std::endl;
    vec->print();
    std::cout << "vector rows: " << std::endl;
    std::cout << static_cast<double>(vec->rowDim()) << std::endl;

    Array<double>* vec2 = new Vector<double>(vecRows);
    vec2->setAll(11);

    std::cout << "colDim: " << std::endl;
    std::cout << vec2->colDim() << std::endl;

    Array<double>* sum = add(vec, vec2);
    sum = multiply(5, sum);
    sum = multiply(vec2, sum);
    std::cout << "sum: " << std::endl;
    sum->print();

    std::cout << "symmetric: " << std::endl;
    DenseArray<double>* sym = new DenseArray<double>(5, 5);
    sym->makeRandomSymmetric();
    sym->print();

    std::cout << "upper triangular: " << std::endl;
    DenseArray<double>* ut = new DenseArray<double>(3, 3);
    ut->makeRandomUpperTriangular();
    ut->print();

    std::cout << "lower triangular: " << std::endl;
    DenseArray<double>* lt = new DenseArray<double>(4, 4);
    lt->makeRandomLowerTriangular();
    lt->print();

    std::cout << "absoluteError: " << std::endl;
    std::cout << absoluteError(2.3, 2.5) << std::endl;

    std::cout << "relativeError: " << std::endl;
    std::cout << relativeError(2.3, 2.5) << std::endl;

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

    return 0;
}
