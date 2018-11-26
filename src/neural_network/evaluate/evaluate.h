#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

#include "../neural_network.h"
#include "../training/training.h"

struct Matrix *network_run(
    struct Network *network, struct Matrix *network_input);

void network_evaluate(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset, const char *dataset_name);

double network_evaluate_accuracy(
    struct Network *network, struct Dataset *dataset);
double network_evaluate_cost(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset);

#endif
