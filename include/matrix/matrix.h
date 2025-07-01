#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct single_mat
    {
        double value;
        int col;
        int row;
    } single_mat;

    typedef struct c_matrix
    {
        int size_x;
        int size_y;
        single_mat *data;
    } c_matrix;

    c_matrix create_matrix(double *arr, int x, int y);

    void print_matrix(const c_matrix *mat);

    void free_matrix(c_matrix *mat);

    int find(const c_matrix *mat, int row, int col);

    void make_minor(const c_matrix *mat, c_matrix *newmat, int exclude_row, int exclude_col);

    int determinant(const c_matrix *mat);

#ifdef __cplusplus
}
#endif

#endif