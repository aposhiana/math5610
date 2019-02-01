#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

template<typename T>
class Array {
public:
    virtual T* operator()(const unsigned int i)=0;
    virtual T& operator()(const unsigned int i, const unsigned int j)=0;
    virtual void makeZeros()=0;
    virtual void makeIdentity()=0;
    virtual void print()=0;
};

#endif
