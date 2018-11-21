#include <stdio.h>

#include "../../utils/matrix.h"
#include "../propagation.h"
#include "training.h"

static void network_update_neurons(struct Network *network, struct Params params)
{
    float weight_modif_rate =
        (params.learn_rate / params.mini_batch_size) *
        // L2 regularization
        (1 - params.learn_rate *
            (params.regularization_rate / params.nb_examples));
    float bias_modif_rate = params.learn_rate / params.mini_batch_size;

    for (size_t i = network->nb_layers - 1; i > 0; i--)
    {
        struct Layer *prev_layer = &network->layers[i - 1];
        struct Layer *layer = &network->layers[i];

        struct Matrix *out_transpose = matrix_transpose(prev_layer->out);
        struct Matrix *delta_x_out = matrix_mul(layer->delta, out_transpose);

        struct Matrix *weight_modif =
            matrix_scalar(delta_x_out, weight_modif_rate);
        matrix_sub_inplace(layer->weight, weight_modif);

        struct Matrix *bias_modif =
            matrix_scalar(layer->delta, bias_modif_rate);
        matrix_sub_inplace(layer->bias, bias_modif);

        matrix_free(out_transpose);
        matrix_free(delta_x_out);
        matrix_free(weight_modif);
        matrix_free(bias_modif);
    }
}

void gradient_descent(
    struct Network *network, struct TrainingSet *train_set)
{
    printf("training network with parameters:\n"
           "nb_examples: %zu\n"
           "nb_epochs: %zu\n"
           "mini_batch_size: %zu\n"
           "learn_rate: %f\n"
           "regularization_rate: %f\n\n",
        train_set->params.nb_examples, train_set->params.nb_epochs,
        train_set->params.mini_batch_size,
        train_set->params.learn_rate, train_set->params.regularization_rate);

    for (size_t epoch = 1; epoch <= train_set->params.nb_epochs; epoch++)
    {
        // TODO: random shuffle + mini batch
        struct TrainingSet *batch = train_set;

        for (size_t i = 0; i < batch->params.nb_examples; i++)
        {
            network_forward(network, batch->examples[i].in);
            network_compute_error(network, batch->examples[i].out);
            network_backward(network);
            network_update_neurons(network, train_set->params);
        }

        if (epoch % 1000 == 0)
            printf("done epoch %zu\n", epoch);
    }
}
