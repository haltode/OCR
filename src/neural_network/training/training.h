#ifndef TRAINING_H
#define TRAINING_H

#include <stddef.h>

#include "../../utils/matrix.h"
#include "../neural_network.h"

struct Params
{
    size_t nb_examples;
    size_t nb_epochs;
    size_t mini_batch_size;
    float learn_rate;
    float regularization_rate;
};

struct TrainingData
{
    struct Matrix *in;
    struct Matrix *out;
};

struct TrainingSet
{
    struct Params params;
    struct TrainingData *examples;
};

struct TrainingSet *train_set_alloc(struct Params params);
void train_set_free(struct TrainingSet *train_set);

void random_shuffle_set(struct TrainingSet *train_set);

void network_train(void);
void gradient_descent(
    struct Network *network, struct TrainingSet *train_set);

#endif
