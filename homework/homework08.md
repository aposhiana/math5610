### Eigth task set

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
3. 
4. 
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
