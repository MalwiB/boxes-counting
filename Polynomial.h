#ifndef BOXES_COUNTING_POLYNOMIAL_H
#define BOXES_COUNTING_POLYNOMIAL_H

#include <iostream>
#include <complex>
#include <vector>

const double MAX_SAME_ROOT_DISTANCE = 0.1;

typedef std::pair<double, double> Scope;

class Polynomial {
private:
    int degree;
    std::vector<double> coefficients;
    std::vector<double> derivative_coefficients;

    void count_derivative_coefficients();
    bool is_root_in_set(std::complex<double> root);

public:
    int number_of_roots;
    std::vector<std::complex<double>> roots;

    std::pair<int, int> scope_randRe;
    std::pair<int, int> scope_randIm;

    Polynomial() {};
    Polynomial(std::vector<double> a_coefficients);

    std::complex<double> count_value(std::complex<double> x);
    std::complex<double> count_derivative_value(std::complex<double> x);

    void find_roots(Scope a_scope_randRe, Scope a_scope_randIm);

};

#endif //BOXES_COUNTING_POLYNOMIAL_H