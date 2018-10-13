#include <math.h>

#include "../utils/matrix.h"
#include "neural_network.h"

float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}

void layer_feedforward(struct Layer *previous, struct Layer *current)
{
    matrix_free(current->in);
    matrix_free(current->out);

    current->in =
        matrix_add(
            matrix_mul(current->weight, previous->out),
            current->bias);
    current->out = matrix_apply_func(current->in, sigmoid);
}

void network_feedforward(struct Network *network, struct Matrix *network_input)
{
    struct Layer *input_layer = &network->layers[0];
    matrix_free(input_layer->in);
    matrix_free(input_layer->out);
    input_layer->in = matrix_copy(network_input);
    input_layer->out = matrix_copy(network_input);

    for (size_t i = 1; i < network->nb_layers; i++)
        layer_feedforward(&network->layers[i - 1], &network->layers[i]);
}
