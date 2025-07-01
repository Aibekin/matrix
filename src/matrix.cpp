#include "matrix/matrix.hpp"
#include <iostream>

matrix::Matrix::Matrix(int size_x, int size_y, const std::vector<double> &data) : _rows(size_x), _cols(size_y), _data(data)
{
    if (data.size() != static_cast<size_t>(size_x * size_y))
        throw std::invalid_argument("Matrix dimensions do not match data size");
}

matrix::Matrix::Matrix(const ::c_matrix *mat) : _rows(mat->rows), _cols(mat->cols)
{
    int total = _rows * _cols;
    _data.reserve(total);
    for (int i = 0; i < total; ++i)
    {
        _data.push_back(mat->data[i].value);
    }
}

double matrix::Matrix::determinant() const
{
    ::c_matrix mat = create_matrix(const_cast<double *>(_data.data()), _rows, _cols);
    double result = ::determinant(&mat);
    ::free_matrix(&mat);
    return result;
}

const std::vector<double> &matrix::Matrix::data() const { return _data; }
int matrix::Matrix::width() const { return _cols; }
int matrix::Matrix::height() const { return _rows; }

void matrix::Matrix::print_matrix() const
{
    ::c_matrix mat = ::create_matrix(const_cast<double *>(_data.data()), _rows, _cols);
    ::print_matrix(&mat);
    ::free_matrix(&mat);
}

double matrix::Matrix::operator()(int row, int col) const
{
    return _data[row * _cols + col];
}

matrix::Matrix matrix::Matrix::inverse() const
{
    if (_rows != _cols)
        throw std::invalid_argument("Only square matrices can be inverted");

    int det = determinant();
    if (det == 0)
        throw std::runtime_error("Matrix is singular and cannot be inverted");

    int n = _rows;
    std::vector<double> cofactors(n * n);

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            std::vector<double> minor;
            for (int i = 0; i < n; ++i)
            {
                if (i == row)
                    continue;
                for (int j = 0; j < n; ++j)
                {
                    if (j == col)
                        continue;
                    minor.push_back(_data[i * n + j]);
                }
            }

            matrix::Matrix minor_matrix(n - 1, n - 1, minor);
            double minor_det = minor_matrix.determinant();

            cofactors[row * n + col] = ((row + col) % 2 == 0 ? 1 : -1) * minor_det;
        }
    }

    std::vector<double> adjugate(n * n);
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            adjugate[col * n + row] = cofactors[row * n + col];
        }
    }

    std::vector<double> inverse_data(n * n);
    for (int i = 0; i < n * n; ++i)
    {
        inverse_data[i] = adjugate[i] / det;
    }

    return Matrix(n, n, inverse_data);
}

matrix::Matrix &matrix::Matrix::operator=(const Matrix &other)
{
    if (this == &other)
        return *this;
    _rows = other._rows;
    _cols = other._cols;
    _data = other._data;

    return *this;
}

// math

matrix::Matrix matrix::Matrix::operator+(const Matrix &other) const // addition
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    ::c_matrix temp1 = create_matrix(const_cast<double *>(_data.data()), _rows, _cols);
    ::c_matrix temp2 = create_matrix(const_cast<double *>(other._data.data()), _rows, _cols);
    ::c_matrix temp_result = addition(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator-(const Matrix &other) const // substraction
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    ::c_matrix temp1 = create_matrix(const_cast<double *>(_data.data()), _rows, _cols);
    ::c_matrix temp2 = create_matrix(const_cast<double *>(other._data.data()), _rows, _cols);
    ::c_matrix temp_result = substraction(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator*(const Matrix &other) const // multiply
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    ::c_matrix temp1 = create_matrix(const_cast<double *>(_data.data()), _rows, _cols);
    ::c_matrix temp2 = create_matrix(const_cast<double *>(other._data.data()), _rows, _cols);
    ::c_matrix temp_result = multiply(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator/(const Matrix &other) const // division
{
    return *this * other.inverse();
}

std::ostream &matrix::operator<<(std::ostream &os, const matrix::Matrix &mat)
{
    for (int i = 0; i < mat.height(); ++i)
    {
        for (int j = 0; j < mat.width(); ++j)
        {
            os << "| " << mat.data()[i * mat.width() + j] << " ";
        }
        os << "|\n";
    }
    return os;
}