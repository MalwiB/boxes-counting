#ifndef BOXES_COUNTING_NEWTON_FRACTAL_H
#define BOXES_COUNTING_NEWTON_FRACTAL_H

#include <fstream> // ofstream
#include "Polynomial.h"

static int fractals_number = 0;

class Newton_fractal {
private:
    void save_points_to_basins();
    void draw_basins_of_attraction(FILE* gnuplot_pipe);
    void set_basins_colors(FILE* gnuplot_pipe);
    void set_plot_options(FILE* gnuplot_pipe);

public:
    Polynomial polynomial;
    std::vector<std::complex<double>>* basins_of_attraction;

    Scope scopeRe;
    Scope scopeIm;

    int resolutionRe = 2000;  // initial: 2000, quite precise resolution, minimal resolution: 1200
    int resolutionIm;

    Newton_fractal(Polynomial a_polynomial, Scope a_scopeRe, Scope a_scopeIm);

    std::complex<double> determine_root(std::complex<double> root);

    void compute_fractal();
    void draw_fractal();
};

#endif //BOXES_COUNTING_NEWTON_FRACTAL_H