#include "boxes_algorithm.h"

int main() {
    // polynomial coefficients format: ... = {0, 1, 2, 3}          3 * z^3 + 2 * z^2 + 1 * z^1 + 0

    std::vector<double> coefficients1 = {9, -5, 3, 1};      // initial polynomial

    Polynomial polynomial(coefficients1);
    Scope newtons_method_scopeRe(-10, 10);
    Scope newtons_method_scopeIm(-10, 10);
    polynomial.find_roots(newtons_method_scopeRe, newtons_method_scopeIm);

    Scope fractal_scopeRe(-1, 1);
    Scope fractal_scopeIm(-1, 1);

    Newton_fractal fractal(polynomial, fractal_scopeRe, fractal_scopeIm);
    //fractal.compute_fractal();
    //fractal.draw_fractal();

    boxes_algorithm(fractal);


    write_fractals_dimensions_to_file();

    return 0;
}
