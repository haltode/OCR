#ifndef PROPAGATION_H
#define PROPAGATION_H

#include "neural_network.h"

void network_forward(struct Network *network, struct Matrix *network_input);
void network_compute_error(struct Network *network, struct Matrix *desired_out);
void network_backward(struct Network *network);

#endif
