#include "ArrayInstantiations.hpp"
#include "DenseArray.hpp"
#include "Vector.hpp"

// Explicit instantiations for use in library
template class DenseArray<double>;
template class DenseArray<int>;
template class Vector<double>;
template class Vector<int>;
