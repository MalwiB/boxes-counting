#ifndef BOXES_COUNTING_NULLCOMPLEX_H
#define BOXES_COUNTING_NULLCOMPLEX_H

#include <iostream>
#include <complex>

template<typename T> class NullComplex : public std::complex<T> {
public:
    std::ostream& operator<<(std::ostream& s) {
        return s << "Null Complex" << std::endl;
    }
};

#endif //BOXES_COUNTING_NULLCOMPLEX_H
