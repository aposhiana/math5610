#include "MachineEpsilon.hpp"

float getMachineEpsilon() {
    float epsilon = 1;
    float nextPossibleEpsilon = epsilon;
    while (nextPossibleEpsilon > 0) {
        epsilon = nextPossibleEpsilon;
        nextPossibleEpsilon /= 2;
    }
    return epsilon;
}

double getDoubleMachineEpsilon() {
    double epsilon = 1;
    double nextPossibleEpsilon = epsilon;
    while (nextPossibleEpsilon > 0) {
        epsilon = nextPossibleEpsilon;
        nextPossibleEpsilon /= 2;
    }
    return epsilon;
}
