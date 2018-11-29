#include <err.h>
#include <stdlib.h>

#include "matrix.h"

struct Matrix *matrix_alloc(size_t nb_rows, size_t nb_cols)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->nb_rows = nb_rows;
    matrix->nb_cols = nb_cols;
    matrix->mat = calloc(nb_rows * nb_cols, sizeof(float));
    return matrix;
}

void matrix_free(struct Matrix *matrix)
{
    free(matrix->mat);
    free(matrix);
}

void matrix_save(FILE *f, struct Matrix *matrix)
{
    fwrite(&matrix->nb_rows, sizeof(size_t), 1, f);
    fwrite(&matrix->nb_cols, sizeof(size_t), 1, f);
    fwrite(matrix->mat, sizeof(float) * matrix_size(matrix), 1, f);
}

struct Matrix *matrix_load(FILE *f)
{
    size_t nb_rows, nb_cols;
    fread(&nb_rows, sizeof(size_t), 1, f);
    fread(&nb_cols, sizeof(size_t), 1, f);

    struct Matrix *matrix = matrix_alloc(nb_rows, nb_cols);
    fread(matrix->mat, sizeof(float) * matrix_size(matrix), 1, f);

    return matrix;
}

void matrix_load_inplace(FILE *f, struct Matrix *matrix)
{
    size_t nb_rows, nb_cols;
    fread(&nb_rows, sizeof(size_t), 1, f);
    fread(&nb_cols, sizeof(size_t), 1, f);
    if (nb_rows != matrix->nb_rows || nb_cols != matrix->nb_cols)
        errx(1, "cannot load inplace (wrong dimensions)");

    fread(matrix->mat, sizeof(float) * matrix_size(matrix), 1, f);
}

size_t matrix_size(struct Matrix *matrix)
{
    return matrix->nb_rows * matrix->nb_cols;
}

struct Matrix *matrix_copy(struct Matrix *matrix)
{
    struct Matrix *copy = matrix_alloc(matrix->nb_rows, matrix->nb_cols);
    for (size_t i = 0; i < matrix_size(matrix); i++)
        copy->mat[i] = matrix->mat[i];
    return copy;
}

float matrix_get(struct Matrix *matrix, size_t row, size_t col)
{
    return matrix->mat[row * matrix->nb_cols + col];
}

void matrix_set(struct Matrix *matrix, size_t row, size_t col, float value)
{
    matrix->mat[row * matrix->nb_cols + col] = value;
}

struct Matrix *matrix_add(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
        errx(1, "cannot add matrices (wrong dimensions)");

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t i = 0; i < matrix_size(a); i++)
        res->mat[i] = a->mat[i] + b->mat[i];
    return res;
}

struct Matrix *matrix_sub(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
        errx(1, "cannot substract matrices (wrong dimensions)");

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t i = 0; i < matrix_size(a); i++)
        res->mat[i] = a->mat[i] - b->mat[i];
    return res;
}

struct Matrix *matrix_scalar(struct Matrix *a, float scalar)
{
    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t i = 0; i < matrix_size(a); i++)
        res->mat[i] = a->mat[i] * scalar;
    return res;
}

struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_cols != b->nb_rows)
        errx(1, "cannot multiply matrices (wrong dimensions)");

    struct Matrix *res = matrix_alloc(a->nb_rows, b->nb_cols);
    for (size_t r = 0; r < res->nb_rows; r++)
        for (size_t c = 0; c < res->nb_cols; c++)
            for (size_t s = 0; s < a->nb_cols; s++)
            {
                float sum = matrix_get(res, r, c) +
                            matrix_get(a, r, s) *
                            matrix_get(b, s, c);
                matrix_set(res, r, c, sum);
            }
    return res;
}

struct Matrix *matrix_hadamard_mul(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
        errx(1, "cannot use hadamard product (wrong dimensions)");

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t i = 0; i < matrix_size(a); i++)
        res->mat[i] = a->mat[i] * b->mat[i];
    return res;
}

void matrix_add_inplace(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
        errx(1, "cannot add matrices (wrong dimensions)");

    for (size_t i = 0; i < matrix_size(a); i++)
        a->mat[i] += b->mat[i];
}

void matrix_sub_inplace(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
        errx(1, "cannot substract matrices (wrong dimensions)");

    for (size_t i = 0; i < matrix_size(a); i++)
        a->mat[i] -= b->mat[i];
}

struct Matrix *matrix_transpose(struct Matrix *matrix)
{
    struct Matrix *res = matrix_alloc(matrix->nb_cols, matrix->nb_rows);
    for (size_t r = 0; r < res->nb_rows; r++)
        for (size_t c = 0; c < res->nb_cols; c++)
        {
            float value = matrix_get(matrix, c, r);
            matrix_set(res, r, c, value);
        }
    return res;
}

struct Matrix *matrix_apply_func(struct Matrix *matrix, float (*func)(float))
{
    struct Matrix *res = matrix_alloc(matrix->nb_rows, matrix->nb_cols);
    for (size_t i = 0; i < matrix_size(res); i++)
        res->mat[i] = (*func)(matrix->mat[i]);
    return res;
}

int matrix_argmax(struct Matrix *matrix)
{
    int max_idx = 0;
    for (size_t i = 0; i < matrix_size(matrix); i++)
        if (matrix->mat[i] > matrix->mat[max_idx])
            max_idx = i;
    return max_idx;
}

void matrix_print(struct Matrix *matrix)
{
    for (size_t r = 0; r < matrix->nb_rows; r++)
    {
        for (size_t c = 0; c < matrix->nb_cols; c++)
        {
            printf("%f", matrix_get(matrix, r, c));
            if (c + 1 < matrix->nb_cols)
                printf("\t");
        }
        printf("\n");
    }
}
