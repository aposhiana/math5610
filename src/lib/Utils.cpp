#include <random>

#include "Utils.hpp"

double getRandDouble(const double min, const double max) {
    double randFactor = rand() / static_cast<double>(RAND_MAX);
    return (randFactor * (max - min)) + min;
}
