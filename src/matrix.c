#include "matrix/matrix.h"
#include <stdio.h>

c_matrix create_initial_matrix(double value, int _rows, int _cols)
{
	c_matrix mat = alloc_matrix(_rows, _cols);
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			MAT_AT(&mat, row, col).value = value;
			MAT_AT(&mat, row, col).row = row;
			MAT_AT(&mat, row, col).col = col;
		}
	}
	return mat;
}

c_matrix create_zeros(int _rows, int _cols)
{
	return create_initial_matrix(0.0, _rows, _cols);
}

c_matrix create_ones(int _rows, int _cols)
{
	return create_initial_matrix(1.0, _rows, _cols);
}

c_matrix create_random(int _rows, int _cols, double low, double high)
{
	c_matrix mat = alloc_matrix(_rows, _cols);
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			MAT_AT(&mat, row, col).value = (double)rand() / (double)RAND_MAX * (high - low) + low;
			MAT_AT(&mat, row, col).row = row;
			MAT_AT(&mat, row, col).col = col;
		}
	}
	return mat;
}

c_matrix *create_initial_pmatrix(double value, int _rows, int _cols)
{
	c_matrix *mat = alloc_pmatrix(_rows, _cols);
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			MAT_AT(mat, row, col).value = value;
			MAT_AT(mat, row, col).row = row;
			MAT_AT(mat, row, col).col = col;
		}
	}
	return mat;
}

c_matrix *create_pzeros(int _rows, int _cols)
{
	return create_initial_pmatrix(0.0, _rows, _cols);
}

c_matrix *create_pones(int _rows, int _cols)
{
	return create_initial_pmatrix(1.0, _rows, _cols);
}

c_matrix *create_prandom(int _rows, int _cols, double low, double high)
{
	c_matrix *mat = alloc_pmatrix(_rows, _cols);
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			MAT_AT(mat, row, col).value = (double)rand() / (double)RAND_MAX * (high - low) + low;
			MAT_AT(mat, row, col).row = row;
			MAT_AT(mat, row, col).col = col;
		}
	}
	return mat;
}

void copy_matrix(c_matrix *dst, c_matrix *src)
{
	assert(dst->rows == src->rows);
	assert(dst->cols == src->cols);
	for (int i = 0; i < dst->rows; ++i)
	{
		for (int j = 0; j < dst->cols; ++j)
		{
			MAT_AT(dst, i, j) = MAT_AT(src, i, j);
		}
	}
}

double find(const c_matrix *mat, int row, int col)
{
	if (!mat || row < 0 || col < 0 || row >= mat->rows || col >= mat->cols)
		return 0;

	return MAT_AT(mat, row, col).value;
}

coord find_el(const c_matrix *mat, double el)
{
	coord res = {-1, -1};
	for (int row = 0; row < mat->rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
		{
			if (find(mat, row, col) == el)
			{
				res.row = row;
				res.col = col;
				return res;
			}
		}
	}
	return res;
}

c_matrix transpose(const c_matrix *mat)
{
	int cols = mat->rows; // 2
	int rows = mat->cols; // 3
	double *arr = malloc(sizeof(double) * rows * cols);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			arr[i * cols + j] = MAT_AT(mat, i, j).value;
		}
	}
	c_matrix res = create_matrix(arr, rows, cols);
	free(arr);
	return res;
}

double sum_of_matrix(const c_matrix *mat)
{
	double res = 0;
	for (int row = 0; row < mat->rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
		{
			res += MAT_AT(mat, row, col).value;
		}
	}
	return res;
}

double average_of_matrix(const c_matrix *mat)
{
	return sum_of_matrix(mat) / (mat->cols * mat->rows);
}

double min_of_matrix(const c_matrix *mat)
{
	double min = mat->data[0].value;
	for (int row = 0; row < mat->rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
		{
			if (min >= MAT_AT(mat, row, col).value)
				min = MAT_AT(mat, row, col).value;
		}
	}
	return min;
}

double max_of_matrix(const c_matrix *mat)
{
	double min = mat->data[0].value;
	for (int row = 0; row < mat->rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
		{
			if (min <= MAT_AT(mat, row, col).value)
				min = MAT_AT(mat, row, col).value;
		}
	}
	return min;
}

c_matrix submatrix(const c_matrix *mat, int row_start, int col_start, int row_end, int col_end)
{
	assert(row_start < 0);
	assert(row_end >= mat->rows);
	assert(col_start < 0);
	assert(col_end >= mat->cols);
	// if (row_start < 0 || row_end >= mat->rows || col_start < 0 || col_end >= mat->cols)
	// {
	// 	fprintf(stderr, "Submatrix indices out of bounds\n");
	// 	exit(EXIT_FAILURE);
	// }

	int rows = row_end - row_start + 1;
	int cols = col_end - col_start + 1;
	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			// arr[row * cols + col] = mat->data[(row_start + row) * mat->cols + (col_start + col)].value;
			arr[row * cols + col] = MAT_AT(mat, (row_start + row), (col_start + col)).value;
		}
	}
	c_matrix sub_mat = create_matrix(arr, rows, cols);
	free(arr);
	return sub_mat;
}

