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
8. Douglas N. Arnold, former president of SIAM, describes several disasters that have occurred due to numerical computing mistakes. The descriptions can be found [here](http://www-users.math.umn.edu/~arnold//disasters/). Here are summaries of the disasters:

    **1) Patriot Missile failure.** During the Gulf War, a Patriot Missile failed to intercept an Iraqi missile, resulting in 28 soldiers being killed, around 100 others being injured, and the destruction of a US Army barracks. The failure was due to accumulating error in the system's clock which occurred because of a multiplication every second by 1/10 done to compute time in seconds. The error accumulated because the value 1/10 has a non-terminal binary expansion, but it was only stored using 24 bits of precision. The truncation introduced error in the result every time the multiplication was made.

    **2) Explosion of Ariane 5 rocket.** In 1996, the Ariane 5 rocket exploded after lift off. The failure was due to a software error where a 64-bit floating point number was converted to a 16-bit integer. The number was larger than the 16-bit integer could hold causing the conversion to fail. The development of the rocket had taken 10 years and costed \$7 billion in development and \$500 million for the rocket and its cargo.

    **3) Sinking of the Sleipner A offshore platform.** The sinking ot the Sleipner A platform was due to the failure of a concrete structure known as a tricell. The tricells form part of the cell structure which supports the platform and raises it above the sea-floor. The tricell was not designed sufficiently strong, causing a cell wall to break and let in excessive water. The reason for the insufficient design was an incorrect finite element analysis computation done to analyze the stresses on the tricell. The computation was done using a popular finite element analysis program.
9.
10. NumPy LAPACK Eigen Armadillo

solving linear systems
solving for eigenvalues
matrix multiplication
