#ifndef PROPAGATION_H
#define PROPAGATION_H

#include "../utils/matrix.h"
#include "neural_network.h"

void layer_forward(struct Layer *previous, struct Layer *current);
void network_forward(struct Network *network, struct Matrix *network_input);

void network_compute_error(struct Network *network, struct Matrix *desired_out);

void layer_backward(struct Layer *previous, struct Layer *current);
void network_backward(struct Network *network);

#endif
