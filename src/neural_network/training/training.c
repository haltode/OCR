#include <stdlib.h>

#include "training.h"

struct TrainingSet *train_set_alloc(struct Params params)
{
    struct TrainingSet *train_set = malloc(sizeof(struct TrainingSet));
    train_set->params = params;
    train_set->examples =
        malloc(sizeof(struct TrainingData) * params.nb_examples);

    return train_set;
}

void train_set_free(struct TrainingSet *train_set)
{
    for (size_t i = 0; i < train_set->params.nb_examples; i++)
    {
        matrix_free(train_set->examples[i].in);
        matrix_free(train_set->examples[i].out);
    }
    free(train_set->examples);
    free(train_set);
}

// https://stackoverflow.com/a/6127606
void random_shuffle_set(struct TrainingSet *train_set)
{
    size_t nb_examples = train_set->params.nb_examples;
    if (nb_examples <= 1)
        return;

    for (size_t i = 0; i < nb_examples - 1; i++)
    {
        size_t n = i + rand() / (RAND_MAX / (nb_examples - i) + 1);

        struct TrainingData tmp = train_set->examples[n];
        train_set->examples[n] = train_set->examples[i];
        train_set->examples[i] = tmp;
    }
}

void network_train(void)
{
}
