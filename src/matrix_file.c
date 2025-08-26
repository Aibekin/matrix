#include "matrix/matrix_file.h"

void save_matrix(const char *filename, const c_matrix *mat)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
    {
        perror("fopen");
        return;
    }

    fwrite(&mat->rows, sizeof(int), 1, f);
    fwrite(&mat->cols, sizeof(int), 1, f);
    for (int i = 0; i < mat->rows * mat->cols; i++)
    {
        fwrite(&mat->data[i].value, sizeof(double), 1, f);
    }

    fclose(f);
}

c_matrix load_matrix(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("fopen");
        exit(1);
    }

    int rows, cols;
    fread(&rows, sizeof(int), 1, f);
    fread(&cols, sizeof(int), 1, f);

    c_matrix mat = alloc_matrix(rows, cols);

    for (int i = 0; i < rows * cols; i++)
    {
        fread(&mat.data[i].value, sizeof(double), 1, f);
        mat.data[i].row = i / cols;
        mat.data[i].col = i % cols;
    }

    fclose(f);
    return mat;
}

void save_matrix_bin(const char *filename, const c_matrix *mat)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
    {
        perror("fopen");
        return;
    }

    fwrite(MATRIX_MAGIC, 1, MATRIX_MAGIC_LEN, f);

    int32_t rows = mat->rows;
    int32_t cols = mat->cols;
    fwrite(&rows, sizeof(int32_t), 1, f);
    fwrite(&cols, sizeof(int32_t), 1, f);

    for (int i = 0; i < rows * cols; i++)
    {
        fwrite(&mat->data[i].value, sizeof(double), 1, f);
    }

    fclose(f);
}

c_matrix load_matrix_bin(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("fopen");
        exit(1);
    }

    char magic[MATRIX_MAGIC_LEN];
    fread(magic, 1, MATRIX_MAGIC_LEN, f);
    if (memcmp(magic, MATRIX_MAGIC, MATRIX_MAGIC_LEN) != 0)
    {
        fprintf(stderr, "Ошибка: файл %s не является .matrix\n", filename);
        fclose(f);
        exit(1);
    }

    int32_t rows, cols;
    fread(&rows, sizeof(int32_t), 1, f);
    fread(&cols, sizeof(int32_t), 1, f);

    c_matrix mat = alloc_matrix(rows, cols);

    for (int i = 0; i < rows * cols; i++)
    {
        fread(&mat.data[i].value, sizeof(double), 1, f);
        mat.data[i].row = i / cols;
        mat.data[i].col = i % cols;
    }

    fclose(f);
    return mat;
}

c_matrix *load_pmatrix_bin(const char *filename)
{
    c_matrix mat = load_matrix_bin(filename);
    return &mat;
}