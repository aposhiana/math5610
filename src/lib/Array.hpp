#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#include <iostream>

template<typename T>
class Array {
public:
    virtual unsigned int colDim()=0;
    virtual unsigned int rowDim()=0;
    virtual T& operator()(unsigned int i, unsigned int j)=0;
    virtual void set(unsigned int i, unsigned int j, T value)=0;
    virtual void setAll(T value)=0;
    void makeZeros() { setAll(0); }
    void makeOnes() { setAll(1); }
    virtual void print()=0;
};

#endif
