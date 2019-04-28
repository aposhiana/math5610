#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "Array.hpp"

template <typename T>
class Vector : public Array<T> {
public:
    // Getters
    unsigned int colDim() const override { return m_colDim; }
    unsigned int rowDim() const override { return m_rowDim; }
    T** getRawArray() override { return m_array; }

    // Constructors
    Vector(const unsigned int rowDim, bool init=false) :
        m_rowDim(rowDim)
        {if (init) { initializeEmptyArray(); }}
    Vector(T** array, const unsigned int rowDim, bool init=false) :
        m_array(array), m_rowDim(rowDim)
        { if (init) { initializeEmptyArray(); }}

    // Overloaded () operators for element acceses by indices
    T operator()(unsigned int i, unsigned int j) override;
    T operator()(unsigned int i) { return m_array[0][i]; }
    // Element setters
    void set(unsigned int i, unsigned int j, T value) override;
    void set(unsigned int i, T value) { m_array[0][i] = value; }
    void setAll(T value) override;

    // Prints the array
    void print() override;

    // Overloaded assignment and move assignment
    Vector<T>& operator=(const Vector<T>& rhs);
    Vector<T>& operator=(Vector<T>&& rhs);
    // Destructor, copy constructor, and move constructor
    ~Vector();
    Vector(const Vector<T>& obj);
    Vector(Vector<T>&& obj);

private:
    // Internal representation of vector
    T** m_array = nullptr;
    unsigned int m_rowDim;
    const unsigned int m_colDim = 1;

    void makeCopyOfOther(const Vector<T>& obj);
    void initializeEmptyArray() override;
    void deleteArrayMember();
};

#include "Vector.ipp"

#endif