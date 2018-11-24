#include <math.h>

#include "../utils/math.h"
#include "evaluate.h"
#include "propagation.h"

struct Matrix *network_run(
    struct Network *network, struct Matrix *network_input)
{
    network_forward(network, network_input);

    struct Layer *output_layer = &network->layers[network->nb_layers - 1];
    return output_layer->out;
}

bool is_network_correct(
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

static double network_cost_function(
    struct Network *network, struct Dataset *dataset)
{
    double cost = 0.;

    for (size_t ex_id = 0; ex_id < dataset->nb_examples; ex_id++)
    {
        struct Matrix *network_input = dataset->examples[ex_id].in;
        struct Matrix *expected_output = dataset->examples[ex_id].out;

        struct Matrix *network_output = network_run(network, network_input);
        double example_sum = 0.;
        for (size_t i = 0; i < network_output->nb_rows; i++)
        {
            double a_i = matrix_get(network_output, i, 0);
            double y_i = matrix_get(expected_output, i, 0);
            double v = y_i * log(a_i) + (1 - y_i) * log(1 - a_i);
            if (!isnan(v))
                example_sum += v;
        }
        cost += example_sum;
    }

    cost *= -1. / dataset->nb_examples;
    return cost;
}

double network_evaluate_cost(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset)
{
    double sum_cost = network_cost_function(network, dataset);

    double sum_regularization = 0.;
    for (size_t i = 0; i < network->nb_layers; i++)
    {
        struct Layer *layer = &network->layers[i];
        struct Matrix *weight = layer->weight;
        double s = 0;
        for (size_t r = 0; r < weight->nb_rows; r++)
            for (size_t c = 0; c < weight->nb_cols; c++)
                s += matrix_get(weight, r, c) * matrix_get(weight, r, c);
        sum_regularization += s;
    }
    sum_regularization *=
        params.regularization_rate / (2. * dataset->nb_examples);

    double total_cost = sum_cost + sum_regularization;
    return total_cost;
}
