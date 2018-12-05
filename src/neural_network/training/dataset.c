#include <err.h>
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

void dataset_save(struct Dataset *dataset, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        errx(1, "cannot save dataset to %s", filename);

    fwrite(&dataset->nb_examples, sizeof(size_t), 1, f);
    for (size_t i = 0; i < dataset->nb_examples; i++)
    {
        struct ExampleData *example = &dataset->examples[i];
        matrix_save(f, example->in);
        matrix_save(f, example->out);
    }

    fclose(f);
}

struct Dataset *dataset_load(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        errx(1, "cannot load dataset from %s", filename);

    size_t nb_examples;
    fread(&nb_examples, sizeof(size_t), 1, f);

    struct Dataset *dataset = dataset_alloc(nb_examples);
    for (size_t i = 0; i < nb_examples; i++)
    {
        struct ExampleData *example = &dataset->examples[i];
        example->in = matrix_load(f);
        example->out = matrix_load(f);
    }

    fclose(f);

    return dataset;
}

static void example_data_copy(struct ExampleData *dst, struct ExampleData *src)
{
    dst->in = matrix_copy(src->in);
    dst->out = matrix_copy(src->out);
}

struct Dataset *dataset_get_batch(
    struct Dataset *full_set, size_t batch_size, size_t batch_id)
{
    struct Dataset* batch = dataset_alloc(batch_size);
    for (size_t i = 0; i < batch_size; i++)
    {
        size_t j = batch_id * batch_size + i;
        example_data_copy(&batch->examples[i], &full_set->examples[j]);
    }
    return batch;
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

void dataset_split(
    struct Dataset *full_set,
    struct Dataset *train_set, struct Dataset *validation_set,
    struct Dataset *test_set)
{
    size_t total_examples = train_set->nb_examples +
                            validation_set->nb_examples +
                            test_set->nb_examples;
    if (total_examples > full_set->nb_examples)
        errx(1, "cannot split more dataset data than available");

    dataset_random_shuffle(full_set);

    size_t data_idx = 0;
    for (size_t i = 0; i < train_set->nb_examples; i++)
        example_data_copy(
            &train_set->examples[i], &full_set->examples[data_idx++]);
    for (size_t i = 0; i < validation_set->nb_examples; i++)
        example_data_copy(
            &validation_set->examples[i], &full_set->examples[data_idx++]);
    for (size_t i = 0; i < test_set->nb_examples; i++)
        example_data_copy(
            &test_set->examples[i], &full_set->examples[data_idx++]);
}
