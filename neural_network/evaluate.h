#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

#include "neural_network.h"
#include "training/training.h"

int network_run(struct Network *network, struct Matrix *network_input);
bool is_network_correct(struct Network *network,
    struct Matrix *network_input, struct Matrix *expected_output);
void network_evaluate(struct Network *network, struct TrainingSet *train_set);

#endif
