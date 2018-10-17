#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include "../neural_network.h"
#include "training.h"

void gradient_descent(struct Network *network,
    struct TrainingSet *train_set, size_t nb_epochs, float learning_rate);

#endif
