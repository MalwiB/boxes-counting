#include "Newton_fractal.h"
#include "newtons_method.h"
#include "NullComplex.h"

Newton_fractal::Newton_fractal(Polynomial a_polynomial, std::pair<double, double> a_scopeRe, std::pair<double, double> a_scopeIm) {
    polynomial = a_polynomial;

    int number_of_basins = polynomial.number_of_roots+1;
    basins_of_attraction = new std::vector<std::complex<double>>[number_of_basins];

    scopeRe = a_scopeRe;
    scopeIm = a_scopeIm;

    resolutionIm = (int)(resolutionRe * fabs(scopeIm.first - scopeIm.second) / fabs(scopeRe.first - scopeRe.second));

    fractals_number++;
}

// because of approximation in Newtons_method, points in the same basin of attraction
// may have coinciding, but not exactly the same roots
// determine_root function purpose is to evaluate which root correspond to approximated root
// and return exact root
// then it is possible to save point to basin of that root, in method save_points_to_basins
std::complex<double> Newton_fractal::determine_root(std::complex<double> root) {
    std::vector<std::complex<double>>::iterator it;
    for (it = polynomial.roots.begin(); it != polynomial.roots.end(); ++it) {
        if (abs(root - *it) < MAX_SAME_ROOT_DISTANCE)
            return *it;
    }
    return NullComplex<double>();
}

void Newton_fractal::save_points_to_basins() {
    double increaseRe = fabs(scopeRe.first - scopeRe.second) / resolutionRe;
    double increaseIm = fabs(scopeIm.first - scopeIm.second) / resolutionIm;
    std::cout << "increaseRe: " << increaseRe << std::endl;
    std::cout << "increaseIm: " << increaseIm << std::endl << std::endl;
    for (double i=scopeRe.first; i<=scopeRe.second; i+=increaseRe) {
        for (double j=scopeIm.first; j<=scopeIm.second; j+=increaseIm) {
            std::complex<double> root = newtons_method(polynomial, std::complex<double>(i, j));
            static NullComplex<double> null_obj;
            if (root == null_obj)
                basins_of_attraction[0].push_back(std::complex<double>(i, j));
            else {
                for (int k = 0; k < polynomial.number_of_roots; k++) {
                    if (abs(root - polynomial.roots[k]) < MAX_SAME_ROOT_DISTANCE) {
                        basins_of_attraction[k+1].push_back(std::complex<double>(i, j));
                        break;
                    }
                }
            }
        }
    }
}

void Newton_fractal::compute_fractal() {
    std::cout << "Saving points to basins of attraction..." << std::endl << std::endl;
    save_points_to_basins();
    std::cout << "Points saved to basins of attraction." << std::endl << std::endl << std::endl;

}


void Newton_fractal::draw_basins_of_attraction(FILE* gnuplot_pipe) {
    for (int i = 0; i <= polynomial.number_of_roots; i++) {
        for (std::complex<double> point : basins_of_attraction[i]) {
            std::string point_str = std::to_string(point.real());
            point_str += " ";
            point_str += std::to_string(point.imag());
            point_str += "\n";
            fprintf(gnuplot_pipe, point_str.c_str());
        }
        fprintf(gnuplot_pipe, "EOF\n");
        std::cout << "Root" << i << " points in plot: " << basins_of_attraction[i].size() << " points." << std::endl;
    }
}

void Newton_fractal::set_basins_colors(FILE* gnuplot_pipe) {    // green, red , blue,  yellow, when initial polynomial
    std::string gnuplot_colors[] = {"green", "red", "blue", "yellow", "dark-turquoise", "dark-green", "gray", "orange", "black"};

    for(int i=0; i<=polynomial.number_of_roots; i++) {
        std::string root_number = std::to_string(i);
        std::string color_str = gnuplot_colors[i];
        std::string plot_str = "\'-\' using 1:2 title \"root";
        plot_str += root_number;
        plot_str += "\" with dots lt rgb \"";
        plot_str += color_str;
        plot_str += "\"";
        if (i != polynomial.number_of_roots)
            plot_str += ",";
        else
            plot_str += "\n";
        fprintf(gnuplot_pipe, plot_str.c_str());
    }
}

void Newton_fractal::set_plot_options(FILE* gnuplot_pipe) {
    fprintf(gnuplot_pipe, "set terminal png size %d, %d\n", resolutionRe, resolutionIm);
    std::string set_plot_name = "set output \"fractal";
    std::string plot_number = std::to_string(fractals_number);
    set_plot_name += plot_number;
    set_plot_name += ".png\"\n";
    fprintf(gnuplot_pipe, set_plot_name.c_str());
    // offset, margins, font, set for purpose of my thesis
    // needed to be changed, when resolution is less than ~2000
    // or when there are decimal places
    fprintf(gnuplot_pipe, "set xlabel \"Re\" font \",40\" offset 0,-6\n");
    fprintf(gnuplot_pipe, "set ylabel \"Im\" font \",40\" offset -6, 0\n");
    fprintf(gnuplot_pipe, "set grid front\n");
    fprintf(gnuplot_pipe, "set tics font \",40\"\n");
    fprintf(gnuplot_pipe, "set xtics offset 0,-3,0\n");
    fprintf(gnuplot_pipe, "set ytics offset -2,0,0\n");
    fprintf(gnuplot_pipe, "set bmargin 10\n");
    fprintf(gnuplot_pipe, "set lmargin 24\n");
    fprintf(gnuplot_pipe, "set rmargin 6\n");
    fprintf(gnuplot_pipe, "set tmargin 3\n");
    fprintf(gnuplot_pipe, "plot ");
}

FILE* open_gnuplot_pipe() {
    FILE* gnuplot_pipe = popen( "gnuplot", "w" );
    if(!gnuplot_pipe) {
        perror("Pipe opening failed");
        exit(EXIT_FAILURE);
    }
    return  gnuplot_pipe;
}

void Newton_fractal::draw_fractal() {
    std::cout << "Drawing Newton's fractal plot..." << std::endl << std::endl;
    FILE* gnuplot_pipe = open_gnuplot_pipe();
    set_plot_options(gnuplot_pipe);
    set_basins_colors(gnuplot_pipe);
    draw_basins_of_attraction(gnuplot_pipe);
    pclose(gnuplot_pipe);
    std::cout << "\nPlot of Newton's fractal is done." << std::endl << std::endl << std::endl;
}
