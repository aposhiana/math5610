#include <random>

#include <iostream>
#include <exception>

#include "Utils.hpp"

// Gets a random double value between min and max inclusive
double getRandDouble(const double min, const double max) {
    double randFactor = rand() / static_cast<double>(RAND_MAX);
    return (randFactor * (max - min)) + min;
}

// Asserts min < max
void assertProperMinMax(const double min, const double max) {
    if (min >= max) {
        std::cout << "min is not less than max" << std::endl;
        throw std::exception();
    }
}
