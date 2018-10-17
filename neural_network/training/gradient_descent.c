#include <stdio.h>

#include "../../utils/matrix.h"
#include "../propagation.h"
#include "gradient_descent.h"

static void network_update_neurons(struct Network *network, float modif_rate)
{
    for (size_t i = network->nb_layers - 1; i > 0; i--)
    {
        struct Layer *prev_layer = &network->layers[i - 1];
        struct Layer *layer = &network->layers[i];

        struct Matrix *out_transpose = matrix_transpose(prev_layer->out);
        struct Matrix *delta_x_out = matrix_mul(layer->delta, out_transpose);
        struct Matrix *weight_modif = matrix_scalar(delta_x_out, modif_rate);
        struct Matrix *bias_modif = matrix_scalar(layer->delta, modif_rate);

        matrix_sub_inplace(layer->weight, weight_modif);
        matrix_sub_inplace(layer->bias, bias_modif);

        matrix_free(out_transpose);
        matrix_free(delta_x_out);
        matrix_free(weight_modif);
        matrix_free(bias_modif);
    }
}

void gradient_descent(struct Network *network,
    struct TrainingSet *train_set, size_t nb_epochs, float learning_rate)
{
    for (size_t epoch = 0; epoch < nb_epochs; epoch++)
    {
        printf("epoch %zu: ", epoch);

        // TODO: random shuffle + mini batch
        struct TrainingSet *batch = train_set;
        float modif_rate = learning_rate / batch->nb_examples;
        for (size_t i = 0; i < batch->nb_examples; i++)
        {
            network_forward(network, batch->examples[i].in);
            network_compute_error(network, batch->examples[i].out);
            network_backward(network);
            network_update_neurons(network, modif_rate);
        }

        printf("\n");
    }
}