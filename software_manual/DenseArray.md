**Class Template Name:** DenseArray\<T\>

**Parent Class:** [Array\<T\>](./Array.md)

**Author:** Andrew Aposhian

**Language:** C++

To use the DenseArray class template, include the correct header file at the top of your file as follows:
```
#include "DenseArray.hpp"
```

**Description/Purpose:** This class template is a wrapper for a two dimensional array. It includes various methods that make it easier to use including some quick initialization methods.

Note that currently the template is principally designed to be used only for the `DenseArray<double>` class; however it was designed so that it may also be used for integer types etcetera although keep in mind that for now not all methods may function properly with other data types.

**Implementation/Code:**
See the following files on GitHub
[DenseArray.hpp](https://github.com/aposhiana/math5610/blob/master/src/lib/DenseArray.hpp)
[DenseArray.ipp](https://github.com/aposhiana/math5610/blob/master/src/lib/DenseArray.ipp)

**Last Modified:** February/2019
