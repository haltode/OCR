#include <stdio.h>

#include "../utils/math.h"
#include "evaluate.h"
#include "propagation.h"

int network_run(struct Network *network, struct Matrix *network_input)
{
    network_forward(network, network_input);

    struct Layer *output_layer = &network->layers[network->nb_layers - 1];
    float *output_vect = output_layer->out->mat;
    size_t output_size = matrix_size(output_layer->out);

    return argmax(output_vect, output_size);
}

static bool is_network_correct(
    struct Network *network,
    struct Matrix *network_input, struct Matrix *expected_output)
{
    int network_res = network_run(network, network_input);

    float *output_vect = expected_output->mat;
    size_t output_size = matrix_size(expected_output);
    int expected_res = argmax(output_vect, output_size);

    return (network_res == expected_res);
}

void network_evaluate(struct Network *network, struct Dataset *dataset)
{
    size_t nb_correct = 0;
    for (size_t i = 0; i < dataset->nb_examples; i++)
    {
        struct ExampleData *example = &dataset->examples[i];
        if (is_network_correct(network, example->in, example->out))
            nb_correct++;
    }

    float percentage = 100 * nb_correct / dataset->nb_examples;
    printf("accuracy: %zu / %zu (%.2f%%)\n",
        nb_correct, dataset->nb_examples, percentage);
}
