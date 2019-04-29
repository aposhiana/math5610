#ifndef _DENSE_ARRAY_HPP_
#define _DENSE_ARRAY_HPP_

#include "Array.hpp"

template<typename T>
class DenseArray : public Array<T> {
public:
    // Getters
    unsigned int colDim() const override { return m_colDim; }
    unsigned int rowDim() const override { return m_rowDim; }
    bool isSymmetricForm() { return m_isSymmetricForm; }
    bool isUpperTriangularForm() { return m_isUpperTriangularForm; }
    bool isLowerTriangularForm() { return m_isLowerTriangularForm; }
    T** getRawArray() override { return m_array; }

    // Constructors
    DenseArray(const unsigned int rowDim,
                    const unsigned int colDim, bool init=false) :
        m_rowDim(rowDim), m_colDim(colDim)
        { if (init) { initializeEmptyArray(); }}
    DenseArray(T** array, const unsigned int rowDim,
                    const unsigned int colDim, bool init=false) :
        m_array(array), m_rowDim(rowDim), m_colDim(colDim)
        { if (init) { initializeEmptyArray(); }}

    // Shortcut constructors for square arrays
    DenseArray(const unsigned int axesDim) :
        DenseArray(axesDim, axesDim) {}
    DenseArray(T** array, const unsigned int axesDim) :
        DenseArray(array, axesDim, axesDim) {}

    // Overloaded () operator for element acceses by indices
    T operator()(unsigned int i, unsigned int j) override;
    // Element setter
    void set(unsigned int i, unsigned int j, T value) override;
    void setAll(T value) override;

    // Shortcuts to initialize m_array values
    void makeRandomDD(const double min=0.0, const double max=1.0);
    void makeRandomDDWide(const double min=0.0, const double max=1.0);
    void makeRandomSymmetric(const double min=0.0, const double max=1.0);
    void makeRandomSymmetricDD(const double offDiagMin=0.0, const double offDiagMax=1.0);
    void makeRandomUpperTriangular(const double min=0.0, const double max=1.0);
    void makeRandomLowerTriangular(const double min=0.0, const double max=1.0);
    void makeRandomAugmentedEchelon(const double min=0.0, const double max=1.0);
    void makeIdentity();
    void makeHilbert();

    // Methods to change internal array form
    void makeFullForm();
    void makeSymmetricForm();
    // void setLowerTriangular();
    // void setUpperTriangular();

    // Prints the array
    void print() override;

    // Overloaded assignment and move assignment
    DenseArray<T>& operator=(const DenseArray<T>& rhs);
    DenseArray<T>& operator=(DenseArray<T>&& rhs);
    // Destructor, copy constructor, and move constructor
    ~DenseArray();
    DenseArray(const DenseArray<T>& obj);
    DenseArray(DenseArray<T>&& obj);

private:
    // Internal representation of array
    T** m_array = nullptr;

    // Dimensionality of array
    unsigned int m_rowDim;
    unsigned int m_colDim;

    // Flags indicating the internal-array form
    bool m_isSymmetricForm = false;
    bool m_isUpperTriangularForm = false;
    bool m_isLowerTriangularForm = false;
    bool isInternalTriangular() {
        return (isSymmetricForm() || isUpperTriangularForm() || isLowerTriangularForm());
    }

    // Internal-array-form flag setters
    void setIsFullForm() {
        m_isSymmetricForm = false;
        m_isUpperTriangularForm = false;
        m_isLowerTriangularForm = false;
    }
    void setIsSymmetricForm() {
        m_isSymmetricForm = true;
        m_isUpperTriangularForm = false;
        m_isLowerTriangularForm = false;
    }
    void setIsUpperTriangularForm() {
        m_isSymmetricForm = false;
        m_isUpperTriangularForm = true;
        m_isLowerTriangularForm = false;
    }
    void setIsLowerTriangularForm() {
        m_isSymmetricForm = false;
        m_isUpperTriangularForm = false;
        m_isLowerTriangularForm = true;
    }

    // Helper methods
    void deleteArrayMember();
    void initializeEmptyArray() override;
    void convertToSymmetricIndices(unsigned int& i, unsigned int& j);
    void convertToUpperTriangularIndices(unsigned int& i, unsigned int& j);
    void convertToLowerTriangularIndices(unsigned int& i, unsigned int& j);
    void makeCopyOfOther(const DenseArray<T>& obj);
    void makeRandomInternalTriangular(const double min=0.0, const double max=1.0);
    void assertSquare();
};

#include "DenseArray.ipp"

#endif
