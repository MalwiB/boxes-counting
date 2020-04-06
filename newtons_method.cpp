#include "newtons_method.h"
#include "NullComplex.h"

std::complex<double> newtons_method(Polynomial polynomial, std::complex<double> starting_point) {
    std::complex<double> z0 = starting_point;
    std::complex<double> z1;
    int iterations = 0;
    double progress;
    std::complex<double> previous;
    do {
        if (iterations == MAX_Newton_I) {
            return NullComplex<double>();
        }
        z1 = z0 - polynomial.count_value(z0) / polynomial.count_derivative_value(z0);
        progress = abs(z1 - z0);
        if(z1 == previous) {    // starting point enters a cycle
            return NullComplex<double>();
        }
        previous = z0;
        z0 = z1;
        ++iterations;
        // show proceeding approximations as output:
        //std::cout << z1 << std::endl;
    } while(progress > MIN_progress);
    return z1;
}
