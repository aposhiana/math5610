### First task set
1. I wrote two routines, `getMachineEpsilon` and `getDoubleMachineEpsilon`, both of which are defined in `MachineEpsilon.hpp`. They return the machine epsilon for single and double precision floating point data types respectively. See the software manual entries for [getMachineEpsilon](../software_manual/getMachineEpsilon) and [getDoubleMachineEpsilon](../software_manual/getDoubleMachineEpsilon)
2. I created my GitHub repository for this class. [See the repository's root directory](https://github.com/aposhiana/math5610).
3. I enabled GitHub Pages for my math5610 repository. [See the math5610 Pages site](https://aposhiana.github.io/math5610/).
4. I copied the software manual template file into my software_manual directory. [See the template file](../software_manual/softwareManualTemplate).
5. I created tables of contents for my homeworks and my software manual. [See the homework table of contents](). [See the software manual table of contents](../software_manual/README).
6. I used CMake and clang++ to compile my routines into a static library archive file. [See the build directory]().
7. I wrote a Hello World program to test OpenMP with C++ on my Mac. [See the source code for my program](../src/toy_programs/multicore_hello.cpp). To use OpenMP with C++ on macOS, I used the clang++ compiler. Here is an example command for compiling with OpenMP functionality using clang++:
    ```
    clang++ -Xpreprocessor -fopenmp my_program.cpp -o MyProgram -lomp
    ```
    Below is an example usage sequence of the Hello World program, demonstrating the commands to compile and run the program along with the expected output. You can see that I have 4 cores on my computer.
    ```
    $ ls
    multicore_hello.cpp
    $ clang++ -Xpreprocessor -fopenmp multicore_hello.cpp -o    Hello -lomp
    $ ls
    Hello			multicore_hello.cpp
    $ ./Hello 
    Hello world
    Hello world
    Hello world
    Hello world
    ```
8. Douglas N. Arnold, former president of SIAM, describes several disasters that have occurred due to numerical computing mistakes. The descriptions can be found [here](http://www-users.math.umn.edu/~arnold//disasters/). Here are summaries of the disasters:

    1. **Patriot Missile failure.** During the Gulf War, a Patriot Missile failed to intercept an Iraqi missile, resulting in 28 soldiers being killed, around 100 others being injured, and the destruction of a US Army barracks. The failure was due to accumulating error in the system's clock which occurred because of a multiplication every second by 1/10 done to compute time in seconds. The error accumulated because the value 1/10 has a non-terminal binary expansion, but it was only stored using 24 bits of precision. The truncation introduced error in the result every time the multiplication was made.

    2. **Explosion of Ariane 5 rocket.** In 1996, the Ariane 5 rocket exploded after lift off. The failure was due to a software error where a 64-bit floating point number was converted to a 16-bit integer. The number was larger than the 16-bit integer could hold causing the conversion to fail. The development of the rocket had taken 10 years and costed \$7 billion in development and \$500 million for the rocket and its cargo.

    3. **Sinking of the Sleipner A offshore platform.** The sinking ot the Sleipner A platform was due to the failure of a concrete structure known as a tricell. The tricells form part of the cell structure which supports the platform and raises it above the sea-floor. The tricell was not designed sufficiently strong, causing a cell wall to break and let in excessive water. The reason for the insufficient design was an incorrect finite element analysis computation done to analyze the stresses on the tricell. The computation was done using a popular finite element analysis program.
9. I wrote a utility function called `makeRandomArray` that takes row and column dimensions as parameters and returns an array with its elements set to random values between 0 and 1. [See the software manual entry](../software_manual/makeRandomArray).
10. 
    Some important problems that I think we will cover in this class include solving linear systems of equations, solving for eigenvalues, and (more fundamentally) matrix multiplication. The following three websites give some information about these tasks as they are implemented in various libraries:
    
    1. The website [https://www.netlib.org/lapack/lug/node68.html](https://www.netlib.org/lapack/lug/node68.html) discusses the speed of different matrix factorizations used to solve linear systems of equations in the library LAPACK. The article compares the speed of the algorithms when using different block sizes. Solving systems of linear equations using block methods or matrix factorizations may allow for the use of several sparse matrices rather than a single, large dense one, thus helping decrease memory usage and the number of operations.

    2. At the website [http://gallery.rcpp.org/articles/armadillo-eigenvalues/](http://gallery.rcpp.org/articles/armadillo-eigenvalues/), Dirk Eddelbuettel discusses the linear algebra packages used behind the scenes by R and Rcpp to compute eigenvalues. R is a very popular high level language for statistics. Rcpp is an extension to the R language. R uses a package called BLAS (Basic Linear Algebra Subprograms), which is written in Fortran and C. Rcpp also allows access to the Armadillo library, which is a linear algebra library for C++.

    3. The website [https://martin-thoma.com/matrix-multiplication-python-java-cpp/](https://martin-thoma.com/matrix-multiplication-python-java-cpp/) compares the speeds of different algorithms for matrix multiplication as implemented in various linear algebra libraries. The library implementations are also compared to custom implementations: the "ijk-algorithm" and the "ikj-algorithm". For Python, NumPy and SciPy perform much faster than the custom implementations shown. Using Numpy and SciPy is also very simple which is good. For Java, the custom ikj-algorithm is much faster than the custom ijk-algorithm, but the JAMA library function is still faster. For C++, the Boost library function for matrix multiplication was slower than the custom implementations.

