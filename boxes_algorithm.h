#ifndef BOXES_COUNTING_BOXES_H
#define BOXES_COUNTING_BOXES_H

#include <list>
#include <fstream>
#include "Newton_fractal.h"

typedef std::pair<std::pair<double, double>, std::pair<double, double>> Square;
typedef std::list<Square> BoxesList;
typedef BoxesList::iterator BoxesIterator;

const int MIN_divisions_number = 1;
const int MAX_divisions_number = 12; // max reasonable number: 13

const int Max_boxes_I = 50;

bool compare_points_roots_in_box(Newton_fractal fractal, Square box);

double boxes_dimension(std::vector<int> boxes_amount);

void divide_box(Square box, BoxesIterator box_place, BoxesList* intervals_with_fractal);

void boxes_chart(std::vector<int> boxes_amount);

void boxes_algorithm(Newton_fractal fractal);

void write_fractals_dimensions_to_file();

#endif //BOXES_COUNTING_BOXES_H