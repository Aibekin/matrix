#include "matrix/matrix.hpp"
#include <iostream>

matrix::Matrix::Matrix(int size_x, int size_y, const std::vector<double> &data)
    : _size_x(size_x), _size_y(size_y), _data(data)
{
    if (data.size() != static_cast<size_t>(size_x * size_y))
        throw std::invalid_argument("Matrix dimensions do not match data size");
}

int matrix::Matrix::determinant() const
{
    ::c_matrix mat = create_matrix(const_cast<double *>(_data.data()), _size_x, _size_y);
    int result = ::determinant(&mat);
    ::free_matrix(&mat);
    return result;
}

const std::vector<double> &matrix::Matrix::data() const { return _data; }
int matrix::Matrix::width() const { return _size_x; }
int matrix::Matrix::height() const { return _size_y; }

void matrix::Matrix::print_matrix() const
{
    ::c_matrix mat = create_matrix(const_cast<double *>(_data.data()), _size_x, _size_y);
    ::print_matrix(&mat);
    ::free_matrix(&mat);
}

int matrix::Matrix::operator()(int row, int col) const
{
    return _data[row * _size_x + col];
}

matrix::Matrix matrix::Matrix::inverse() const
{
    if (_size_x != _size_y)
        throw std::invalid_argument("Only square matrices can be inverted");

    int det = determinant();
    if (det == 0)
        throw std::runtime_error("Matrix is singular and cannot be inverted");

    int n = _size_x;
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
            int minor_det = minor_matrix.determinant();

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
    _size_x = other._size_x;
    _size_y = other._size_y;
    _data = other._data;

    return *this;
}

matrix::Matrix matrix::Matrix::operator+(const Matrix &other) const // сложение
{
    if (_size_x != other._size_x || _size_y != other._size_y)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> result_data(_size_x * _size_y);
    for (int i = 0; i < _size_x * _size_y; ++i)
    {
        result_data[i] = _data[i] + other._data[i];
    }

    return Matrix(_size_x, _size_y, result_data);
}

matrix::Matrix matrix::Matrix::operator-(const Matrix &other) const // вычитание
{
    if (_size_x != other._size_x || _size_y != other._size_y)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> result_data(_size_x * _size_y);
    for (int i = 0; i < _size_x * _size_y; ++i)
    {
        result_data[i] = _data[i] - other._data[i];
    }

    return Matrix(_size_x, _size_y, result_data);
}

matrix::Matrix matrix::Matrix::operator*(const Matrix &other) const // умножение
{
    if (_size_x != other._size_x || _size_y != other._size_y)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> result_data(_size_x * _size_y);
    for (int i = 0; i < _size_x * _size_y; ++i)
    {
        result_data[i] = _data[i] * other._data[i];
    }

    return Matrix(_size_x, _size_y, result_data);
}

matrix::Matrix matrix::Matrix::operator/(const Matrix &other) const // деление
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