#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

#include "neural_network.h"
#include "training/training.h"

struct Matrix *network_run(
    struct Network *network, struct Matrix *network_input);
bool is_network_correct(
    struct Network *network,
    struct Matrix *network_input, struct Matrix *expected_output);

double network_evaluate_accuracy(
    struct Network *network, struct Dataset *dataset);
double network_evaluate_cost(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset);

#endif
