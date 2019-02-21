**Class Template Name:** Array<T>

**Parent Class:** None

**Author:** Andrew Aposhian

**Language:** C++

To use the DenseArray class template, include the correct header file at the top of your file as follows:
```
#include "Array.hpp"
```

**Description/Purpose:** This is an abstract class template to be derived from to create usable array wrapper classes.

Note that currently the template is principally designed to be used only for the `Array<double>` class; however it was designed so that it may also be used for integer types etcetera although keep in mind that for now not all methods may function properly with other data types.

**Implementation/Code:**
See [Array.hpp](../src/lib/Array.hpp)

**Last Modified:** February/2019
