#include "random_complex.h"

std::random_device rd;

std::complex<double> random_complex(std::pair<double, double> scope_randRe, std::pair<double, double> scope_randIm) {

    std::uniform_real_distribution<> dis1(scope_randRe.first, scope_randRe.second);
    std::uniform_real_distribution<> dis2(scope_randIm.first, scope_randIm.second);

    double randRe = dis1(rd);
    double randIm = dis2(rd);

    return std::complex<double>(randRe, randIm);
}
