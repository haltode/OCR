#ifndef TRAINING_H
#define TRAINING_H

#include <stddef.h>

#include "../utils/matrix.h"
#include "neural_network.h"

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

void gradient_descent(struct Network *network, struct TrainingSet *train_set);
void gradient_descent_step(struct Network *network, struct TrainingSet *batch);
void network_update_neurons(struct Network *network, float modif_rate);

#endif
