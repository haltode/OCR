#include "evaluate.h"

static bool is_network_correct(
    struct Network *network,
    struct Matrix *network_input, struct Matrix *expected_output)
{
    struct Matrix *network_output = network_run(network, network_input);

    int network_res = matrix_argmax(network_output);
    int expected_res = matrix_argmax(expected_output);
    return (network_res == expected_res);
}

double network_evaluate_accuracy(
    struct Network *network, struct Dataset *dataset)
{
    size_t nb_correct = 0;
    for (size_t i = 0; i < dataset->nb_examples; i++)
    {
        struct ExampleData *example = &dataset->examples[i];
        if (is_network_correct(network, example->in, example->out))
            nb_correct++;
    }

    double percentage = 100 * nb_correct / dataset->nb_examples;
    return percentage;
}
