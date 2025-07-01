#include "matrix/matrix.h"
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

void make_minor(const c_matrix *mat, c_matrix *newmat, int exclude_row, int exclude_col)
{
	newmat->rows = mat->rows - 1;
	newmat->cols = mat->cols - 1;
	newmat->data = malloc(sizeof(single_mat) * newmat->rows * newmat->cols);
	int idi = 0;
	for (int i = 0; i < mat->rows; ++i)
	{
		if (i == exclude_row)
			continue;
		int idj = 0;
		for (int j = 0; j < mat->cols; ++j)
		{
			if (j == exclude_col)
				continue;

			int src_index = i * mat->cols + j;
			int dst_index = idi * newmat->cols + idj;

			newmat->data[dst_index].value = mat->data[src_index].value;
			newmat->data[dst_index].row = idi;
			newmat->data[dst_index].col = idj;
			++idj;
		}
		++idi;
	}
}

double determinant(const c_matrix *mat)
{
	if (mat->rows == 1)
	{
		return mat->data[0].value;
	}
	if (mat->rows == 2)
	{
		return mat->data[0].value * mat->data[3].value - mat->data[1].value * mat->data[2].value;
	}

	double res = 0;

	for (int i = 0; i < mat->rows; ++i)
	{
		double sign = (i % 2 == 0) ? 1 : -1;
		double temp = mat->data[i].value;

		c_matrix minor;
		make_minor(mat, &minor, 0, i);

		int det = determinant(&minor);
		res += sign * temp * det;
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

// math

c_matrix inverse(const c_matrix *mat)
{
	double det = determinant(mat);
	if (det == 0)
		return *mat;
	int n = mat->rows;
	double *cofactors = malloc(sizeof(double) * n * n);
	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			double *minor = malloc(sizeof(double) * (n - 1) * (n - 1));
			int id = 0;
			for (int i = 0; i < n; ++i)
			{
				if (i == row)
					continue;
				for (int j = 0; j < n; ++j)
				{
					if (j == col)
						continue;
					minor[id++] = mat->data[i * n + j].value;
				}
			}

			c_matrix minor_matrix = create_matrix(minor, n - 1, n - 1);
			double minor_det = determinant(&minor_matrix);

			cofactors[row * n + col] = ((row + col) % 2 == 0 ? 1 : -1) * minor_det;
			free(minor);
		}
	}

	double *adjugate = malloc(sizeof(double) * n * n);
	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			adjugate[col * n + row] = cofactors[row * n + col];
		}
	}

	double *inverse_data = malloc(sizeof(double) * n * n);
	;
	for (int i = 0; i < n * n; ++i)
	{
		inverse_data[i] = adjugate[i] / det;
	}

	free(cofactors);
	free(adjugate);
	return create_matrix(inverse_data, n, n);
}

c_matrix addition(const c_matrix *mat1, const c_matrix *mat2)
{
	double *arr = malloc(sizeof(double) * mat1->rows * mat1->cols);
	if (mat1->rows != mat2->rows || mat1->cols != mat2->cols)
	{
		return create_matrix(arr, mat1->rows, mat1->cols);
	}
	for (int i = 0; i < mat1->rows * mat1->cols; ++i)
	{
		arr[i] = mat1->data[i].value + mat2->data[i].value;
	}

	return create_matrix(arr, mat1->rows, mat1->cols);
}

c_matrix substraction(const c_matrix *mat1, const c_matrix *mat2)
{
	double *arr = malloc(sizeof(double) * mat1->rows * mat1->cols);
	if (mat1->rows != mat2->rows || mat1->cols != mat2->cols)
	{
		return create_matrix(arr, mat1->rows, mat1->cols);
	}
	for (int i = 0; i < mat1->rows * mat1->cols; ++i)
	{
		arr[i] = mat1->data[i].value - mat2->data[i].value;
	}

	return create_matrix(arr, mat1->rows, mat1->cols);
}

c_matrix multiply(const c_matrix *mat1, const c_matrix *mat2)
{
	if (mat1->cols != mat2->rows)
		return create_matrix((double *)calloc(1, sizeof(double)), mat1->rows, mat2->cols);

	int rows = mat1->rows;
	int cols = mat2->cols;
	int inner = mat1->cols;

	double *result_data = malloc(sizeof(double) * rows * cols);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			double sum = 0.0;
			for (int k = 0; k < inner; ++k)
			{
				double a = mat1->data[i * inner + k].value;
				double b = mat2->data[k * cols + j].value;
				sum += a * b;
			}
			result_data[i * cols + j] = sum;
		}
	}

	return create_matrix(result_data, rows, cols);
}

c_matrix division(const c_matrix *mat1, const c_matrix *mat2)
{
	c_matrix inv_mat = inverse(mat2);
	c_matrix res = multiply(mat1, &inv_mat);
	free_matrix(&inv_mat);
	return res;
}