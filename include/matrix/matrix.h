#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct coord
    {
        int row;
        int col;
    } coord;

    typedef struct single_mat
    {
        double value;
        int col;
        int row;
    } single_mat;

    typedef struct c_matrix
    {
        int rows;
        int cols;
        single_mat *data;
    } c_matrix;

    c_matrix create_matrix(const double *arr, int _rows, int _cols);

    void print_matrix(const c_matrix *mat);

    void free_matrix(c_matrix *mat);

    double find(const c_matrix *mat, int row, int col);

    coord find_el(const c_matrix *mat, double el);

    void make_minor(const c_matrix *mat, c_matrix *newmat, int exclude_row, int exclude_col);

    double determinant(const c_matrix *mat);

    c_matrix transpose(const c_matrix *mat);

    // math
    c_matrix inverse(const c_matrix *mat);
    c_matrix addition(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix substraction(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix multiply(const c_matrix *mat1, const c_matrix *mat2);
    c_matrix division(const c_matrix *mat1, const c_matrix *mat2);

    double sum_of_matrix(const c_matrix *mat);
    double average_of_matrix(const c_matrix *mat);
    double min_of_matrix(const c_matrix *mat);
    double max_of_matrix(const c_matrix *mat);

#ifdef __cplusplus
}
#endif

#endif