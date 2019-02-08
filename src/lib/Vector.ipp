#include <iostream>
#include <exception>

// Overriden method for getting element in m_array
template <typename T>
T& Vector<T>::operator()(unsigned int i, unsigned int j) {
    if (i != 0) {
        std::cout << "Row index for Vector set must be 0 or omitted" << std::endl;
        throw std::exception();
    }
    return m_array[j];
}

// Overriden method for setting element in m_array
template <typename T>
void Vector<T>::set(unsigned int i, unsigned int j, T value) {
    if (i != 0) {
        std::cout << "Row index for Vector set must be 0 or omitted" << std::endl;
        throw std::exception();
    }
    m_array[j] = value;
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    delete[] m_array;
}

// Helper function that makes the instance match the passed object
template <typename T>
void Vector<T>::makeCopyOfOther(const Vector<T>& obj) {
    // m_rowDim = obj.m_rowDim;
    m_colDim = obj.m_colDim;
    m_array = new T[m_colDim];
    // Copy all elements of obj to m_array
    for (unsigned int j = 0; j < m_rowDim; j++) {
        m_array[j] = obj.m_array[j];
    }
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T>& obj) {
    makeCopyOfOther(obj);
}

// Move constructor
template <typename T>
Vector<T>::Vector(Vector<T>&& obj) {
    m_array = obj.m_array;
    // m_rowDim = obj.m_rowDim;
    m_colDim = obj.m_colDim;

    obj.m_array = nullptr;
    // obj.m_rowDim = 0;
    obj.m_colDim = 0;
}

// Copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    // Check for self-assignment
    if (&rhs != this) {
        delete[] m_array;
        makeCopyOfOther(rhs);
    }
    return *this;
}

// Move assignment
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) {
    // Check for self-assignment
    if (&rhs != this) {
        std::swap(m_array, rhs.m_array);
        // std::swap(m_rowDim, rhs.m_rowDim);
        std::swap(m_colDim, rhs.m_colDim);
    }
    return *this;
}

// Sets m_array to all zeros
template <typename T>
void Vector<T>::makeZeros() {
    if (m_array == nullptr) {
        m_array = new T[m_colDim];
    }
    for (unsigned int j = 0; j < m_colDim; j++) {
        m_array[j] = 0;
    }
}

// Prints the array
template <typename T>
void Vector<T>::print() {
    if (m_array == nullptr) {
        std::cout << "internal array not set" << std::endl;
        return;
    }
    for (unsigned int j = 0; j < m_colDim; j++) {
        std::cout << m_array[j] << std::endl;
    }
}
