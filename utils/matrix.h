#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

struct Matrix
{
    size_t nb_rows;
    size_t nb_cols;
    float *mat;
};

struct Matrix *matrix_alloc(size_t nb_rows, size_t nb_cols);
void matrix_free(struct Matrix *matrix);

float matrix_get(struct Matrix *matrix, size_t row, size_t col);

void matrix_print(struct Matrix *matrix);

#endif
