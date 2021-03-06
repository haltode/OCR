#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stddef.h>

#include "../utils/matrix.h"

struct Layer
{
    size_t nb_neurons;
    struct Matrix *in;
    struct Matrix *out;
    struct Matrix *weight;
    struct Matrix *bias;
    struct Matrix *delta;
};

struct Network
{
    size_t nb_layers;
    struct Layer *layers;
};

struct Network *network_alloc(size_t nb_layers, size_t *layers_size);
void network_free(struct Network *network);

void network_save(struct Network *network, const char *filename);
struct Network *network_load(const char *filename);

#endif
