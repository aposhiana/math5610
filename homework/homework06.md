### Sixth task set

1. I implemented a routine called `qrSolve` which computes the solution of a square linear system of equations using the QR factorization. I checked my solutions on 6 x 6 linear systems (after some debugging of the Gram-Schmidt methods) and was able to achieve exactly the same results as my `luSolve` method using the LU factorization. [See my software manual entry](../software_manual/qrSolve.md).
2. I implemented a routine called `squareModifiedGramSchmidt` which uses the modified Gram-Schmidt to compute the QR factorization of a matrix. Interestingly, at least on the small examples which I tested, it typically produced the same results as the classical version of Gram-Schmidt. [See my software manual entry](../software_manual/squareModifiedGramSchmidt.md).
3. Incomplete
4. 
5. 
6. I implemented a routine called `jacobiSolve` that utilizes Jacobi Iteration to approximately solve a linear system of equations. [See my software manual entry](../software_manual/jacobiSolve.md).

    Here is an example problem of 1000 equations with 1000 unknowns. Note that I use the same `A_iterative_large` matrix and `b_iterative_large` vector for the example using Gauss-Seidel in problem 

    ```
    std::cout << "A_iterative_large: " << std::endl;
    DenseArray<double>* A_iterative_large = new DenseArray<double>(1000);
    A_iterative_large->makeRandomSymmetricDD(-100.0, 100.0);
    A_iterative_large->print();

    std::cout << "b_iterative_large for Iterative methods: " << std::endl;
    Vector<double>* b_iterative_large = new Vector<double>(1000);
    b_iterative_large->makeRandom(-100.0, 100.0);
    b_iterative_large->print();
    ```
    The output from the lines above is too large to be included here. [See appendix 1 for the output](./hw06_appendix1.md)

    Below is the code for solving the above system using Jacobi and the corresponding output.
    ```
    Vector<double> x_ji_large = jacobiSolve(*A_iterative_large, *b_iterative_large, 0, 5000);
    std::cout << "x_ji_large found using Jacobi: " << std::endl;
    x_ji_large.print();
    ```
    The output from the lines above is too large to be included here. [See appendix 2 for the output](./hw06_appendix2.md).

7. I implemented a routine called `gaussSeidelSolve` that utilizes Gauss-Seidel Iteration to approximately solve a linear system of equations. [See my software manual entry](../software_manual/gaussSeidelSolve.md).

    Below is the code for solving the system in problem 6 using Gauss-Seidel and the corresponding output.
    ```
    Vector<double> x_gs_large = gaussSeidelSolve(*A_iterative_large, *b_iterative_large, 0, 5000);
    std::cout << "x_gs_large found using Gauss-Seidel: " << std::endl;
    x_gs_large.print();
    ```
    The output from the lines above is too large to be included here. [See appendix 3 for the output](./hw06_appendix3.md).

8. 
9. * I read an article from a faculty member at the University of Illinois at [https://faculty.math.illinois.edu/~hirani/cbmg/linalg2.html](https://faculty.math.illinois.edu/~hirani/cbmg/linalg2.html). The article discusses solving the least squares problem using the normal equation and then discusses the advantages of using the QR algorithm instead. The conditioning of the linear system, as the article explains, depends on the conditioning of the matrix A as well as the angle that the b vector makes with the matrix A. The b vector cannot typically be controlled since it represents the given data, however, the matrix A (or rather the pseudo inverse of A) can be replaced by one that is better conditioned. Orthogonal matrices are very well conditioned, making the QR algorithm much more stable than using the normal equation.
    * I also read the article on Wikipedia for "Numerical methods for linear least squares" at [https://en.wikipedia.org/wiki/Numerical_methods_for_linear_least_squares](https://en.wikipedia.org/wiki/Numerical_methods_for_linear_least_squares). As the article states, methods for solving least squares problems using orthogonal decompositions are more numerically stable because the matrix multiplication of A' with A is not required. However, as the article also states, methods like the QR decomposition are slower than solving the normal equations.
10. * I read the Wikipedia article on the QR decomposition where it discusses different methods for computing the QR decomposition. As the article states, Gram-Shmidt has an intuitively appealing geometric interpretation; however, the process of repeatedly finding the projections is numerically unstable. Householder reflections are a much more numerically stable method of coputing the QR decomposition. One disadvantage that the article states for the Householder reflection algorithm is that it is not easily parallelizable and is bandwidth heavy since every reflection changes all elements of the Q and R matrices. In contrast, Givens rotations are well-suited for parallelizing the QR decomposition. See the article at [https://en.wikipedia.org/wiki/QR_decomposition#Computing_the_QR_decomposition](https://en.wikipedia.org/wiki/QR_decomposition#Computing_the_QR_decomposition).
    * I read portions of the lecture notes for a professor at UC Berkeley available at [https://people.eecs.berkeley.edu/~demmel/ma221_Fall10/Lectures/Lecture_13.html](https://people.eecs.berkeley.edu/~demmel/ma221_Fall10/Lectures/Lecture_13.html). In the notes, it talks about how the modified Gram-Schmidt algorithm when used to produce the QR factorization for a rectangular system frequently will produce a matrix Q that is not orthogonal, although it may yield acceptable results to the least squares problem. This is easily verified by multiplying the resulting Q matrix from modified Gram-Schmidt and observing that the product is not quite the identity. As the article states, Householder reflections and Givens rotations are simple orthogonal matrices which can be used to compute the QR decomposition. Multiplying our matrix with a series of such orthogonal matrices mitigates the risk of losing orthogonality in the process of computing the factorization since "a product of  orthogonal matrices is orthogonal."