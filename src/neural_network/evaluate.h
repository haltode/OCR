#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

#include "neural_network.h"
#include "training/dataset.h"

int network_run(struct Network *network, struct Matrix *network_input);
void network_evaluate(struct Network *network, struct Dataset *dataset);

#endif
