#include <stdio.h>
#include <stdlib.h>

#include "../utils/matrix.h"
#include "../neural_network/neural_network.h"
#include "../neural_network/training/gradient_descent.h"

const int xor_fct[4][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};

static void add_training_data(struct TrainingSet *train_set, size_t idx)
{
    struct Matrix *in = matrix_alloc(2, 1);
    in->mat[0] = xor_fct[idx][0];
    in->mat[1] = xor_fct[idx][1];
    struct Matrix *out = matrix_alloc(1, 1);
    out->mat[0] = xor_fct[idx][2];

    struct TrainingData example = {in, out};
    train_set->examples[idx] = example;
}

void test_xor_network(void)
{
    size_t layers_size[] = {2, 1, 1};
    struct Network *network = network_alloc(3, layers_size);

    struct TrainingSet *train_set = train_set_alloc(4);
    for (size_t i = 0; i < 4; i++)
        add_training_data(train_set, i);

    const size_t nb_epochs = 100;
    const float learning_rate = 3.;
    gradient_descent(network, train_set, nb_epochs, learning_rate);

    train_set_free(train_set);
    network_free(network);
}
