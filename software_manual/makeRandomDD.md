**Method Name:** makeRandomDD

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
See [DenseArray.ipp on GitHub](https://github.com/aposhiana/math5610/blob/master/src/lib/DenseArray.ipp)
```
template <typename T>
void DenseArray<T>::makeRandomDD(const double min, const double max) {
    assertSquare();
    assertProperMinMax(min, max);
    const double ABS_OF_MIN = abs(min);
    const double ABS_OF_MAX = abs(max);
    const double MAX_ABS = (ABS_OF_MIN > ABS_OF_MAX) ? ABS_OF_MIN : ABS_OF_MAX;
    double minAbs;
    if (min <= 0 && max >= 0) {
        minAbs = 0;
    }
    else {
        minAbs = (ABS_OF_MIN > ABS_OF_MAX) ? ABS_OF_MAX : ABS_OF_MIN;
    }
    const double MIN_ABS = minAbs;

    // Assert value range is valid
    if (MIN_ABS * (colDim() - 1) >= MAX_ABS) {
        std::cout << "Invalid value range to make diagonally dominant array with n = ";
        std::cout << colDim() << " columns: " << std::endl;
        std::cout << "(min absolute val=" << MIN_ABS << ")";
        std::cout << " * (n - 1) >= (max absolute val=" << MAX_ABS << ")" << std::endl;
        throw std::exception();
    }

    initializeEmptyArray();

    const double OFF_DIAG_COUNT = colDim() - 1;

    // For each row
    for (unsigned int i = 0; i < rowDim(); i++) {
        // Get off-diagonal values for row
        std::vector<double> rowVals(OFF_DIAG_COUNT);
        double absRowSum = 0;
        for (unsigned int j = 0; j < OFF_DIAG_COUNT; j++) {
            // Find bounds for value
            double minSumOfRest = absRowSum + ((OFF_DIAG_COUNT - j - 1) * MIN_ABS);
            double maxAbsOfVal = MAX_ABS - minSumOfRest;
            double minBound;
            if (min >= 0 || maxAbsOfVal > ABS_OF_MIN) {
                minBound = min;
            }
            else {
                minBound = -maxAbsOfVal;
            }
            double maxBound;
            if (max <= 0 || maxAbsOfVal > ABS_OF_MAX) {
                maxBound = max;
            }
            else {
                maxBound = maxAbsOfVal;
            }
            // Get a random value
            double randValue;
            do {
                randValue = getRandDouble(minBound, maxBound);
                // Continue to loop to look for a different random value
                // if the new absolute row sum equals MAX_ABS.
                // This guarantees strict diagonal dominance.
                // >= instead of == just for extra safety with 
                // floating point arithmetic.
            } while (abs(randValue) + absRowSum >= MAX_ABS);

            // Save the random value in rowVals
            rowVals[j] = randValue;

            // Update the absolute row sum
            absRowSum += abs(randValue);
        }
        // Randomly permute rowVals
        std::random_shuffle(rowVals.begin(), rowVals.end());

        // Set array values in off-diagonal of row
        for (unsigned int j = 0; j < colDim(); j++) {
            if (j == i) {
                // Skip the diagonal
                continue;
            }
            set(i, j, rowVals.back());
            rowVals.pop_back();
        }

        // Get sign of diagonal value:
        // ABS_OF_MIN > absRowSum and not ABS_OF_MAX > absRowSum
        // implies the random value must be negative.
        // ABS_OF_MAX > absRowSum and not ABS_OF_MIN > absRowSum
        // implies the random value must be positive.
        // If ABS_OF_MIN > absRowSum and ABS_OF_MAX > absRowSum, then
        // the random value can be positive or negative, so we randomly
        // select whether it will be positive or negative.
        bool positive;
        if (ABS_OF_MIN > absRowSum && ABS_OF_MAX > absRowSum) {
            // Randomly select whether value will be positive or negative
            double signSelector = getRandDouble(-1.0, 1.0);
            positive = (signSelector > 0) ? true : false;
        }
        else if (ABS_OF_MIN > absRowSum) {
            positive = false;
        }
        else if (ABS_OF_MAX > absRowSum) {
            positive = true;
        }
        else {
            std::cout << "min and max are equal" << std::endl;
            throw std::exception();
        }
        // Find a random value between min and max with an absolute
        // value greater than absRowSum.
        double randMaxAbs;
        do {
            if (positive) {
                randMaxAbs = getRandDouble(absRowSum, ABS_OF_MAX);
            }
            else {
                randMaxAbs = getRandDouble(-absRowSum, -ABS_OF_MIN);
            }
            // Continue to loop to look for a random value
            // if randMaxAbs value has an absolute value equal
            // to absRowSum. This guarantees strict diagonal dominance.
            // The probablity of this looping is low.
            // <= instead of == just for extra safety with 
            // floating point arithmetic.
        } while (abs(randMaxAbs) <= absRowSum);
        // Set array value on diagonal to the random value
        set(i, i, randMaxAbs);
    }
}
```

**Last Modified:** February/2019
