#include "boxes_algorithm.h"
#include "random_complex.h"
#include "newtons_method.h"

std::vector<double> all_boxes_dimensions;

void divide_box(Square box, BoxesIterator box_place, BoxesList* intervals_with_fractal) {
    double stepR = fabs(box.first.first - box.first.second) / 2;
    double stepI = fabs(box.second.first - box.second.second) / 2;

    std::pair<double, double> sR(box.first.first,  box.first.first + stepR);
    std::pair<double, double> sR2(box.first.second - stepR,  box.first.second);
    std::pair<double, double> sI(box.second.first, box.second.first + stepI);
    std::pair<double, double> sI2(box.second.second - stepI,  box.second.second);
    Square s1(Square(sR, sI));
    Square s2(Square(sR, sI2));
    Square s3(Square(sR2, sI));
    Square s4(Square(sR2, sI2));

    intervals_with_fractal->insert(box_place, s1);
    intervals_with_fractal->insert(box_place, s2);
    intervals_with_fractal->insert(box_place, s3);
    intervals_with_fractal->insert(box_place, s4);
}


void boxes_chart(std::vector<int> boxes_amount) {
    std::cout << "Creating boxes chart..." << std::endl << std::endl;
    std::cout << "grid\t\t\tboxes with fractal " << std::endl;

    std::ofstream boxes_file;
    try {
        boxes_file.open("boxes.dat", std::ofstream::out);
    }
    catch(std::ofstream::failure e) {
        std::cerr << "Open file exception: boxes.dat\n";
    }

    FILE* gnuplot_pipe = popen( "gnuplot", "w" );
    if(!gnuplot_pipe) {
        perror("Pipe opening failed");
        exit(EXIT_FAILURE);
    }

    fprintf(gnuplot_pipe, "set terminal png\n");
    fprintf(gnuplot_pipe, "set out \"boxes.png\"\n");
    fprintf(gnuplot_pipe, "set xlabel \"grid\"\n");
    fprintf(gnuplot_pipe, "set ylabel \"boxes\"\n");
    fprintf(gnuplot_pipe, "set logscale\n");
    fprintf(gnuplot_pipe, "set grid front\n");
    fprintf(gnuplot_pipe, "unset key\n");

    double n=0;
    for (std::vector<int>::iterator it_b = boxes_amount.begin(); it_b != boxes_amount.end(); ++it_b) {
        double grid = pow(2, n);
        boxes_file << grid << "\t\t\t" << *it_b << std::endl;
        std::cout << grid << "\t\t\t" << *it_b << std::endl;
        n++;
    }
    std::cout << std::endl;

    fprintf(gnuplot_pipe, "plot \"boxes.dat\" using 1:2\n");

    boxes_file.close();
    pclose(gnuplot_pipe);
}

double boxes_dimension(std::vector<int> boxes_amount) {
    double grid_k_1 =  pow(2, boxes_amount.size() - 2);
    double grid_k = pow(2, boxes_amount.size() - 1);

    int boxes_k_1 = boxes_amount[boxes_amount.size()-2];
    int boxes_k = boxes_amount.back();

    double dimension = (log(boxes_k) - log(boxes_k_1)) / (log(grid_k) - log(grid_k_1));

    std::cout << "Boxes counting dimension of fractal is " << dimension << "." << std::endl;

    all_boxes_dimensions.push_back(dimension);

    return dimension;
}

bool compare_points_roots_in_box(Newton_fractal fractal, Square box) {
    std::complex<double> root1, root2;

    int needed_iterations = 0;

    do {
        if(needed_iterations == Max_boxes_I)
            return false;
        std::complex<double> point1, point2;    //random 2 points, until find fractal or maxIterBox
        point1 = random_complex(box.first, box.second);
        point2 = random_complex(box.first, box.second);

        root1 = newtons_method(fractal.polynomial, point1);
        root1 = fractal.determine_root(root1);

        root2 = newtons_method(fractal.polynomial, point2);
        root2 = fractal.determine_root(root2);

        needed_iterations++;

    } while (root1 == root2);

    return true;
}

void boxes_algorithm(Newton_fractal fractal) {
    Scope scopeRe_B = fractal.scopeRe;
    Scope scopeIm_B = fractal.scopeIm;

    //vector of intervals with fractal, pair interval<scopeRe<minRe, maxRe>, scopeIm<minIm, maxIm>>
    BoxesList* boxes_with_fractal = new BoxesList();
    std::vector<int> boxes_amount;

    std::pair<double, double> Square_Re(scopeRe_B.first, scopeRe_B.second);
    std::pair<double, double> Square_Im(scopeIm_B.first, scopeIm_B.second);

    boxes_with_fractal->push_back(Square(Square_Re, Square_Im));

    int sq = 1;
    for (int i = MIN_divisions_number; i <= MAX_divisions_number; i++) {
        int boxes_number = 0;
        for (BoxesIterator box_it = boxes_with_fractal->begin(); box_it != boxes_with_fractal->end(); ++box_it) {
            bool is_fractal_in_box = compare_points_roots_in_box(fractal, *box_it);
            if (is_fractal_in_box) {
                boxes_number++;
                divide_box(*box_it, box_it, boxes_with_fractal);
            }
            box_it = boxes_with_fractal->erase(box_it);
            --box_it;
        }
        std::cout << sq << " boxes - ";
        boxes_amount.push_back(boxes_number);
        boxes_dimension(boxes_amount);
        sq *= 4;
    }
    std::cout << std::endl;
    boxes_chart(boxes_amount);
}

void write_fractals_dimensions_to_file() {
    std::ofstream dimensions_file;
    try {
        dimensions_file.open("dimensions.txt", std::ofstream::out);
    }
    catch(std::ofstream::failure e) {
        std::cerr << "Open file exception: dimensions.txt\n";
    }

    for(int i=0; i <all_boxes_dimensions.size(); i++) {
        dimensions_file << all_boxes_dimensions[i] << "\n";
    }
}