c_matrix submatrix_from_array(const double *arr, int orig_rows, int orig_cols, int row_start, int col_start, int row_end, int col_end)
{
	int rows = row_end - row_start + 1;
	int cols = col_end - col_start + 1;

	c_matrix mat = alloc_matrix(rows, cols);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int src_row = row_start + i;
			int src_col = col_start + j;

			double val = arr[src_row * orig_cols + src_col];
			MAT_AT(&mat, i, j).value = val;
			MAT_AT(&mat, i, j).row = i;
			MAT_AT(&mat, i, j).col = j;
		}
	}
	return mat;
}

c_matrix get_row(c_matrix *mat, int _row)
{
	return submatrix(mat, _row, 0, _row, mat->cols - 1);
}

c_matrix get_col(c_matrix *mat, int _col)
{
	return submatrix(mat, 0, _col, mat->rows - 1, _col);
}

c_matrix *get_prow(c_matrix *mat, int _row)
{
	c_matrix *out = malloc(sizeof(c_matrix));
	*out = alloc_matrix(1, mat->cols);
	for (int col = 0; col < mat->cols; ++col)
	{
		MAT_AT(out, 0, col).value = MAT_AT(mat, _row, col).value;
		MAT_AT(out, 0, col).row = 0;
		MAT_AT(out, 0, col).col = col;
	}
	return out;
}

c_matrix *get_pcol(c_matrix *mat, int _col)
{
	c_matrix *out = malloc(sizeof(c_matrix));
	*out = alloc_matrix(mat->rows, 1);
	for (int row = 0; row < mat->rows; ++row)
	{
		MAT_AT(out, 0, row).value = MAT_AT(mat, row, _col).value;
		MAT_AT(out, 0, row).row = row;
		MAT_AT(out, 0, row).col = 0;
	}
	return out;
}

c_matrix append_rows(const c_matrix *src_mat, const c_matrix *mat_bottom)
{
	int rows = src_mat->rows + mat_bottom->rows;
	int cols = src_mat->cols;

	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < src_mat->rows; ++row)
	{
		for (int col = 0; col < src_mat->cols; ++col)
			arr[row * cols + col] = MAT_AT(src_mat, row, col).value;
	}
	for (int row = 0; row < mat_bottom->rows; ++row)
	{
		for (int col = 0; col < mat_bottom->cols; ++col)
			arr[(src_mat->rows + row) * cols + col] = MAT_AT(mat_bottom, row, col).value;
	}
	c_matrix mat = create_matrix(arr, rows, cols);
	free(arr);
	return mat;
}

c_matrix append_cols(const c_matrix *src_mat, const c_matrix *mat_right)
{
	int rows = src_mat->rows;
	int cols = src_mat->cols + mat_right->cols;

	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < src_mat->cols; ++col)
			arr[row * cols + col] = MAT_AT(src_mat, row, col).value;
		for (int col = 0; col < mat_right->cols; ++col)
			arr[row * cols + (src_mat->cols + col)] = MAT_AT(mat_right, row, col).value;
	}
	c_matrix mat = create_matrix(arr, rows, cols);
	free(arr);
	return mat;
}

void append_rows_to_matrix(c_matrix *mat, const c_matrix *mat_bottom)
{
	int rows = mat->rows + mat_bottom->rows;
	int cols = mat->cols;

	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < mat->rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
			arr[row * cols + col] = MAT_AT(mat, row, col).value;
	}
	for (int row = 0; row < mat_bottom->rows; ++row)
	{
		for (int col = 0; col < mat_bottom->cols; ++col)
			arr[(mat->rows + row) * cols + col] = MAT_AT(mat_bottom, row, col).value;
	}
	mat = create_pmatrix(arr, rows, cols);
	free(arr);
}

void append_cols_to_matrix(c_matrix *mat, const c_matrix *mat_right)
{
	int rows = mat->rows;
	int cols = mat->cols + mat_right->cols;

	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < mat->cols; ++col)
			arr[row * cols + col] = MAT_AT(mat, row, col).value;
		for (int col = 0; col < mat_right->cols; ++col)
			arr[row * cols + (mat->cols + col)] = MAT_AT(mat_right, row, col).value;
	}
	mat = create_pmatrix(arr, rows, cols);
	free(arr);
}