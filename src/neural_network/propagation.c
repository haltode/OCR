#include "../utils/math.h"
#include "propagation.h"

static void layer_forward(struct Layer *previous, struct Layer *current)
{
    matrix_free(current->in);
    matrix_free(current->out);

    struct Matrix *weight_x_out = matrix_mul(current->weight, previous->out);

    current->in = matrix_add(weight_x_out, current->bias);
    current->out = matrix_apply_func(current->in, sigmoid);

    matrix_free(weight_x_out);
}

void network_forward(struct Network *network, struct Matrix *network_input)
{
    struct Layer *input_layer = &network->layers[0];
    matrix_free(input_layer->in);
    matrix_free(input_layer->out);
    input_layer->in = matrix_copy(network_input);
    input_layer->out = matrix_copy(network_input);

    for (size_t i = 1; i < network->nb_layers; i++)
        layer_forward(&network->layers[i - 1], &network->layers[i]);
}

void network_compute_error(struct Network *network, struct Matrix *desired_out)
{
    struct Layer *output_layer = &network->layers[network->nb_layers - 1];

    matrix_free(output_layer->delta);
    output_layer->delta = matrix_sub(output_layer->out, desired_out);
}

static void layer_backward(struct Layer *previous, struct Layer *current)
{
    matrix_free(previous->delta);

    struct Matrix *weight_transpose = matrix_transpose(current->weight);
    struct Matrix *wT_x_delta = matrix_mul(weight_transpose, current->delta);
    struct Matrix *in_sigmoid = matrix_apply_func(previous->in, sigmoid_prime);

    previous->delta = matrix_hadamard_mul(wT_x_delta, in_sigmoid);

    matrix_free(weight_transpose);
    matrix_free(wT_x_delta);
    matrix_free(in_sigmoid);
}

void network_backward(struct Network *network)
{
    for (int i = network->nb_layers - 2; i >= 0; i--)
        layer_backward(&network->layers[i], &network->layers[i + 1]);
}
