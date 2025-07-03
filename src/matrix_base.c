#include "matrix/matrix_base.h"
#include <stdio.h>

c_matrix create_matrix(const double *arr, int _rows, int _cols)
{
    c_matrix mat;
    mat.rows = _rows;
    mat.cols = _cols;
    mat.data = malloc(sizeof(single_mat) * _rows * _cols);

    for (int row = 0; row < _rows; ++row)
    {
        for (int col = 0; col < _cols; ++col)
        {
            int index = row * _cols + col;
            mat.data[index].value = arr[index];
            mat.data[index].row = row;
            mat.data[index].col = col;
        }
    }
    return mat;
}

void print_matrix(const c_matrix *mat)
{
    for (int i = 0; i < mat->rows; ++i)
    {
        for (int j = 0; j < mat->cols; ++j)
        {
            printf("| %lf ", mat->data[i * mat->cols + j].value);
        }
        printf("|\n\n");
    }
}

void free_matrix(c_matrix *mat)
{
    free(mat->data);
    mat->data = NULL;
}