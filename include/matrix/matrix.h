#ifndef MATRIX_H
#define MATRIX_H

#include "matrix/matrix_base.h"
#include "matrix/matrix_math.h"

#ifdef __cplusplus
extern "C"
{
#endif

    c_matrix create_initial_matrix(double value, int _rows, int _cols);
    c_matrix create_zeros(int _rows, int _cols);
    c_matrix create_ones(int _rows, int _cols);

    double find(const c_matrix *mat, int row, int col);

    coord find_el(const c_matrix *mat, double el);

    c_matrix transpose(const c_matrix *mat);

    // math

    double sum_of_matrix(const c_matrix *mat);
    double average_of_matrix(const c_matrix *mat);
    double min_of_matrix(const c_matrix *mat);
    double max_of_matrix(const c_matrix *mat);

#ifdef __cplusplus
}
#endif

#endif