#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix/matrix.h"
#include <vector>
#include <ostream>

namespace matrix
{
    class Matrix
    {
    private:
        int _rows;
        int _cols;
        std::vector<double> _data;
        Matrix inverse() const;

    public:
        Matrix(int rows, int cols, const std::vector<double> &data);
        Matrix(const ::c_matrix *mat);

        double determinant() const;

        const std::vector<double> &data() const;
        int width() const;
        int height() const;

        void print_matrix() const;

        // int find(int row, int col) const;
        static Matrix transpose(Matrix &mat);

        double operator()(int row, int col) const;
        double &operator()(int row, int col);
        Matrix &operator=(const Matrix &other);
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix operator*(const Matrix &other) const;
        Matrix operator/(const Matrix &other) const;
    };

    std::ostream &operator<<(std::ostream &os, const Matrix &mat);
}

#endif
