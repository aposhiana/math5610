#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#include <iostream>
#include <cmath>

#include "Utils.hpp"

template<typename T>
class Array {
public:
    virtual unsigned int colDim() const = 0;
    virtual unsigned int rowDim() const = 0;
    virtual T operator()(unsigned int i, unsigned int j) = 0;
    virtual void set(unsigned int i, unsigned int j, T value) = 0;
    virtual void setAll(T value) = 0;
    void makeRandom(const double min=0.0, const double max=1.0);
    void makeZeros() { setAll(0); }
    void makeOnes() { setAll(1); }
    virtual void print()=0;
private:
    virtual void initializeEmptyArray()=0;
};

template <typename T>
void Array<T>::makeRandom(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
    initializeEmptyArray();
    for (unsigned int i = 0; i < rowDim(); i++) {
        for (unsigned int j = 0; j < colDim(); j++) {
            double randValue = getRandDouble(min, max);
            set(i, j, randValue);
        }
    }
}

#endif
