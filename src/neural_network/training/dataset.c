#include <stdlib.h>

#include "dataset.h"

struct Dataset *dataset_alloc(size_t nb_examples)
{
    struct Dataset *dataset = malloc(sizeof(struct Dataset));
    dataset->nb_examples = nb_examples;
    dataset->examples = malloc(sizeof(struct ExampleData) * nb_examples);
    return dataset;
}

void dataset_free(struct Dataset *dataset)
{
    for (size_t i = 0; i < dataset->nb_examples; i++)
    {
        matrix_free(dataset->examples[i].in);
        matrix_free(dataset->examples[i].out);
    }
    free(dataset->examples);
    free(dataset);
}

// https://stackoverflow.com/a/6127606
void dataset_random_shuffle(struct Dataset *dataset)
{
    if (dataset->nb_examples <= 1)
        return;

    for (size_t i = 0; i < dataset->nb_examples - 1; i++)
    {
        size_t n = i + rand() / (RAND_MAX / (dataset->nb_examples - i) + 1);

        struct ExampleData tmp = dataset->examples[n];
        dataset->examples[n] = dataset->examples[i];
        dataset->examples[i] = tmp;
    }
}
