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
