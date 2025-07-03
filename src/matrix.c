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