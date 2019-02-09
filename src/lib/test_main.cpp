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

    DenseArray<int> b = DenseArray<int>(3, 3);
    b.makeIdentity();
    std::cout << "identity: " << std::endl;
    b.print();

    unsigned int cRows = 5;
    unsigned int cCols = 10;
    double** cRawArray = makeRandomArray(cRows, cCols);
    DenseArray<double>* c = new DenseArray<double>(cRawArray, cRows, cCols);
    c->print();

    unsigned int vecRows = 8;
    Array<double>* vec = new Vector<double>(vecRows);
    vec->makeOnes();

    std::cout << "vector: " << std::endl;
    vec->print();
    std::cout << "vector rows: " << std::endl;
    std::cout << static_cast<double>(vec->rowDim()) << std::endl;

    Array<double>* vec2 = new Vector<double>(vecRows);
    vec2->makeOnes();

    std::cout << "colDim: " << std::endl;
    std::cout << vec2->colDim() << std::endl;

    Array<double>* sum = add(vec, vec2);
    sum = multiply(5, sum);
    std::cout << "sum: " << std::endl;
    sum->print();
    return 0;
}
