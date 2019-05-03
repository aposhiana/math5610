### Eighth task set

1. I implemented a routine called `powerEigenSolve` that computes the approximate eigenvalue of the largest magnitude for a given square matrix. [See my software manual entry](../software_manual/powerEigenSolve.md). Here is an example usage of the routine on Hilbert matrices of size 5. I verified the result using [this paper](https://www.jstor.org/stable/2003247?seq=3#metadata_info_tab_contents).

    ```
    std::cout << "Hilbert Matrix: " << std::endl;
    DenseArray<double>* A_hilbert = new DenseArray<double>(5);
    A_hilbert->makeHilbert();
    A_hilbert->print();

    double A_hilbert_lambda = powerEigenSolve(*A_hilbert, 0.0001, 10000);
    std::cout << "A_hilbert_lambda found using power method: " << A_hilbert_lambda << std::endl;
    ```
Output from lines above

    ```
    Hilbert Matrix: 
    1 0.5 0.333333 0.25 0.2 
    0.5 0.333333 0.25 0.2 0.166667 
    0.333333 0.25 0.2 0.166667 0.142857 
    0.25 0.2 0.166667 0.142857 0.125 
    0.2 0.166667 0.142857 0.125 0.111111 
    A_hilbert_lambda found using power method: 1.56705
    ```
2. I implemented a routine called `inverseEigenSolve` that computes the approximate eigenvalue closest in magnitude to the shift parameter alpha it is passed for a given square matrix. [See my software manual entry](../software_manual/inverseEigenSolve.md). Here is an example usage of the routine on Hilbert matrices of size 5. I verified the result using [this paper](https://www.jstor.org/stable/2003247?seq=3#metadata_info_tab_contents).

    ```
    std::cout << "Hilbert Matrix: " << std::endl;
    DenseArray<double>* A_hilbert = new DenseArray<double>(5);
    A_hilbert->makeHilbert();

    double A_hilbert_smallest = inverseEigenSolve(*A_hilbert, 0, 0.000001, 10000);
    std::cout << "A_hilbert_smallest found using inverse iteration: " << A_hilbert_smallest << std::endl;
    ```
Output from lines above

    ```
    A_hilbert_smallest found using inverse iteration: 3.30737e-06
    ```
3. I wrote a routine called `estimate2NormConditionNumber` which computes an approximation of the condition in the 2-norm. Testing it on a Hilbert matrix of n = 4 gave a result of 14837.3. [See the software manual entry](../software_manual/estimate2NormConditionNumber.md).
4. I tested the `estimate2NormConditionNumber` routine on Hilbert matrices of increasing sizes. Here were my results:

    ```
    | Hilbert Size | Estimated Kappa |
    |--------------|-----------------|
    | 2            | 19.2815         |
    | 4            | 14833.7         |
    | 6            | 1.46242e+07     |
    | 8            | 1.52529e+10     |
    | 10           | 1.38789e+13     |
    | 12           | 1.74467e+16     |
    ```
5. 
6. I implemented a routine called `rayleighEigenSolve` that computes an approximate eigenvalue for a given square matrix. [See my software manual entry](../software_manual/rayleighEigenSolve.md). Here is an example usage of the routine on Hilbert matrices of size 5. I verified the result using [this paper](https://www.jstor.org/stable/2003247?seq=3#metadata_info_tab_contents).
    ```
    std::cout << "Hilbert Matrix: " << std::endl;
    DenseArray<double>* A_hilbert = new DenseArray<double>(5);
    A_hilbert->makeHilbert();

    double A_hilbert_rayleigh = rayleighEigenSolve(*A_hilbert, 0.000001, 1000);
    std::cout << "eigenvalue for hilbert found with Rayleigh Quotient Iteration: " << A_hilbert_rayleigh << std::endl;
    ```
Output from lines above
    ```
    eigenvalue for hilbert found with Rayleigh Quotient Iteration: 1.56705
    ```
7. 
8. * I read an article by ALGLIB, a numerical analysis library, at [http://www.alglib.net/matrixops/rcond.php](http://www.alglib.net/matrixops/rcond.php) which discusses on a high level how they estimate the condition number. What I found interesting is that their algorithms compute an LU or Cholesky factorization of the matrix in the process of computing the condition number unless the matrix is already factorized. In fact, they note that with only the factorization and not the original matrix their estimating techniques are less precise. This illustrates how the computing the condition number in practice is likely not useful since it likely requires the same amount of work as solving the linear system at hand.
    * In a blog post by Cleve Moler at [https://blogs.mathworks.com/cleve/2017/07/17/what-is-the-condition-number-of-a-matrix/](https://blogs.mathworks.com/cleve/2017/07/17/what-is-the-condition-number-of-a-matrix/), he discusses the basic concepts of the condition number. He mentions how computing the condition number takes O(n^3) operations as it involves computing the inverse of the matrix.
9. I tested my routines for inverse iteration and Rayleigh iteration on various sizes of random matrices and compared the time they took to solve for eigenvalues with a tolerance of 1e-6 and a maximum of 1000 iterations. The Rayleigh iteration routine, as expected, performs increasingly much slower than the inverse iteration routine as the sizes of the matrices increases. My results are tabulated below. Note that the times are listed under the names of the algorithm and are in seconds.

    ```
    | Matrix size | Inverse iteration | Rayleigh iteration |
    |-------------|--------------- ---|--------------------|
    | 100         | 0.0161625         | 12.9778            |
    | 200         | 0.882786          | 25.6918            |
    | 300         | 1.85088           | 315.301            |
    ```

    Below is the code I used to perform the tests. For the timing methods, I `#`-included `chrono` from the C++ standard library.

    ```
    for (unsigned int size = 100; size < 400; size += 100) {
        DenseArray<double>* A_eig_timing = new DenseArray<double>(size);
        A_eig_timing->makeRandom(-100, 100);

        auto invStart = std::chrono::high_resolution_clock::now();
        double eig_inv = inverseEigenSolve(*A_eig_timing, 0, 0.000001, 1000);
        auto invEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> invTime = invEnd - invStart;
        std::cout << "Inverse time for " << size << ": " << invTime.count() << std::endl;

        auto rayStart = std::chrono::high_resolution_clock::now();
        double eig_ray = rayleighEigenSolve(*A_eig_timing, 0.000001, 1000);
        auto rayEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> rayTime = rayEnd - rayStart;
        std::cout << "Rayleigh time for " << size << ": " << rayTime.count() << std::endl;
    }
    ```
10. I implemented a version of the Inverse iteration algorithm that uses Jacobi iteration called `inverseEigenJacobiSolve`. I tested this routine using a random diagonally dominant matrix as is shown in the example in the software manual. [See my software manual entry](../software_manual/inverseEigenJacobiSolve.md).
