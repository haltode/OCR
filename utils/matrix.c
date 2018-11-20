#include <stdio.h>
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

struct Matrix *matrix_copy(struct Matrix *matrix)
{
    struct Matrix *copy = matrix_alloc(matrix->nb_rows, matrix->nb_cols);
    for (size_t idx = 0; idx < matrix->nb_rows * matrix->nb_cols; idx++)
        copy->mat[idx] = matrix->mat[idx];
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
    {
        perror("matrix: cannot add matrices (wrong dimensions).");
        return NULL;
    }

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        res->mat[idx] = a->mat[idx] + b->mat[idx];
    return res;
}

struct Matrix *matrix_sub(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
    {
        perror("matrix: cannot substract matrices (wrong dimensions).");
        return NULL;
    }

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        res->mat[idx] = a->mat[idx] - b->mat[idx];
    return res;
}

struct Matrix *matrix_scalar(struct Matrix *a, float scalar)
{
    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        res->mat[idx] = a->mat[idx] * scalar;
    return res;
}

struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_cols != b->nb_rows)
    {
        perror("matrix: cannot multiply matrices (wrong dimensions).");
        return NULL;
    }

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
    {
        perror("matrix: cannot use hadamard product (wrong dimensions).");
        return NULL;
    }

    struct Matrix *res = matrix_alloc(a->nb_rows, a->nb_cols);
    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        res->mat[idx] = a->mat[idx] * b->mat[idx];
    return res;
}

void matrix_add_inplace(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
    {
        perror("matrix: cannot add matrices (wrong dimensions).");
        return;
    }

    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        a->mat[idx] += b->mat[idx];
}

void matrix_sub_inplace(struct Matrix *a, struct Matrix *b)
{
    if (a->nb_rows != b->nb_rows || a->nb_cols != b->nb_cols)
    {
        perror("matrix: cannot substract matrices (wrong dimensions).");
        return;
    }

    for (size_t idx = 0; idx < a->nb_rows * a->nb_cols; idx++)
        a->mat[idx] -= b->mat[idx];
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
    for (size_t idx = 0; idx < res->nb_rows * res->nb_cols; idx++)
        res->mat[idx] = (*func)(matrix->mat[idx]);
    return res;
}

void matrix_print(struct Matrix *matrix, FILE *f)
{
    for (size_t r = 0; r < matrix->nb_rows; r++)
    {
        for (size_t c = 0; c < matrix->nb_cols; c++)
        {
            fprintf(f, "%f", matrix_get(matrix, r, c));
            if (c + 1 < matrix->nb_cols)
                fprintf(f, "\t");
        }
        fprintf(f, "\n");
    }
}

void matrix_print_inline(struct Matrix *matrix, FILE *f)
{
    size_t nb_ele = matrix->nb_rows * matrix->nb_cols;
    for (size_t idx = 0; idx < nb_ele; idx++)
    {
        fprintf(f, "%f", matrix->mat[idx]);
        if (idx + 1 < nb_ele)
            fprintf(f, " ");
    }
    fprintf(f, "\n");
}
