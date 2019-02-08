#include <iostream>
#include <ctime>

#include "MachineEpsilon.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"
#include "ArrayUtils.hpp"

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
    // for (int i = 0; i < a.m_rowDim; i++) {
    //     std::cout << a(i, 0) << std::endl;
    // }
    // // std::cout << a.m_colDim << std::endl;
    // std::cout << "cols: " << std::endl;
    // for (int i = 0; i < a.m_colDim; i++) {
    //     std::cout << a(0, i) << std::endl;
    // }


    DenseArray<int> b = DenseArray<int>(3, 3);
    b.makeIdentity();
    std::cout << "identity: " << std::endl;
    b.print();
    // for (int i = 0; i < b.m_rowDim; i++) {
    //     std::cout << b(i, 0) << std::endl;
    // }
    // // std::cout << a.m_colDim << std::endl;
    // std::cout << "cols: " << std::endl;
    // for (int i = 0; i < b.m_colDim; i++) {
    //     std::cout << b(0, i) << std::endl;
    // }

    unsigned int cRows = 5;
    unsigned int cCols = 10;
    double** cRawArray = makeRandomArray(cRows, cCols);
    DenseArray<double>* c = new DenseArray<double>(cRawArray, cRows, cCols);
    c->print();

    unsigned int vecCols = 8;
    Vector<double>* vec = new Vector<double>(vecCols);
    vec->makeZeros();
    std::cout << "vector: " << std::endl;
    vec->print();
    std::cout << "vector rows: " << std::endl;
    std::cout << vec->m_rowDim << std::endl;

    return 0;
}
