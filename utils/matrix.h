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
void matrix_set(struct Matrix *matrix, size_t row, size_t col, float value);

struct Matrix *matrix_add(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_sub(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b);

struct Matrix *matrix_transpose(struct Matrix *matrix);
struct Matrix *matrix_apply_func(struct Matrix *matrix, float (*func)(float));
void matrix_fill_random(struct Matrix *matrix, float lower, float upper);
void matrix_print(struct Matrix *matrix);

#endif
