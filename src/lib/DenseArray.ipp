#include <iostream>
#include <exception>
#include <algorithm>

// Sets m_array to all zeros
template <typename T>
void DenseArray<T>::makeZeros() {
    T** a = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        a[i] = new T[m_colDim];
        for (unsigned int j = 0; j < m_colDim; j++) {
            a[i][j] = 0;
        }
    }
    m_array = a;
}

// Sets m_array to the identity
template <typename T>
void DenseArray<T>::makeIdentity() {
    if (m_rowDim != m_colDim) {
        std::cout << "Calling makeIdentity on non-square array" << std::endl;
        throw std::exception();
    }
    makeZeros();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        m_array[i][i] = 1;
    }
}

// Destructor
template <typename T>
DenseArray<T>::~DenseArray() {
    if (m_array != nullptr) {
        for (unsigned int i = 0; i < m_rowDim; i++) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }
}

// Prints the array
template <typename T>
void DenseArray<T>::print() {
    // TODO: Format nicer
    for (unsigned int i = 0; i < m_rowDim; i++) {
        for (unsigned int j = 0; j < m_colDim; j++) {
            std::cout << m_array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

// Helper function that makes the instance match the passed object
template <typename T>
void DenseArray<T>::makeCopyOfOther(const DenseArray<T>& obj) {
    m_rowDim = obj.m_rowDim;
    m_colDim = obj.m_colDim;
    m_array = new T*[m_rowDim];
    // Copy all elements of obj to m_array
    for (unsigned int i = 0; i < m_rowDim; i++) {
        m_array[i] = new T[m_colDim];
        for (unsigned int j = 0; j < m_colDim; j++) {
            m_array[i][j] = obj.m_array[i][j];
        }
    }
}

// Copy assignment
template <typename T>
DenseArray<T>& DenseArray<T>::operator=(const DenseArray<T>& rhs) {
    // Check for self-assignment
    if (&rhs != this) {
        delete[] m_array;
        makeCopyOfOther(rhs);
    }
    return *this;
}

// Move assignment
template <typename T>
DenseArray<T>& DenseArray<T>::operator=(DenseArray<T>&& rhs) {
    // Check for self-assignment
    if (&rhs != this) {
        std::swap(m_array, rhs.m_array);
        std::swap(m_rowDim, rhs.m_rowDim);
        std::swap(m_colDim, rhs.m_colDim);
    }
    return *this;
}

// Copy constructor
template <typename T>
DenseArray<T>::DenseArray(const DenseArray<T>& obj) {
    makeCopyOfOther(obj);
}

// Move constructor
template <typename T>
DenseArray<T>::DenseArray(DenseArray<T>&& obj) {
    m_array = obj.m_array;
    m_rowDim = obj.m_rowDim;
    m_colDim = obj.m_colDim;

    obj.m_array = nullptr;
    obj.m_rowDim = 0;
    obj.m_colDim = 0;
}
