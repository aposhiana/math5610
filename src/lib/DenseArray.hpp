#ifndef _DENSE_ARRAY_HPP_
#define _DENSE_ARRAY_HPP_

#include "Array.hpp"

template<typename T>
class DenseArray : public Array<T> {
public:
    unsigned int m_rowDim;
    unsigned int m_colDim;

    // Constructors
    DenseArray(const unsigned int rowDim, const unsigned int colDim) : 
        m_rowDim(rowDim), m_colDim(colDim) {};
    DenseArray(T** array, const unsigned int rowDim, const unsigned int colDim) : 
        m_array(array), m_rowDim(rowDim), m_colDim(colDim) {};
    // Shortcut constructors for square arrays
    DenseArray(const unsigned int axesDim)
        { return DenseArray(axesDim, axesDim); }
    DenseArray(T** array, const unsigned int axesDim)
        { return DenseArray(array, axesDim, axesDim); }

    // Overloaded () operator for element acceses by indices
    T& operator()(const unsigned int i, const unsigned int j) override 
        { return m_array[i][j]; }

    // Overloaded assignment and move assignment
    DenseArray<T>& operator=(const DenseArray<T>& rhs);
    DenseArray<T>& operator=(DenseArray<T>&& rhs);

    // Destructor, copy constructor, and move constructor
    ~DenseArray();
    DenseArray(const DenseArray<T>& obj);
    DenseArray(DenseArray<T>&& obj);

    // Shortcuts to initialize m_array
    void makeZeros() override;
    void makeIdentity() override;
    void print() override;
private:
    // Internal representation of array
    T** m_array = nullptr;

    // Helper method for assignment and copy constructor
    void makeCopyOfOther(const DenseArray<T>& obj);
};

#include "DenseArray.ipp"

#endif
