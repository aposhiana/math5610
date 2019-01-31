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

template <typename T>
DenseArray<T>::~DenseArray() {
    if (m_array != nullptr) {
        for (unsigned int i = 0; i < m_rowDim; i++) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }
}