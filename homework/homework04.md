### Fourth task set

1. To obtain the scalar multiple of a matrix, use the overloaded `multiply` function from ArrayUtils.hpp. See the [software manual entry for multiply](../software_manual/multiply.md). Here is an example usage:
    ```
    const double SCALAR_CONST = 0.5;
    DenseArray<double>* toScale = new DenseArray<double>(5, 5);
    toScale->makeRandom();
    std::cout << "Array to be scaled:" << std::endl;
    toScale->print();

    // Multiply array by scalar
    Array<double>* scaledArray = multiply(SCALAR_CONST, toScale);

    std::cout << "Array scaled by " << SCALAR_CONST << ":" << std::endl;
    scaledArray->print();
    ```
    Output from code above:
    ```
    Array to be scaled:
    0.511361 0.439794 0.615418 0.322499 0.242159 
    0.967718 0.437061 0.678504 0.617304 0.0255087 
    0.725143 0.473234 0.639555 0.00720982 0.175527 
    0.0746027 0.847045 0.278218 0.0142751 0.921693 
    0.899001 0.512843 0.344937 0.348687 0.379236 
    Array scaled by 0.5:
    0.25568 0.219897 0.307709 0.16125 0.12108 
    0.483859 0.21853 0.339252 0.308652 0.0127544 
    0.362571 0.236617 0.319778 0.00360491 0.0877633 
    0.0373013 0.423522 0.139109 0.00713755 0.460847 
    0.449501 0.256421 0.172468 0.174343 0.189618 
    ```
2. To obtain the sum of two matrices of the same size, use the `add` function from ArrayUtils.hpp. See the [software manual entry for add](../software_manual/add.md).
3. To obtain the outer product of two vectors, use the `matmul` function from ArrayUtils.hpp. The arguments will be a vector and a transpose of a vector. Vectors can be transposed with the `transpose` function. See the [software manual entry for transpose](../software_manual/transpose.md). See the [software manual entry for matmul](../software_manual/matmul.md). Here is the example usage for computing an outer product:
    ```
    std::cout << "Vector 1 for outer product:  " << std::endl;
    Vector<double>* vfcp1 = new Vector<double>(5);
    vfcp1->makeRandom();
    vfcp1->print();

    std::cout << "Vector 2 for outer product:  " << std::endl;
    Vector<double>* vfcp2 = new Vector<double>(5);
    vfcp2->makeRandom();
    vfcp2->print();

    std::cout << "Outer product:  " << std::endl;
    Array<double>* outerProductResult = matmul(vfcp1, transpose(vfcp2));
    outerProductResult->print();
    ```
    Output from code above:
    ```
    Vector 1 for outer product:  
    0.805051
    0.488381
    0.215585
    0.338402
    0.517412
    Vector 2 for outer product:  
    0.144707
    0.0868463
    0.62567
    0.631875
    0.92788
    Outer product:  
    0.116496 0.0699157 0.503696 0.508692 0.74699 
    0.070672 0.0424141 0.305565 0.308596 0.453159 
    0.0311966 0.0187228 0.134885 0.136223 0.200037 
    0.048969 0.0293889 0.211728 0.213828 0.313996 
    0.074873 0.0449353 0.323729 0.32694 0.480096 
    ```
4. I implemented a routine called `solveLinearDiagonalSystem` that computes the solution of a square linear system of equations where the coefficient matrix is a diagonal matrix. [See my software manual entry](../software_manual/solveLinearDiagonalSystem.md)
5. I implemented a backsubstitution routine called `backsub` that computes the solution of a square linear system of equations where the coefficient matrix is upper triangular. [See my software manual entry](../software_manual/backsub.md)
6. I implemented a forward substitution routine called `forwardsub` that computes the solution of a square linear system of equations where the coefficient matrix is lower triangular. [See my software manual entry](../software_manual/forwardsub.md)
7. I implemented a routine called `rowReduce` that performs Gaussian elimination on a matrix in order to put it in row echelon form. The routine is overloaded to provide the option of using an augmented coefficient matrix or to do row reduction on any other rectangular matrix. [See my software manual entry](../software_manual/rowReduce.md)
8. I implemented a routine called `solveLinearSystem` that solves a square linear system of equations using Gaussian elimination. This routine utilizes my `rowReduce` and `backsub` routines to find the solution. [See my software manual entry](../software_manual/solveLinearSystem.md)
9. I implemented a method called `makeRandomSymmetricDD` on my DenseArray class template that makes the class instance from which it is called a symmetric diagonally dominant matrix. [See my software manual entry](../software_manual/makeRandomSymmetricDD.md)
10. * I read the Wikipedia article on matrix multiplication at [https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm](https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm). According to the article, one parallilzable algorithm for matrix-matrix multiplication is a divide and conquer algorithm that recursively divides computes the multiplication of submatrices to find the solution. On an ideal computer, this algorithm could speedup the big-theta time complexity by a factor of (1 / (log n) * (log n)). The problem with this algorithm is that it requires a high bandwidth of communication between the parallelized computation nodes, making it impractical. Memory loading and cache misses are frequently the most expensive parts of matrix multiplication with large matrices. A faster parallel algorithm is Cannon's algorithm, which can be run on mesh networks.
    * I also read the article at [http://parallelcomp.uw.hu/ch08lev1sec1.html](http://parallelcomp.uw.hu/ch08lev1sec1.html) which discusses matrix-vector multiplication. It discusses the most obvious way to parallelize matrix-vector multiplication of using one process per row. The runtime for this algorithm is O(n). The article also discusses other ways to parallelize the operation, including one algorithm which uses one process per element in element in the matrix. This algorithm is not cost-optimal.
