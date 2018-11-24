#include <stdio.h>

#include "../propagation.h"
#include "../evaluate.h"
#include "training.h"

static void network_update_neurons(
    struct Network *network, struct TrainingParams params)
{
    float weight_modif_rate =
        (params.learn_rate / params.mini_batch_size) *
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

static struct Dataset *get_mini_batch(
    struct Dataset *train_set, size_t batch_size, size_t batch_id)
{
    struct Dataset* batch = dataset_alloc(batch_size);
    for (size_t i = 0; i < batch_size; i++)
    {
        size_t j = batch_id * batch_size + i;
        batch->examples[i].in = matrix_copy(train_set->examples[j].in);
        batch->examples[i].out = matrix_copy(train_set->examples[j].out);
    }
    return batch;
}

static void gradient_descent_step(
    struct Network *network, struct TrainingParams params,
    struct Dataset *batch)
{
    for (size_t i = 0; i < batch->nb_examples; i++)
    {
        network_forward(network, batch->examples[i].in);
        network_compute_error(network, batch->examples[i].out);
        network_backward(network);
        network_update_neurons(network, params);
    }
}

void gradient_descent(
    struct Network *network, struct TrainingParams params,
    struct Dataset *train_set, struct Dataset *validation_set,
    bool verbose)
{
    printf("training network with parameters:\n"
           "nb_examples: %zu\n"
           "nb_epochs: %zu\n"
           "mini_batch_size: %zu\n"
           "learn_rate: %f\n"
           "regularization_rate: %f\n\n",
        params.nb_examples, params.nb_epochs,
        params.mini_batch_size,
        params.learn_rate, params.regularization_rate);

    for (size_t epoch = 1; epoch <= params.nb_epochs; epoch++)
    {
        dataset_random_shuffle(train_set);

        size_t nb_batch = params.nb_examples / params.mini_batch_size;
        for (size_t batch_id = 0; batch_id < nb_batch; batch_id++)
        {
            struct Dataset *batch =
                get_mini_batch(train_set, params.mini_batch_size, batch_id);
            gradient_descent_step(network, params, batch);
            dataset_free(batch);
        }

        if (verbose)
        {
            printf("done epoch %zu\n", epoch);
            printf("validation set results:\n"
                   "accuracy: %.2f%%\n"
                   "cost: %.2f\n\n",
                network_evaluate_accuracy(network, validation_set),
                network_evaluate_cost(network, params, validation_set));
        }
    }
}
