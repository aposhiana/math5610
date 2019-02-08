#ifndef _DENSE_ARRAY_HPP_
#define _DENSE_ARRAY_HPP_

#include "Array.hpp"

template<typename T>
class DenseArray : public Array<T> {
public:
    unsigned int m_rowDim;
    unsigned int m_colDim;
    bool isSymmetricForm() { return m_isSymmetricForm; }
    void setSymmetric();

    // Constructors
    DenseArray(const unsigned int rowDim, const unsigned int colDim) : 
        m_rowDim(rowDim), m_colDim(colDim) {};
    DenseArray(T** array, const unsigned int rowDim,
                const unsigned int colDim, const bool symmetric=false) :
        m_array(array), m_rowDim(rowDim),
        m_colDim(colDim), m_isSymmetricForm(symmetric)
        { if (symmetric) { setSymmetric(); }}

    // Constructors for square arrays
    DenseArray(const unsigned int axesDim)
        { return DenseArray(axesDim, axesDim); }
    DenseArray(T** array, const unsigned int axesDim, const bool symmetric=false)
        { return DenseArray(array, axesDim, axesDim, symmetric); }

    // Overloaded () operator for element acceses by indices
    T& operator()(unsigned int i, unsigned int j) override;
    
    // Element setter
    void set(unsigned int i, unsigned int j, T value) override;

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
    T** m_array = nullptr; // Internal representation of array
    bool m_isSymmetricForm = false;
    void deleteArrayMember();
    void convertToSymmetricIndices(unsigned int& i, unsigned int& j);

    // Helper method for assignment and copy constructor
    void makeCopyOfOther(const DenseArray<T>& obj);
};

#include "DenseArray.ipp"

#endif
