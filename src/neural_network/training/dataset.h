#ifndef DATASET_H
#define DATASET_H

#include <stddef.h>

#include "../../utils/matrix.h"

struct ExampleData
{
    struct Matrix *in;
    struct Matrix *out;
};

struct Dataset
{
    size_t nb_examples;
    struct ExampleData *examples;
};

struct Dataset *dataset_alloc(size_t nb_examples);
void dataset_free(struct Dataset *dataset);

void dataset_random_shuffle(struct Dataset *dataset);

void dataset_split(
    struct Dataset *full_set,
    struct Dataset *train_set, struct Dataset *validation_set,
    struct Dataset *test_set);

#endif
