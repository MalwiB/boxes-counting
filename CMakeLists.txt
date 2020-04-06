cmake_minimum_required(VERSION 3.6)
project(Boxes_counting)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Polynomial.h Polynomial.cpp newtons_method.h newtons_method.cpp
        Newton_fractal.h Newton_fractal.cpp boxes_algorithm.h boxes_algorithm.cpp
        random_complex.h random_complex.cpp NullComplex.h)
add_executable(Boxes_counting ${SOURCE_FILES})