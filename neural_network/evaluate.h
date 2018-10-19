#ifndef EVALUATE_H
#define EVALUATE_H

#include "neural_network.h"
#include "training/training.h"

int network_run(struct Network *network, struct Matrix *network_input);
void network_evaluate(struct Network *network, struct TrainingSet *train_set);

#endif
