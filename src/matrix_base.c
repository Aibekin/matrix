#include "matrix/matrix_base.h"
#include <stdio.h>

c_matrix alloc_matrix(int _rows, int _cols)
{
    c_matrix mat;
    mat.rows = _rows;
    mat.cols = _cols;
    mat.data = malloc(sizeof(single_mat) * _rows * _cols);
    return mat;
}

void fill_matrix(c_matrix *mat, const double *arr)
{
    for (int row = 0; row < mat->rows; ++row)
    {
        for (int col = 0; col < mat->cols; ++col)
        {
            int index = row * mat->cols + col;
            mat->data[index].value = arr[index];
            mat->data[index].row = row;
            mat->data[index].col = col;
        }
    }
}

c_matrix create_matrix(const double *arr, int _rows, int _cols)
{
    c_matrix mat = alloc_matrix(_rows, _cols);
    fill_matrix(&mat, arr);
    return mat;
}

c_matrix *alloc_matrix_array(int _amount)
{
    c_matrix *mat_array = malloc(_amount * sizeof(c_matrix));
    return mat_array;
}

void print_matrix(const c_matrix *mat, const char *name, size_t padding)
{
    printf("%*s%s = {\n", (int)padding, "", name);
    for (int i = 0; i < mat->rows; ++i)
    {
        printf("%*s\t", (int)padding, "");
        for (int j = 0; j < mat->cols; ++j)
        {
            printf("| %lf ", MAT_AT(mat, i, j).value);
        }
        printf("|\n");
    }
    printf("%*s}\n", (int)padding, "");
}

void free_matrix(c_matrix *mat)
{
    free(mat->data);
    mat->data = NULL;
}