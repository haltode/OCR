#ifndef PROPAGATION_H
#define PROPAGATION_H

void layer_feedforward(struct Layer *previous, struct Layer *current);
void network_feedforward(struct Network *network, struct Matrix *network_input);

#endif
