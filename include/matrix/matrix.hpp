#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix/matrix.h"
#include "matrix/matrix_output.hpp"
#include <vector>
#include <ostream>

namespace matrix
{
    class Matrix
    {
    private:
        int _rows;
        int _cols;
        std::vector<::single_mat> _data;
        Matrix inverse() const;
        std::vector<double> to_raw_data() const;

    public:
        Matrix(int rows, int cols, const std::vector<double> &data);
        Matrix(const ::c_matrix *mat);
        Matrix(double value, int rows, int cols);

        double determinant() const;

        std::vector<double> data() const;
        int width() const;
        int height() const;

        void print() const;

        // int find(int row, int col) const;
        Matrix transpose() const;

        coord find_el(double el);

        double sum() const;
        double average() const;
        double min() const;
        double max() const;

        Matrix submatrix(int row_start, int col_start, int row_end, int col_end);
        void append_rows(const Matrix &mat);
        void append_cols(const Matrix &mat);

        double operator()(int row, int col) const;
        double &operator()(int row, int col);
        Matrix &operator=(const Matrix &other);
        Matrix operator+(const Matrix &other) const;
        Matrix operator+(double value) const;
        Matrix operator-(const Matrix &other) const;
        Matrix operator-(double value) const;
        Matrix operator*(const Matrix &other) const;
        Matrix operator*(double value) const;
        Matrix operator/(const Matrix &other) const;
        Matrix operator/(double value) const;
    };

    std::ostream &operator<<(std::ostream &os, const Matrix &mat);
}

#endif
