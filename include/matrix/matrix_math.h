#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "matrix_base.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void make_minor(const c_matrix *mat, c_matrix *newmat, int exclude_row, int exclude_col);
    double determinant(const c_matrix *mat);

    c_matrix inverse(const c_matrix *mat);
    c_matrix addition(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix substraction(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix multiply(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix division(const c_matrix *mat1, const c_matrix *mat2);

    void add_matrix_to_scalar(c_matrix *mat, double scalar);
    void substract_matrix_from_scalar(c_matrix *mat, double scalar);
    void multiply_matrix_by_scalar(c_matrix *mat, double scalar);
    void divide_matrix_by_scalar(c_matrix *mat, double scalar);

#ifdef __cplusplus
}
#endif

#endif