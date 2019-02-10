#include <exception>
#include <algorithm>

// Changes internal array to full form
template <typename T>
void DenseArray<T>::setFull() {
    T** newArray = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        newArray[i] = new T[m_colDim];
        for (unsigned int j = 0; j < m_colDim; j++) {
            newArray[i][j] = (*this)(i, j);
        }
    }
    deleteArrayMember();
    m_array = newArray;
    m_isSymmetricForm = false;
    m_isUpperTriangularForm = false;
    m_isLowerTriangularForm = false;
}

// Changes internal array to symetric form and throws error if
// the existing array is not symmetric
template <typename T>
void DenseArray<T>::setSymmetric() {
    assertSquare();
    // Change to symmetric form
    T** newArray = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        unsigned int rowLength = m_rowDim - i;
        newArray[i] = new T[rowLength];
        for (unsigned int j = 0; j < rowLength; j++) {
            // Assert that the matrix is indeed symmetric
            if ((*this)(i, j) != (*this)(j, i)) {
                std::cout << "Cannot set to symmetric form because array is not symmetric" << std::endl;
                throw std::exception();
            }
            // The jth element of row i in newArray corresponds to
            // column j + i in original array
            newArray[i][j] = (*this)(i, j + i);
        }
    }
    deleteArrayMember(); // Clean up old memory
    m_array = newArray;
    setIsSymmetricForm();
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
        newColIndex = i - j; // Offset for internal triangular form
    }
    else {
        newRowIndex = i;
        newColIndex = j - i; // Offset for internal triangular form
    }
    i = newRowIndex;
    j = newColIndex;
}

// Takes references of row index i and col index j
// and adjusts them to be correct for upper triangular form
// This should only be used by set and operator()!
template <typename T>
void DenseArray<T>::convertToUpperTriangularIndices(unsigned int& i, unsigned int& j) {
    unsigned int newRowIndex;
    unsigned int newColIndex;
    newRowIndex = i;
    newColIndex = j - i; // Offset for internal triangular form
    i = newRowIndex;
    j = newColIndex;
}

// Takes references of row index i and col index j
// and adjusts them to be correct for symmetric form
// This should only be used by set and operator()!
template <typename T>
void DenseArray<T>::convertToLowerTriangularIndices(unsigned int& i, unsigned int& j) {
    unsigned int newRowIndex;
    unsigned int newColIndex;
    // Switch j and i for mirrored element
    newRowIndex = j;
    newColIndex = i - j; // Offset for internal triangular form
    i = newRowIndex;
    j = newColIndex;
}

// Method for setting elements of array
template <typename T>
void DenseArray<T>::set(unsigned int i, unsigned int j, T value) {
    if (isSymmetricForm()) {
        convertToSymmetricIndices(i, j);
    }
    else if (isUpperTriangularForm()) {
        if (i > j) {
            setFull();
        }
        else {
            convertToUpperTriangularIndices(i, j);
        }
    }
    else if (isLowerTriangularForm()) {
        if (j > i) {
            setFull();
        }
        else {
            convertToLowerTriangularIndices(i, j);
        }
    }
    m_array[i][j] = value;
}

// Makes array full form with all elements set to value
template <typename T>
void DenseArray<T>::setAll(T value) {
    if (m_array == nullptr) {
        initializeEmptyArray();
    }
    for (unsigned int i = 0; i < m_rowDim; i++) {
        for (unsigned int j = 0; j < m_colDim; j++) {
            set(i, j, value);
        }
    }
}

// Overloaded () for element access
template <typename T>
T DenseArray<T>::operator()(unsigned int i, unsigned int j) {
    if (isSymmetricForm()) {
        convertToSymmetricIndices(i, j);
    }
    else if (isUpperTriangularForm()) {
        if (i > j) {
            return T();
        }
        else {
            convertToUpperTriangularIndices(i, j);
        }
    }
    else if (isLowerTriangularForm()) {
        if (j > i) {
            return T();
        }
        else {
            convertToLowerTriangularIndices(i, j);
        }
    }
    return m_array[i][j];
}

// Allocates memory for m_array
template <typename T>
void DenseArray<T>::initializeEmptyArray() {
    if (m_array != nullptr) {
        deleteArrayMember();
    }
    m_array = new T*[m_rowDim];
    for (unsigned int i = 0; i < m_rowDim; i++) {
        if (isInternalTriangular()) {
            m_array[i] = new T[m_colDim - i];
        }
        else {
            m_array[i] = new T[m_colDim];
        }
    }
}

// Sets internal triangular array to contain random values between min and max
template <typename T>
void DenseArray<T>::makeRandomInternalTriangular(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
    assertSquare();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        for (unsigned int j = 0; j < m_colDim - i; j++) {
            double randFactor = rand() / static_cast<double>(RAND_MAX);
            double randValue = (randFactor * (max - min)) + min;
            m_array[i][j] = randValue;
        }
    }
}

// Sets to a symmetric matrix containing random values between min and max
template <typename T>
void DenseArray<T>::makeRandomSymmetric(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
    assertSquare();
    // It is important that the form be changed before array initialization
    // so that the correct form of array be allocated
    setIsSymmetricForm();
    initializeEmptyArray();
    makeRandomInternalTriangular(min, max);
}

// Sets to a upper triangular matrix containing random values between min and max
template <typename T>
void DenseArray<T>::makeRandomUpperTriangular(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
    assertSquare();
    // It is important that the form be changed before array initialization
    // so that the correct form of array be allocated
    setIsUpperTriangularForm();
    initializeEmptyArray();
    makeRandomInternalTriangular(min, max);
}

// Sets to a lower triangular matrix containing random values between min and max
template <typename T>
void DenseArray<T>::makeRandomLowerTriangular(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
    assertSquare();
    // It is important that the form be changed before array initialization
    // so that the correct form of array be allocated
    setIsLowerTriangularForm();
    initializeEmptyArray();
    makeRandomInternalTriangular(min, max);
}

// Sets m_array to the identity
template <typename T>
void DenseArray<T>::makeIdentity() {
    assertSquare();
    this->makeZeros();
    for (unsigned int i = 0; i < m_rowDim; i++) {
        set(i, i, 1);
    }
}

// Asserts rowDim equals colDim
template <typename T>
void DenseArray<T>::assertSquare() {
    if (m_rowDim != m_colDim) {
        std::cout << "m_rowDim is not equal to m_colDim" << std::endl;
        throw std::exception();
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
