#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#include <iostream>

template<typename T>
class Array {
public:
    virtual T& operator()(unsigned int i, unsigned int j)=0;
    virtual void set(unsigned int i, unsigned int j, T value)=0;
    virtual unsigned int colDim()=0;
    virtual unsigned int rowDim()=0;
    virtual void makeZeros()=0;
    virtual void print()=0;
};

#endif
