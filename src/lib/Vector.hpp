#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "Array.hpp"

template <typename T>
class Vector : public Array<T> {
public:
    unsigned int colDim() override { return m_colDim; }
    unsigned int rowDim() override { return m_rowDim; }

    // Constructors
    Vector(const unsigned int rowDim) :
        m_rowDim(rowDim) { initializeEmptyArray(); }
    Vector(T* array, const unsigned int rowDim) :
        m_array(array), m_rowDim(rowDim) {}

    // Overloaded () operators for element acceses by indices
    T operator()(unsigned int i, unsigned int j) override;
    T operator()(unsigned int i) { return m_array[i]; }

    // Element setters
    void set(unsigned int i, unsigned int j, T value) override;
    void set(unsigned int i, T value) { m_array[i] = value; }
    void setAll(T value) override;

    // Overloaded assignment and move assignment
    Vector<T>& operator=(const Vector<T>& rhs);
    Vector<T>& operator=(Vector<T>&& rhs);

    // Destructor, copy constructor, and move constructor
    ~Vector();
    Vector(const Vector<T>& obj);
    Vector(Vector<T>&& obj);

    // Prints the array
    void print() override;

private:
    // Internal representation of vector
    T* m_array = nullptr;
    unsigned int m_rowDim;
    const unsigned int m_colDim = 1;

    void makeCopyOfOther(const Vector<T>& obj);
    void initializeEmptyArray() override;
};

#include "Vector.ipp"

#endif