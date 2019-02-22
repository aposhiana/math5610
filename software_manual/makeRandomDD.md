**Method Name:** makeRandomSymmetric

**Author:** Andrew Aposhian

**Language:** C++

This method must be called on an instance of a DenseArray of doubles. See [the docs for DenseArray](./DenseArray.md) for details about the DenseArray class template.

**Description/Purpose:** The purpose of this method is to set a DenseArray to contain entries set to random real floating point values in the range [min, max], such that the matrix is diagonally dominant. The min and max arguments have default values of 0.0 and 1.0 respectively.

**Input:**
1. `min` : a double representing the minimum value to which an entry in the matrix can be set
2. `max` : a double representing the maximum value to which an entry in the matrix can be set. This must be strictly greater than `min`.

**Output:** None

**Usage/Example:** The example below shows instantiating a DenseArray of doubles, calling makeRandomDD on that DenseArray instance with the default arguments, then printing the array.
```
std::cout << "Random DD Matrix:  " << std::endl;
DenseArray<double>* ddA = new DenseArray<double>(5, 5);
ddA->makeRandomDD(-5, 5);
ddA->print();
```

Output from lines above:
```
Random DD Matrix: 
-4.96466 2.24876 -0.278311 0.0989411 -2.29522 
2.23385 -4.99332 0.0213465 -1.34278 1.39068 
0.0131428 -4.01333 -4.99231 0.566554 -0.394448 
-4.16298 0.473458 0.293169 4.99812 0.0512707 
-0.397526 1.11989 -1.12894 -2.08432 4.9713 
```

**Implementation/Code:**
See [DenseArray.ipp](../src/lib/DenseArray.ipp)

**Last Modified:** February/2019
