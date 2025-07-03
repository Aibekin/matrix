#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

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

#ifdef __cplusplus
}
#endif

#endif