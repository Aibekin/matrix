#include "matrix/matrix.hpp"
#include <iostream>

matrix::Matrix::Matrix(int rows, int cols, const std::vector<double> &data) : _rows(rows), _cols(cols)
{
    if (data.size() != static_cast<size_t>(rows * cols))
        throw std::invalid_argument("Matrix dimensions do not match data size");
    _data.resize(rows * cols);
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            _data[row * cols + col].value = data[row * cols + col];
            _data[row * cols + col].row = row;
            _data[row * cols + col].col = col;
        }
    }
}

matrix::Matrix::Matrix(const ::c_matrix *mat) : _rows(mat->rows), _cols(mat->cols)
{
    int total = _rows * _cols;
    _data.resize(total);
    for (int row = 0; row < mat->rows; ++row)
    {
        for (int col = 0; col < mat->cols; ++col)
        {
            _data[row * mat->cols + col].value = mat->data[row * mat->cols + col].value;
            _data[row * mat->cols + col].row = mat->data[row * mat->cols + col].row;
            _data[row * mat->cols + col].col = mat->data[row * mat->cols + col].col;
        }
    }
}

matrix::Matrix::Matrix(double value, int rows, int cols) : _rows(rows), _cols(cols)
{
    int total = _rows * _cols;
    _data.resize(total);
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            _data[row * cols + col].value = value;
            _data[row * cols + col].row = row;
            _data[row * cols + col].col = col;
        }
    }
}

std::vector<double> matrix::Matrix::to_raw_data() const
{
    std::vector<double> raw;
    raw.reserve(_data.size());
    for (const auto &el : _data)
        raw.push_back(el.value);
    return raw;
}

double matrix::Matrix::determinant() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    double result = ::determinant(&mat);
    ::free_matrix(&mat);
    return result;
}

std::vector<double> matrix::Matrix::data() const { return to_raw_data(); }
int matrix::Matrix::width() const { return _cols; }
int matrix::Matrix::height() const { return _rows; }

void matrix::Matrix::print_matrix() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::print_matrix(&mat);
    ::free_matrix(&mat);
}

matrix::Matrix matrix::Matrix::transpose() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix matr = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::c_matrix transposed = ::transpose(&matr);
    Matrix res(&transposed);
    ::free_matrix(&transposed);
    return res;
}

coord matrix::Matrix::find_el(double el)
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    coord res = ::find_el(&mat, el);
    ::free_matrix(&mat);
    return res;
}

double matrix::Matrix::sum() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    double res = ::sum_of_matrix(&mat);
    ::free_matrix(&mat);
    return res;
}

double matrix::Matrix::average() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    double res = ::average_of_matrix(&mat);
    ::free_matrix(&mat);
    return res;
}

double matrix::Matrix::min() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    double res = ::min_of_matrix(&mat);
    ::free_matrix(&mat);
    return res;
}

double matrix::Matrix::max() const
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix mat = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    double res = ::max_of_matrix(&mat);
    ::free_matrix(&mat);
    return res;
}

double matrix::Matrix::operator()(int row, int col) const // getter
{
    return _data[row * _cols + col].value;
}

double &matrix::Matrix::operator()(int row, int col) // setter
{
    return _data[row * _cols + col].value;
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

matrix::Matrix matrix::Matrix::inverse() const
{
    if (_rows != _cols)
        throw std::invalid_argument("Only square matrices can be inverted");

    double det = determinant();
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
                    minor.push_back(_data[i * n + j].value);
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

matrix::Matrix matrix::Matrix::operator+(const Matrix &other) const // addition
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> raw1 = to_raw_data();
    ::c_matrix temp1 = create_matrix(const_cast<double *>(raw1.data()), _rows, _cols);
    std::vector<double> raw2 = other.to_raw_data();
    ::c_matrix temp2 = create_matrix(const_cast<double *>(raw2.data()), _rows, _cols);
    ::c_matrix temp_result = addition(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator+(double value) const // add to scalar
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix temp = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::add_matrix_to_scalar(&temp, value);
    Matrix mat(&temp);
    ::free_matrix(&temp);
    return mat;
}

matrix::Matrix matrix::Matrix::operator-(const Matrix &other) const // substraction
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> raw1 = to_raw_data();
    ::c_matrix temp1 = create_matrix(const_cast<double *>(raw1.data()), _rows, _cols);
    std::vector<double> raw2 = other.to_raw_data();
    ::c_matrix temp2 = create_matrix(const_cast<double *>(raw2.data()), _rows, _cols);
    ::c_matrix temp_result = substraction(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator-(double value) const // substract from scalar
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix temp = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::substract_matrix_from_scalar(&temp, value);
    Matrix mat(&temp);
    ::free_matrix(&temp);
    return mat;
}

matrix::Matrix matrix::Matrix::operator*(const Matrix &other) const // multiply
{
    if (_rows != other._rows || _cols != other._cols)
        throw std::invalid_argument("Matrix sizes do not match");

    std::vector<double> raw1 = to_raw_data();
    ::c_matrix temp1 = create_matrix(const_cast<double *>(raw1.data()), _rows, _cols);
    std::vector<double> raw2 = other.to_raw_data();
    ::c_matrix temp2 = create_matrix(const_cast<double *>(raw2.data()), _rows, _cols);
    ::c_matrix temp_result = multiply(&temp1, &temp2);
    matrix::Matrix result(&temp_result);
    ::free_matrix(&temp_result);
    return result;
}

matrix::Matrix matrix::Matrix::operator*(double value) const // multiply by scalar
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix temp = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::multiply_matrix_by_scalar(&temp, value);
    Matrix mat(&temp);
    ::free_matrix(&temp);
    return mat;
}

matrix::Matrix matrix::Matrix::operator/(const Matrix &other) const // division
{
    return *this * other.inverse();
}

matrix::Matrix matrix::Matrix::operator/(double value) const // divide by scalar
{
    std::vector<double> raw = to_raw_data();
    ::c_matrix temp = create_matrix(const_cast<double *>(raw.data()), _rows, _cols);
    ::divide_matrix_by_scalar(&temp, value);
    Matrix mat(&temp);
    ::free_matrix(&temp);
    return mat;
}

std::ostream &matrix::operator<<(std::ostream &os, const matrix::Matrix &mat)
{
    int cell_width = 5;
    // os << std::fixed << std::setprecision(2);

    for (int i = 0; i < mat.height(); ++i)
    {
        for (int j = 0; j < mat.width(); ++j)
        {
            os << "| " << std::setw(cell_width) << mat(i, j) << " ";
        }
        os << "|\n";
    }
    return os;
}