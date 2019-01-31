#include <iostream>
#include "MachineEpsilon.hpp"
#include "DenseArray.hpp"

int main() {
    std::cout << "BEGINNING TESTS..." << std::endl;

    std::cout << "Single Machine Epsilon: " << getMachineEpsilon() << std::endl;
    std::cout << "Double Machine Epsilon: " << getDoubleMachineEpsilon() << std::endl;


    DenseArray<int> a = DenseArray<int>(2, 3);
    a.makeZeros();
    std::cout << "rows: " << std::endl;
    for (int i = 0; i < a.m_rowDim; i++) {
        std::cout << a(i, 0) << std::endl;
    }
    // std::cout << a.m_colDim << std::endl;
    std::cout << "cols: " << std::endl;
    for (int i = 0; i < a.m_colDim; i++) {
        std::cout << a(0, i) << std::endl;
    }


    DenseArray<int> b = DenseArray<int>(3, 3);
    b.makeIdentity();
    std::cout << "rows: " << std::endl;
    for (int i = 0; i < b.m_rowDim; i++) {
        std::cout << b(i, 0) << std::endl;
    }
    // std::cout << a.m_colDim << std::endl;
    std::cout << "cols: " << std::endl;
    for (int i = 0; i < b.m_colDim; i++) {
        std::cout << b(0, i) << std::endl;
    }
    
    return 0;
}
