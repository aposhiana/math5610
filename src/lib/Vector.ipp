#include <exception>

// Allocates memory for m_array
template <typename T>
void Vector<T>::initializeEmptyArray() {
    if (m_array != nullptr) {
        return;
    }
    m_array = new T[m_rowDim];
}

// Overriden method for getting element in m_array
template <typename T>
T Vector<T>::operator()(unsigned int i, unsigned int j) {
    if (j != 0) {
        std::cout << "Column index for Vector must be 0 or omitted" << std::endl;
        throw std::exception();
    }
    return m_array[i];
}

// Overriden method for setting element in m_array
template <typename T>
void Vector<T>::set(unsigned int i, unsigned int j, T value) {
    if (j != 0) {
        std::cout << "Column index for Vector must be 0 or omitted" << std::endl;
        throw std::exception();
    }
    m_array[i] = value;
}

// Sets m_array to all zeros
template <typename T>
void Vector<T>::setAll(T value) {
    initializeEmptyArray();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        set(i, value);
    }
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    delete[] m_array;
}

// Helper function that makes the instance match the passed object
template <typename T>
void Vector<T>::makeCopyOfOther(const Vector<T>& obj) {
    m_rowDim = obj.m_rowDim;
    m_array = new T[m_rowDim];
    // Copy all elements of obj to m_array
    for (unsigned int i = 0; i < m_rowDim; i++) {
        m_array[i] = obj.m_array[i];
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
    m_rowDim = obj.m_rowDim;

    obj.m_array = nullptr;
    obj.m_rowDim = 0;
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
        std::swap(m_rowDim, rhs.m_rowDim);
    }
    return *this;
}

// Prints the array
template <typename T>
void Vector<T>::print() {
    if (m_array == nullptr) {
        std::cout << "internal array not set" << std::endl;
        return;
    }
    for (unsigned int i = 0; i < m_rowDim; i++) {
        std::cout << (*this)(i) << std::endl;
    }
}
