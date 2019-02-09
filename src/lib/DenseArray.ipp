#include <exception>
#include <algorithm>

// Change internal array to symetric form and throw error if
// the existing array is not symmetric
template <typename T>
void DenseArray<T>::setSymmetric() {
    // Assert that the matrix is allegedly square
    if (m_rowDim != m_colDim) {
        std::cout << "Symmetric set to true but m_rowDim is not equal to m_colDim" << std::endl;
        throw std::exception();
    }
    // Change to symmetric form
    T** newArray = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        unsigned int rowLength = m_rowDim - i;
        newArray[i] = new T[rowLength];
        for (unsigned int j = 0; j < rowLength; j++) {
            // Assert that the matrix is indeed symmetric
            if (m_array[i][j] != m_array[j][i]) {
                std::cout << "Symmetric set to true but m_array is not symmetric" << std::endl;
                throw std::exception();
            }
            // The jth element of row i in newArray corresponds to
            // column j + i in original m_array
            newArray[i][j] = m_array[i][j + i];
        }
    }
    deleteArrayMember(); // Clean up old memory
    m_array = newArray;
    m_isSymmetricForm = true;
}

// Takes references of row index i and col index j
// and adjusts them to be correct for symmetric form
// This should only be used by set and operator()!
template <typename T>
void DenseArray<T>::convertToSymmetricIndices(unsigned int& i, unsigned int& j) {
    unsigned int newRowIndex;
    unsigned int newColIndex;
    if (j < i) {
        // Switch j and i for mirrored element
        newRowIndex = j;
        newColIndex = i - j; // Offset for symmetric form
    }
    else {
        newRowIndex = i;
        newColIndex = j - i; // Offset for symmetric form
    }
    i = newRowIndex;
    j = newColIndex;
}

// Method for setting elements of array
template <typename T>
void DenseArray<T>::set(unsigned int i, unsigned int j, T value) {
    if (m_isSymmetricForm) {
        convertToSymmetricIndices(i, j);
    }
    m_array[i][j] = value;
}

// Sets all elements of m_array to the value
template <typename T>
void DenseArray<T>::setAll(T value) {
    initializeEmptyArray();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        for (unsigned int j = 0; j < m_colDim; j++) {
            set(i, j, value);
        }
    }
}

// Overloaded () for element access
template <typename T>
T& DenseArray<T>::operator()(unsigned int i, unsigned int j) {
    if (m_isSymmetricForm) {
        convertToSymmetricIndices(i, j);
    }
    return m_array[i][j];
}

// Allocates memory for m_array
template <typename T>
void DenseArray<T>::initializeEmptyArray() {
    if (m_array != nullptr) {
        return;
    }
    m_array = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        m_array[i] = new T[m_colDim];
    }
}

// Sets m_array to the identity
template <typename T>
void DenseArray<T>::makeIdentity() {
    if (m_rowDim != m_colDim) {
        std::cout << "Calling makeIdentity on non-square array" << std::endl;
        throw std::exception();
    }
    this->makeZeros();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        set(i, i, 1);
    }
}

// Deletes m_array
template <typename T>
void DenseArray<T>::deleteArrayMember() {
    if (m_array != nullptr) {
        for (unsigned int i = 0; i < m_rowDim; i++) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }
    m_array = nullptr;
}

// Destructor
template <typename T>
DenseArray<T>::~DenseArray() {
    deleteArrayMember();
}

// Prints the array
template <typename T>
void DenseArray<T>::print() {
    if (m_array == nullptr) {
        std::cout << "Internal array not set" << std::endl;
        return;
    }
    // TODO: Format nicer
    for (unsigned int i = 0; i < m_rowDim; i++) {
        for (unsigned int j = 0; j < m_colDim; j++) {
            // Use () operator to handle symmetric matrices
            std::cout << (*this)(i, j) << ' ';
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
        deleteArrayMember();
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
