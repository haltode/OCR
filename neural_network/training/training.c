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

void network_train(void)
{
}
