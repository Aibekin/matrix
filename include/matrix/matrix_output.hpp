#ifndef MATRIX_OUTPUT_H
#define MATRIX_OUTPUT_H

#include <iostream>
#include <iomanip>
#include "matrix/matrix.h"

std::ostream &operator<<(std::ostream &os, const coord &coor);

std::ostream &operator<<(std::ostream &os, const c_matrix &mat);

#endif