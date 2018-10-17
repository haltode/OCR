#ifndef TRAINING_H
#define TRAINING_H

#include <stddef.h>

#include "../../utils/matrix.h"

struct TrainingData
{
    struct Matrix *in;
    struct Matrix *out;
};

struct TrainingSet
{
    size_t nb_examples;
    struct TrainingData *examples;
};

struct TrainingSet *train_set_alloc(size_t nb_examples);
void train_set_free(struct TrainingSet *train_set);

void network_train(void);

#endif
