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
    Output:
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
3. 