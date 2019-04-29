**Routine Name:** rowReduce

**Author:** Andrew Aposhian

**Language:** C++

To use this function, include the correct header file at the top of your file as follows:
```
#include "LinearSolvers.hpp"
```

**Description/Purpose:** The purpose of this overloaded routine is to take a matrix and change it to reduced row echelon form. There are two signatures for `rowReduce`. The first accepts a square matrix and corresponding b vector for a linear system and treats them as if they were an augmented coefficient matrix. The second signature can accept rectangular matrices. An exception will be thrown by default if the rectangular matrix is not n x n + 1 dimensional unless the `isLinearSystem` flag is set to false.

**Input:**
*Signature 1:*
1. `A` : an Array of doubles of dimensionality n x n
2. `b` : an Array of doubles of dimensionality n x 1
*Signature 2:*
1. `AB` : an Array of doubles of dimensionality n x (n + 1)
2. `isLinearSystem` : bool set to true by default

**Output:** None. This method modifies the original Array passed to it.

**Usage/Example:** Below is example code that demonstrates all basic uses of `rowReduce`. The first use shows creating and printing a diagonally dominant matrix and b vector, then using `rowReduce` to put the linear system in reduced row echelon form. The matrix and vector are printed afte the reduction. The second use shows creating a random augmented coefficient matrix, then printing it before and after performing `rowReduce` on it. The third use shows creating a random rectangular matrix, then printing it before and after performing `rowReduce` on it.
```
// USE 1
std::cout << "Random DD matrix A_dd0: " << std::endl;
DenseArray<double>* A_dd0 = new DenseArray<double>(3, 3);
A_dd0->makeRandomDD(1.0, 10.0);
A_dd0->print();

std::cout << "b_dd0 for A_dd0 system:  " << std::endl;
Vector<double>* b_dd0 = new Vector<double>(3);
b_dd0->makeRandom(1, 10);
b_dd0->print();

rowReduce(*A_dd0, *b_dd0);
std::cout << "A_dd0 after rowReduce: " << std::endl;
A_dd0->print();
std::cout << "b_dd0 after rowReduce: " << std::endl;
b_dd0->print();

// USE 2
std::cout << "Random augmented coefficient matrix  AB_1 to be reduced: " << std::endl;
DenseArray<double>* AB_1 = new DenseArray<double>(3, 4);
AB_1->makeRandom(1.0, 10.0);
AB_1->print();

std::cout << "AB_1 after row reduction: " << std::endl;
rowReduce(*AB_1);
AB_1->print();

// USE 3
std::cout << "Wide DD Matrix A_wide_dd" << std::endl;
DenseArray<double>* A_wide_dd = new DenseArray<double>(3, 6);
A_wide_dd->makeRandomDDWide(1.0, 10.0);
A_wide_dd->print();

std::cout << "A_wide_dd in echelon form" << std::endl;
rowReduce(*A_wide_dd, false);
A_wide_dd->print();
```

Output from lines above:
```
Random DD matrix A_dd0: 
9.43411 2.35371 6.53936 
2.57943 8.26189 1.20299 
1.12153 7.01968 8.37836 
b_dd0 for A_dd0 system:  
7.59193
9.52191
1.99918
A_dd0 after rowReduce: 
9.43411 2.35371 6.53936 
0 7.61835 -0.58497 
0 0 8.11847 
b_dd0 after rowReduce: 
7.59193
7.44616
-5.49089
Random augmented coefficient matrix  AB_1 to be reduced: 
7.06185 5.50175 4.61396 9.82841 
8.41619 2.93302 9.22008 6.53497 
8.01373 3.81651 4.02855 3.65356 
AB_1 after row reduction: 
7.06185 5.50175 4.61396 9.82841 
0 -3.62388 3.72123 -5.17837 
0 0 -3.69937 -4.03179
Wide DD Matrix A_wide_dd
86.6267 1.90129 7.35662 5.64192 5.58468 7.44538 
7.85637 85.3614 7.48247 9.4153 6.22687 5.57597 
1.03628 5.06808 82.1686 3.74098 5.06627 7.56404 
A_wide_dd in echelon form
86.6267 1.90129 7.35662 5.64192 5.58468 7.44538 
0 85.189 6.81528 8.90362 6.22687 5.57597 
0 0 81.6769 3.14617 5.06627 7.56404
```

**Implementation/Code:**
See [LinearSolvers.cpp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/LinearSolvers.cpp)
```
void rowReduce(DenseArray<double>& A, Vector<double>& b) {
    // TODO: Add scaled partial pivoting
    assertLinearSystem(A, b);
    unsigned int n = A.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = A(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = A(i, pivotIdx) / pivot;
            A.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < n; j++) {
                double oldVal = A(i, j);
                A.set(i, j, oldVal - l * A(pivotIdx, j));
            }
            double oldBVal = b(i);
            b.set(i, oldBVal - l * b(pivotIdx));
        }
    }
}

void rowReduce(DenseArray<double>& AB, bool isLinearSystem) {
    // TODO: Add scaled partial pivoting
    if (isLinearSystem) {
        assertLinearSystem(AB);
    }
    unsigned int n = AB.rowDim();
    for (unsigned int pivotIdx = 0; pivotIdx < n; pivotIdx++) {
        double pivot = AB(pivotIdx, pivotIdx);
        for (unsigned int i = pivotIdx + 1; i < n; i++) {
            double l = AB(i, pivotIdx) / pivot;
            AB.set(i, pivotIdx, 0.0);
            for (unsigned int j = pivotIdx + 1; j < AB.colDim(); j++) {
                double oldVal = AB(i, j);
                AB.set(i, j, oldVal - l * AB(pivotIdx, j));
            }
        }
    }
}
```

**Last Modified:** April/2019
