#ifndef BOXES_COUNTING_ROOTS_H
#define BOXES_COUNTING_ROOTS_H

#include "Polynomial.h"

const int MAX_Newton_I = 50;  // initial: 100
const double MIN_progress = 0.01;  // initial: 0.001

std::complex<double> newtons_method(Polynomial polynomial, std::complex<double> starting_point);

#endif //BOXES_COUNTING_ROOTS_H