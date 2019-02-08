#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "Array.hpp"

template <typename T>
class Vector : public Array<T> {
public:
    const unsigned int m_rowDim = 0;
    unsigned int m_colDim;

    // Constructors
    Vector(T* array, const unsigned int colDim) :
        m_array(array), m_colDim(colDim) {}
    Vector(const unsigned int colDim) : m_colDim(colDim) {}

    // Overloaded () operators for element acceses by indices
    T& operator()(unsigned int i, unsigned int j) override;
    T& operator()(unsigned int j) { return m_array[j]; }

    // Element setters
    void set(unsigned int i, unsigned int j, T value) override;
    void set(unsigned int j, T value) { m_array[j] = value; }

    // Overloaded assignment and move assignment
    Vector<T>& operator=(const Vector<T>& rhs);
    Vector<T>& operator=(Vector<T>&& rhs);

    // Destructor, copy constructor, and move constructor
    ~Vector();
    Vector(const Vector<T>& obj);
    Vector(Vector<T>&& obj);

    // Shortcuts to initialize m_array
    void makeZeros() override;

    // Prints the array
    void print() override;
private:
    // Internal representation of vector
    T* m_array = nullptr;
    void makeCopyOfOther(const Vector<T>& obj);
};

#include "Vector.ipp"

#endif