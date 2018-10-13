#include <stdio.h>

#include "propagation.h"
#include "training.h"

void gradient_descent(struct Network *network, struct TrainingSet *train_set)
{
    const size_t nb_epochs = 100;

    for (size_t epoch = 0; epoch < nb_epochs; epoch++)
    {
        printf("epoch %zu: ", epoch);
        // TODO: random shuffle + mini batch
        gradient_descent_step(network, train_set);
        printf("\n");
    }
}

void gradient_descent_step(struct Network *network, struct TrainingSet *batch)
{
    const float learning_rate = 3.;
    const float modif_rate = learning_rate / batch->nb_examples;

    for (size_t i = 0; i < batch->nb_examples; i++)
    {
        network_feedforward(network, batch->examples[i].in);
        network_compute_error(network, batch->examples[i].out);
        network_backward(network);
        network_update_neurons(network, modif_rate);
    }
}

void network_update_neurons(struct Network *network, float modif_rate)
{
    for (size_t i = network->nb_layers - 1; i > 0; i--)
    {
        struct Layer *layer = &network->layers[i];
        matrix_sub_inplace(layer->weight,
            matrix_scalar(
                matrix_mul(layer->delta,
                    matrix_transpose(network->layers[i - 1].out)),
                modif_rate));
        matrix_sub_inplace(layer->bias,
            matrix_scalar(layer->delta, modif_rate));
    }
}
