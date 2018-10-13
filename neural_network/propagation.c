#include <math.h>

#include "propagation.h"

float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}

float sigmoid_prime(float x)
{
    return sigmoid(x) * (1 - sigmoid(x));
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

void network_compute_error(struct Network *network, struct Matrix *desired_out)
{
    struct Layer *output_layer = &network->layers[network->nb_layers - 1];
    matrix_free(output_layer->delta);

    output_layer->delta =
        matrix_hadamard_mul(
            matrix_sub(output_layer->out, desired_out),
            matrix_apply_func(output_layer->in, sigmoid_prime));
}

void layer_backward(struct Layer *previous, struct Layer *current)
{
    matrix_free(previous->delta);

    previous->delta =
        matrix_hadamard_mul(
            matrix_mul(
                matrix_transpose(current->weight),
                current->delta),
            matrix_apply_func(previous->in, sigmoid_prime));
}

void network_backward(struct Network *network)
{
    for (int i = network->nb_layers - 2; i >= 0; i--)
        layer_backward(&network->layers[i], &network->layers[i + 1]);
}
