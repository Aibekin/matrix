#include "matrix/matrix_output.hpp"

std::ostream &operator<<(std::ostream &os, const coord &coor)
{
    return os << coor.row << " " << coor.col;
}

std::ostream &operator<<(std::ostream &os, const c_matrix &mat)
{
    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {
            os << "| " << mat.data[i * mat.cols + j].value << " ";
        }
        os << "|\n";
    }
    return os;
}