### First task set
1. I wrote two routines, `getMachineEpsilon` and `getDoubleMachineEpsilon`, both of which are defined in `MachineEpsilon.hpp`. They return the machine epsilon for single and double precision floating point data types respectively. See the documentation for [getMachineEpsilon](../software_manual/getMachineEpsilon.md) and [getDoubleMachineEpsilon](getDoubleMachineEpsilon.md)
2. I created my GitHub repository for this class. [See the repository's root directory](https://github.com/aposhiana/math5610).
3. I enabled GitHub Pages for my math5610 repository. [See the math5610 Pages site](https://aposhiana.github.io/math5610/).
4. I copied the software manual template file into my software_manual directory. [See the template file](../software_manual/softwareManualTemplate.md).
5. I created tables of contents for my homeworks and my software manual. [See the homework table of contents](). [See the software manual table of contents](../software_manual/README.md).
6. I used CMake and g++ to compile my routines into a static library archive file. [See the build directory]().
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
8.
9.
10. NumPy LAPACK Eigen Armadillo

solving linear systems
solving for eigenvalues
matrix multiplication
