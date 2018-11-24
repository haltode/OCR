#include <stdio.h>
#include <stdlib.h>

#include "../neural_network/evaluate.h"
#include "../neural_network/neural_network.h"
#include "../neural_network/training/training.h"
#include "../utils/matrix.h"

// Xor truth table with one-hot encoded result
const int xor_table[4][4] = {
    {0, 0, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 0}
};

static void setup_training_data(struct Dataset *train_set, size_t idx)
{
    struct Matrix *in = matrix_alloc(2, 1);
    in->mat[0] = xor_table[idx][0];
    in->mat[1] = xor_table[idx][1];
    struct Matrix *out = matrix_alloc(2, 1);
    out->mat[0] = xor_table[idx][2];
    out->mat[1] = xor_table[idx][3];

    struct ExampleData example = {in, out};
    train_set->examples[idx] = example;
}

void test_xor_network(void)
{
    size_t layers_size[] = {2, 3, 2};
    struct Network *network = network_alloc(3, layers_size);

    struct TrainingParams params;
    params.nb_examples = 4;
    params.nb_epochs = 1000;
    params.mini_batch_size = 4;
    params.learn_rate = 0.5;
    params.regularization_rate = 0;

    struct Dataset *train_set = dataset_alloc(params.nb_examples);
    for (size_t i = 0; i < params.nb_examples; i++)
        setup_training_data(train_set, i);

    gradient_descent(network, params, train_set);

    network_evaluate(network, train_set);
    printf("\nDetails:\n");
    for (size_t i = 0; i < params.nb_examples; i++)
    {
        struct ExampleData *example = &train_set->examples[i];
        printf("input: %f %f\n", example->in->mat[0], example->in->mat[1]);
        int network_res = network_run(network, example->in);

        struct Layer *output_layer = &network->layers[network->nb_layers - 1];
        float raw_out0 = output_layer->out->mat[0];
        float raw_out1 = output_layer->out->mat[1];
        printf("output: %f %f => %d\n\n", raw_out0, raw_out1, network_res);
    }

    network_save(network, "output/xor_network");

    dataset_free(train_set);
    network_free(network);
}
