#include <stdlib.h>

#include "neural_network.h"

static void layer_alloc(struct Layer *layer, size_t nb_in, size_t nb_out)
{
    layer->nb_neurons = nb_out;
    layer->in = matrix_alloc(nb_in, 1);
    layer->out = matrix_alloc(nb_out, 1);
    layer->weight = matrix_alloc(nb_in, nb_out);
    layer->bias = matrix_alloc(nb_out, 1);
}

static void layer_free(struct Layer *layer)
{
    matrix_free(layer->in);
    matrix_free(layer->out);
    matrix_free(layer->weight);
    matrix_free(layer->bias);
}

struct Network *network_alloc(size_t nb_layers, size_t *layers_size)
{
    struct Network *network = malloc(sizeof(struct Network));
    network->nb_layers = nb_layers;
    network->layers = malloc(sizeof(struct Layer) * nb_layers);
    for (size_t i = 0; i < nb_layers; i++)
    {
        size_t prev_layer_size = 0;
        if (i > 0)
            prev_layer_size = layers_size[i - 1];
        layer_alloc(&network->layers[i], prev_layer_size, layers_size[i]);
    }
    return network;
}

void network_free(struct Network *network)
{
    for (size_t i = 0; i < network->nb_layers; i++)
        layer_free(&network->layers[i]);
    free(network->layers);
    free(network);
}
