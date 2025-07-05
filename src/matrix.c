#include "matrix/matrix.h"
#include <stdio.h>

c_matrix create_initial_matrix(double value, int _rows, int _cols)
{
	c_matrix mat;
	mat.rows = _rows;
	mat.cols = _cols;
	mat.data = malloc(sizeof(single_mat) * _rows * _cols);
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			mat.data[row * _cols + col].value = value;
			mat.data[row * _cols + col].row = row;
			mat.data[row * _cols + col].col = col;
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

double find(const c_matrix *mat, int row, int col)
{
	if (!mat || row < 0 || col < 0 || row >= mat->rows || col >= mat->cols)
		return 0;

	return mat->data[row * mat->cols + col].value;
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
			arr[i * cols + j] = mat->data[j * rows + i].value;
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
			res += mat->data[row * mat->cols + col].value;
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
			if (min >= mat->data[row * mat->cols + col].value)
				min = mat->data[row * mat->cols + col].value;
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
			if (min <= mat->data[row * mat->cols + col].value)
				min = mat->data[row * mat->cols + col].value;
		}
	}
	return min;
}

c_matrix submatrix(const c_matrix *mat, int row_start, int col_start, int row_end, int col_end)
{
	if (row_start < 0 || row_end >= mat->rows || col_start < 0 || col_end >= mat->cols)
	{
		fprintf(stderr, "Submatrix indices out of bounds\n");
		exit(EXIT_FAILURE);
	}

	int rows = row_end - row_start + 1;
	int cols = col_end - col_start + 1;
	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			arr[row * cols + col] = mat->data[(row_start + row) * mat->cols + (col_start + col)].value;
		}
	}
	c_matrix sub_mat = create_matrix(arr, rows, cols);
	free(arr);
	return sub_mat;
}

c_matrix append_rows(const c_matrix *src_mat, const c_matrix *mat_bottom)
{
	int rows = src_mat->rows + mat_bottom->rows;
	int cols = src_mat->cols;

	double *arr = malloc(sizeof(double) * rows * cols);

	for (int row = 0; row < src_mat->rows; ++row)
	{
		for (int col = 0; col < src_mat->cols; ++col)
			arr[row * cols + col] = src_mat->data[row * src_mat->cols + col].value;
	}
	for (int row = 0; row < mat_bottom->rows; ++row)
	{
		for (int col = 0; col < mat_bottom->cols; ++col)
			arr[(src_mat->rows + row) * cols + col] = mat_bottom->data[row * mat_bottom->cols + col].value;
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
			arr[row * cols + col] = src_mat->data[row * src_mat->cols + col].value;
		for (int col = 0; col < mat_right->cols; ++col)
			arr[row * cols + (src_mat->cols + col)] = mat_right->data[row * mat_right->cols + col].value;
	}
	c_matrix mat = create_matrix(arr, rows, cols);
	free(arr);
	return mat;
}