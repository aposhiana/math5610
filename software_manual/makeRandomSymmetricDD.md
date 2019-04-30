**Method Name:** makeRandomSymmetricDD

**Author:** Andrew Aposhian

**Language:** C++

This method must be called on an instance of a DenseArray of doubles. See [the docs for DenseArray](./DenseArray.md) for details about the DenseArray class template.

**Description/Purpose:** The purpose of this method is to set a DenseArray to contain entries set to random, real floating point values in the range [min, max], such that the matrix is diagonally dominant. The min and max arguments have default values of 0.0 and 1.0 respectively.

**Input:**
1. `min` : a double representing the minimum value to which an entry off the diagonal in the matrix can be set
2. `max` : a double representing the maximum value to which an entry off the diagonal in the matrix can be set. This must be strictly greater than `min`.

**Output:** None

**Usage/Example:** The example below shows instantiating a DenseArray of doubles, calling `makeRandomSymmetricDD` on that DenseArray instance with the default arguments, then printing the array.
```
std::cout << "Symmetric Diagonally Dominant Matrix: " << std::endl;
DenseArray<double>* A_sdd = new DenseArray<double>(4);
A_sdd->makeRandomSymmetricDD();
A_sdd->print();
```

Output from lines above:
```
Symmetric Diagonally Dominant Matrix:
9.37813 0.230214 0.341037 0.382559 
0.230214 9.59098 0.560489 0.96989 
0.341037 0.560489 9.6204 0.626361 
0.382559 0.96989 0.626361 9.46717 
```

**Implementation/Code:**
See [DenseArray.ipp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/DenseArray.ipp)
```
template <typename T>
void DenseArray<T>::makeRandomSymmetricDD(const double offDiagMin, const double offDiagMax) {
    assertSquare();
    assertProperMinMax(offDiagMin, offDiagMax);
    // It is important that the form be changed before array initialization
    // so that the correct form of array be allocated
    setIsSymmetricForm();
    initializeEmptyArray();
    makeRandomInternalTriangular(offDiagMin, offDiagMax);
    double maxAbs = ((std::fabs(offDiagMin) > std::fabs(offDiagMax)) ? offDiagMin : offDiagMax);
    double offset = (rowDim() + 5) * maxAbs;
    for (unsigned int i = 0; i < rowDim(); i++) {
        set(i, i, (*this)(i, i) + offset);
    }
}
```

**Last Modified:** April/2019
