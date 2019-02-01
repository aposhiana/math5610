#ifndef _DENSE_ARRAY_HPP_
#define _DENSE_ARRAY_HPP_

#include "Array.hpp"

template<typename T>
class DenseArray : public Array<T> {
public:
    T** m_array = nullptr;
    const unsigned int m_rowDim;
    const unsigned int m_colDim;

    ~DenseArray();
    DenseArray(const unsigned int rowDim, const unsigned int colDim) : 
        m_rowDim(rowDim), m_colDim(colDim) {};
    DenseArray(T** array, const unsigned int rowDim, const unsigned int colDim) : 
        m_array(array), m_rowDim(rowDim), m_colDim(colDim) {};

    // Shortcut constructors for square arrays
    DenseArray(const unsigned int axesDim)
        { return DenseArray(axesDim, axesDim); }
    DenseArray(T** array, const unsigned int axesDim)
        { return DenseArray(array, axesDim, axesDim); }

    T* operator()(const unsigned int i) override 
        { return m_array[i]; }
    T& operator()(const unsigned int i, const unsigned int j) override 
        { return m_array[i][j]; }

    // Shortcuts to initialize m_array
    void makeZeros() override;
    void makeIdentity() override;
    void print() override;
};

#include "DenseArray.ipp"

#endif
