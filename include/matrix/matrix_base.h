#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#define MAT_AT(m, i, j) (m)->data[(i) * (m)->cols + (j)]
#define MATS_AT(m, n, i, j) (m)->data[(i) * (n) + (j)]
#define PRINT_MATRIX(mat) print_matrix(&mat, #mat, 0);

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

    c_matrix alloc_matrix(int _rows, int _cols);
    void fill_matrix(c_matrix *mat, const double *arr);
    c_matrix create_matrix(const double *arr, int _rows, int _cols);
    c_matrix *alloc_matrix_array(int _amount);
    void print_matrix(const c_matrix *mat, const char *name, size_t padding);
    void free_matrix(c_matrix *mat);

    c_matrix *alloc_pmatrix(int _rows, int _cols);
    c_matrix *create_pmatrix(const double *arr, int _rows, int _cols);

#ifdef __cplusplus
}
#endif

#endif