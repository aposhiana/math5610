**Method Name:** makeRandomSymmetric

**Author:** Andrew Aposhian

**Language:** C++

This method must be called on an instance of a DenseArray of doubles. See [the docs for DenseArray](./DenseArray.md) for details about the DenseArray class template.

**Description/Purpose:** The purpose of this method is to set a DenseArray to contain entries set to random real floating point values in the range [min, max]. The min and max arguments have default values of 0.0 and 1.0 respectively.

**Input:**
1. `min` : a double representing the minimum value to which an entry in the matrix can be set
2. `max` : a double representing the maximum value to which an entry in the matrix can be set. This must be strictly greater than `min`.

**Output:** None

**Usage/Example:** The example below shows instantiating a DenseArray of doubles, calling makeRandomSymmetric on that DenseArray instance with the default arguments, then printing the array.
```
// Using default min and max
std::cout << "symmetric: " << std::endl;
DenseArray<double>* sym = new DenseArray<double>(5, 5);
sym->makeRandomSymmetric();
sym->print();

// Using other min and max
std::cout << "symmetric non-default: " << std::endl;
DenseArray<double>* symNonDef = new DenseArray<double>(5, 5);
symNonDef->makeRandomSymmetric();
symNonDef->print();

```

Output from lines above:
```
symmetric: 
0.200392 0.993509 0.913913 0.135969 0.227782 
0.993509 0.332465 0.733959 0.647183 0.201933 
0.913913 0.733959 0.888492 0.888938 0.37583 
0.135969 0.647183 0.888938 0.580875 0.766615 
0.227782 0.201933 0.37583 0.766615 0.490416 
symmetric non-default: 
6.16455 4.6152 4.65097 5.7746 6.75435 
4.6152 5.3819 6.5474 7.21746 4.79049 
4.65097 6.5474 6.83314 5.56579 5.23679 
5.7746 7.21746 5.56579 7.67036 4.7491 
6.75435 4.79049 5.23679 4.7491 7.20306 
```

**Implementation/Code:**
See [DenseArray.ipp](../src/lib/DenseArray.ipp)

**Last Modified:** February/2019
