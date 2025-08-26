#ifndef MATRIX_FILE
#define MATRIX_FILE

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "matrix/matrix.h"

#define MATRIX_MAGIC "MATRIXv1"
#define MATRIX_MAGIC_LEN 8

#ifdef __cplusplus
extern "C"
{
#endif
    void save_matrix(const char *filename, const c_matrix *mat);
    c_matrix load_matrix(const char *filename);

    void save_matrix_bin(const char *filename, const c_matrix *mat);
    c_matrix load_matrix_bin(const char *filename);
#ifdef __cplusplus
}
#endif

#endif