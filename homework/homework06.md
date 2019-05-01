### Sixth task set

1. I implemented a routine called `qrSolve` which computes the solution of a square linear system of equations using the QR factorization. I checked my solutions on 6 x 6 linear systems (after some debugging of the Gram-Schmidt methods) and was able to achieve exactly the same (correct) results as my `luSolve` method using the LU factorization. [See my software manual entry](../software_manual/qrSolve.md).
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

7. I implemented a routine called `gaussSeidelSolve` that utilizes Gauss-Seidel Iteration to approximately solve a linear system of equations. [See my software manual entry](../software_manual/gaussSeidelSolve.md).

    Below is the code for solving the system in problem 6 using Gauss-Seidel and the corresponding output.
    ```
    Vector<double> x_gs_large = gaussSeidelSolve(*A_iterative_large, *b_iterative_large, 5000);
    std::cout << "x_gs_large found using Gauss-Seidel: " << std::endl;
    x_gs_large.print();
    ```
    The output from the lines above is too large to be included here. [See appendix 2 for the output](./hw06_appendix2.md).

8. 
9. 
10. 