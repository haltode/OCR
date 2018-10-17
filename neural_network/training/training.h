#ifndef TRAINING_H
#define TRAINING_H

#include <stddef.h>

#include "../../utils/matrix.h"
#include "../neural_network.h"

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
void gradient_descent(struct Network *network,
    struct TrainingSet *train_set, size_t nb_epochs, float learning_rate);

#endif
