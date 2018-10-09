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
