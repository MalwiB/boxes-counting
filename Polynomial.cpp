#include "Polynomial.h"
#include "random_complex.h"
#include "newtons_method.h"
#include "NullComplex.h"

Polynomial::Polynomial(std::vector<double> a_coefficients) {
    coefficients = a_coefficients;
    degree = coefficients.size()-1;
    number_of_roots = degree;
    count_derivative_coefficients();
}

void Polynomial::count_derivative_coefficients() {
    for (int i=0; i<=degree-1; i++) {
        derivative_coefficients.push_back(coefficients[i+1] * (i + 1));
    }
}

std::complex<double> Polynomial::count_value(std::complex<double> z) {
    std::complex<double> value(0, 0);
    int i;
    for (i=degree; i>=0; i--) {
        value += std::complex<double>(coefficients[i], 0) * pow(z, i);
    }
    return value;
}

std::complex<double> Polynomial::count_derivative_value(std::complex<double> z){
    std::complex<double> value(0, 0);
    int i;
    for (i=degree-1; i>=0; i--) {
        value += std::complex<double>(derivative_coefficients[i], 0) * pow(z, i);
    }
    return value;
}

bool Polynomial::is_root_in_set(std::complex<double> root) {
    for (std::vector<std::complex<double>>::iterator it = roots.begin(); it != roots.end(); ++it)
        if(abs(root - *it) < MAX_SAME_ROOT_DISTANCE)
            return true;
    return false;
}

void Polynomial::find_roots(Scope a_scope_randRe, Scope a_scope_randIm) {
    scope_randRe = a_scope_randRe;
    scope_randIm = a_scope_randIm;

    int number_of_computed_roots = 0;
    do{
        std::complex<double> starting_point = random_complex(scope_randRe, scope_randIm);
        std::cout << "starting point: " << starting_point << std::endl;
        std::complex<double> root = newtons_method(*this, starting_point);
        static NullComplex<double> null_obj;
        if (root != null_obj) {
            if (!is_root_in_set(root)) {
                std::cout<<"ROOT: "<<root<<std::endl<<std::endl;
                roots.push_back(root);
                number_of_computed_roots++;
            }
        }
    } while(number_of_computed_roots < number_of_roots);

    std::cout <<"ALL ROOTS: "<< std::endl;
    for (std::vector<std::complex<double>>::iterator it = roots.begin(); it != roots.end(); ++it)
        std::cout << *it << "\n";
    std::cout << std::endl << std::endl;
}
