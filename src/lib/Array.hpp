#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

template<typename T>
class Array {
public:
    unsigned int m_rowDim;
    unsigned int m_colDim;
    virtual T& operator()(unsigned int i, unsigned int j)=0;
    virtual void set(unsigned int i, unsigned int j, T value)=0;
    virtual void makeZeros()=0;
    virtual void print()=0;
};

#endif
