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
    c_matrix create_random(int _rows, int cols, double low, double high);

    void copy_matrix(c_matrix *dst, c_matrix *src);

    double find(const c_matrix *mat, int row, int col);
    coord find_el(const c_matrix *mat, double el);

    c_matrix transpose(const c_matrix *mat);

    // math

    double sum_of_matrix(const c_matrix *mat);
    double average_of_matrix(const c_matrix *mat);
    double min_of_matrix(const c_matrix *mat);
    double max_of_matrix(const c_matrix *mat);

    c_matrix submatrix(const c_matrix *mat, int row_start, int col_start, int row_end, int col_end);
    c_matrix submatrix_from_array(const double *arr, int orig_rows, int orig_cols, int row_start, int col_start, int row_end, int col_end);
    c_matrix get_row(c_matrix *mat, int _row);
    c_matrix get_col(c_matrix *mat, int _col);
    c_matrix *get_prow(c_matrix *mat, int _row);
    c_matrix *get_pcol(c_matrix *mat, int _col);
    c_matrix append_rows(const c_matrix *src_mat, const c_matrix *mat_bottom);
    c_matrix append_cols(const c_matrix *src_mat, const c_matrix *mat_right);

#ifdef __cplusplus
}
#endif

#endif