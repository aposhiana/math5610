**Class Template Name:** Vector\<T\>

**Parent Class:** [Array\<T\>](./Array.md)

**Author:** Andrew Aposhian

**Language:** C++

To use the Vector class template, include the correct header file at the top of your file as follows:
```
#include "Vector.hpp"
```

**Description/Purpose:** This class template is a wrapper for column vector. It includes various methods that make it easier to use including some quick initialization methods.

Note that currently the template is principally designed to be used only for the `Vector<double>` class; however it was designed so that it may also be used for integer types etcetera although keep in mind that for now not all methods may function properly with other data types.

**Implementation/Code:**
See the following files
[Vector.hpp](../src/lib/Vector.hpp)
[Vector.ipp](../src/lib/Vector.ipp)

**Last Modified:** February/2019
