#include "matrix/matrix.h"
#include <stdio.h>

c_matrix create_matrix(double *arr, int x, int y)
{
    c_matrix mat;
    mat.size_x = x;
    mat.size_y = y;
    mat.data = malloc(sizeof(single_mat) * x * y);

    for (int row = 0; row < y; ++row)
    {
        for (int col = 0; col < x; ++col)
        {
            int index = row * x + col;
            mat.data[index].value = arr[index];
            mat.data[index].row = row;
            mat.data[index].col = col;
        }
    }
    return mat;
}

void print_matrix(const c_matrix *mat)
{
    for (int i = 0; i < mat->size_y; ++i)
    {
        for (int j = 0; j < mat->size_x; ++j)
        {
            printf("| %d ", mat->data[i * mat->size_x + j].value);
        }
        printf("|\n\n");
    }
}

void free_matrix(c_matrix *mat)
{
    free(mat->data);
    mat->data = NULL;
}

void make_minor(const c_matrix *mat, c_matrix *newmat, int exclude_row, int exclude_col)
{
    newmat->size_x = mat->size_x - 1;
    newmat->size_y = mat->size_y - 1;
    newmat->data = malloc(sizeof(single_mat) * newmat->size_x * newmat->size_y);
    int idi = 0;
    for (int i = 0; i < mat->size_y; ++i)
    {
        if (i == exclude_row)
            continue;
        int idj = 0;
        for (int j = 0; j < mat->size_x; ++j)
        {
            if (j == exclude_col)
                continue;

            int src_index = i * mat->size_x + j;
            int dst_index = idi * newmat->size_x + idj;

            newmat->data[dst_index].value = mat->data[src_index].value;
            newmat->data[dst_index].row = idi;
            newmat->data[dst_index].col = idj;
            ++idj;
        }
        ++idi;
    }
}

int determinant(const c_matrix *mat)
{
    if (mat->size_x == 1)
    {
        return mat->data[0].value;
    }
    if (mat->size_x == 2)
    {
        return mat->data[0].value * mat->data[3].value - mat->data[1].value * mat->data[2].value;
    }

    int res = 0;

    for (int i = 0; i < mat->size_x; ++i)
    {
        int sign = (i % 2 == 0) ? 1 : -1;
        int temp = mat->data[i].value;

        c_matrix minor;
        make_minor(mat, &minor, 0, i);

        int det = determinant(&minor);
        res += sign * temp * det;
    }
    return res;
}