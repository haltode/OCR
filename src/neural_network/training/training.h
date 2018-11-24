#ifndef TRAINING_H
#define TRAINING_H

#include <stdbool.h>

#include "../neural_network.h"
#include "dataset.h"

struct TrainingParams
{
    size_t nb_examples;
    size_t nb_epochs;
    size_t mini_batch_size;
    float learn_rate;
    float regularization_rate;
};

void gradient_descent(
    struct Network *network, struct TrainingParams params,
    struct Dataset *train_set, struct Dataset *validation_set,
    bool verbose);

#endif
