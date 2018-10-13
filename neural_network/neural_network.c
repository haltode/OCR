#include <stdio.h>
#include <stdlib.h>

#include "neural_network.h"

static void layer_alloc(struct Layer *layer, size_t nb_in, size_t nb_out)
{
    layer->nb_neurons = nb_out;
    layer->in = matrix_alloc(nb_in, 1);
    layer->out = matrix_alloc(nb_out, 1);
    layer->weight = matrix_alloc(nb_out, nb_in);
    layer->bias = matrix_alloc(nb_out, 1);
    layer->delta = matrix_alloc(nb_out, 1);
}

static void layer_free(struct Layer *layer)
{
    matrix_free(layer->in);
    matrix_free(layer->out);
    matrix_free(layer->weight);
    matrix_free(layer->bias);
    matrix_free(layer->delta);
}

static void layer_random_init(struct Layer *layer)
{
    matrix_fill_random(layer->weight, 0., 1.);
    matrix_fill_random(layer->bias, 0., 1.);
}

struct Network *network_alloc(size_t nb_layers, size_t *layers_size)
{
    struct Network *network = malloc(sizeof(struct Network));
    network->nb_layers = nb_layers;
    network->layers = malloc(sizeof(struct Layer) * nb_layers);
    for (size_t i = 0; i < nb_layers; i++)
    {
        struct Layer *layer = &network->layers[i];
        size_t prev_layer_size = 0;
        if (i > 0)
            prev_layer_size = layers_size[i - 1];
        layer_alloc(layer, prev_layer_size, layers_size[i]);
        layer_random_init(layer);
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

void network_save(struct Network *network, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        perror("network: cannot save network to output file.");
        return;
    }

    fprintf(f, "%zu\n", network->nb_layers);
    for (size_t i = 0; i < network->nb_layers; i++)
    {
        fprintf(f, "%zu", network->layers[i].nb_neurons);
        if (i + 1 < network->nb_layers)
            fprintf(f, " ");
    }
    fprintf(f, "\n");

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        struct Layer *layer = &network->layers[i];
        matrix_print_inline(layer->weight, f);
        matrix_print_inline(layer->bias, f);
    }

    fclose(f);
}

struct Network *network_load(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("network: cannot load network from input file.");
        return NULL;
    }

    size_t nb_layers = 0;
    fscanf(f, "%zu\n", &nb_layers);
    size_t *layers_size = malloc(sizeof(size_t) * nb_layers);
    for (size_t i = 0; i < nb_layers; i++)
        fscanf(f, "%zu", &layers_size[i]);
    fscanf(f, "\n");

    struct Network *network = network_alloc(nb_layers, layers_size);
    for (size_t i = 0; i < nb_layers; i++)
    {
        struct Layer *layer = &network->layers[i];

        size_t nb_ele = layer->weight->nb_rows * layer->weight->nb_cols;
        for (size_t idx = 0; idx < nb_ele; idx++)
            fscanf(f, "%f", &layer->weight->mat[idx]);
        fscanf(f, "\n");

        nb_ele = layer->bias->nb_rows * layer->bias->nb_cols;
        for (size_t idx = 0; idx < nb_ele; idx++)
            fscanf(f, "%f", &layer->bias->mat[idx]);
        fscanf(f, "\n");
    }

    free(layers_size);
    fclose(f);

    return network;
}
