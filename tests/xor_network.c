#include <stdio.h>
#include <stdlib.h>

#include "../neural_network/neural_network.h"
#include "../neural_network/propagation.h"
#include "../neural_network/training/training.h"
#include "../utils/matrix.h"

const int xor_table[4][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};

static void setup_training_data(struct TrainingSet *train_set, size_t idx)
{
    struct Matrix *in = matrix_alloc(2, 1);
    in->mat[0] = xor_table[idx][0];
    in->mat[1] = xor_table[idx][1];
    struct Matrix *out = matrix_alloc(1, 1);
    out->mat[0] = xor_table[idx][2];

    struct TrainingData example = {in, out};
    train_set->examples[idx] = example;
}

void test_xor_network(void)
{
    size_t layers_size[] = {2, 2, 1};
    struct Network *network = network_alloc(3, layers_size);

    struct TrainingSet *train_set = train_set_alloc(4);
    for (size_t i = 0; i < 4; i++)
        setup_training_data(train_set, i);

    const size_t nb_epochs = 1000;
    const float learning_rate = 3.;
    gradient_descent(network, train_set, nb_epochs, learning_rate);

    printf("\n");
    for (size_t i = 0; i < 4; i++)
    {
        struct TrainingData *example = &train_set->examples[i];
        printf("input: %f %f\n", example->in->mat[0], example->in->mat[1]);
        network_forward(network, example->in);

        struct Layer *output_layer = &network->layers[network->nb_layers - 1];
        float raw_out = output_layer->out->mat[0];
        int final_out = (raw_out >= 0.5);
        printf("output: %f => %d\n\n", raw_out, final_out);
    }

    network_save(network, "output/xor_network");

    train_set_free(train_set);
    network_free(network);
}
