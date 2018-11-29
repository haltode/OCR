#ifndef UTILS_MATRIX_H
#define UTILS_MATRIX_H

#include <stddef.h>
#include <stdio.h>

struct Matrix
{
    size_t nb_rows;
    size_t nb_cols;
    float *mat;
};

struct Matrix *matrix_alloc(size_t nb_rows, size_t nb_cols);
void matrix_free(struct Matrix *matrix);

void matrix_save(FILE *f, struct Matrix *matrix);
struct Matrix *matrix_load(FILE *f);
void matrix_load_inplace(FILE *f, struct Matrix *matrix);

size_t matrix_size(struct Matrix *matrix);
struct Matrix *matrix_copy(struct Matrix *matrix);

float matrix_get(struct Matrix *matrix, size_t row, size_t col);
void matrix_set(struct Matrix *matrix, size_t row, size_t col, float value);

struct Matrix *matrix_add(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_sub(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_scalar(struct Matrix *a, float scalar);
struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_hadamard_mul(struct Matrix *a, struct Matrix *b);

void matrix_add_inplace(struct Matrix *a, struct Matrix *b);
void matrix_sub_inplace(struct Matrix *a, struct Matrix *b);

struct Matrix *matrix_transpose(struct Matrix *matrix);
struct Matrix *matrix_apply_func(struct Matrix *matrix, float (*func)(float));
int matrix_argmax(struct Matrix *matrix);

void matrix_print(struct Matrix *matrix);

#endif
