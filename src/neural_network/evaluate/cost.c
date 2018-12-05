#include <math.h>

#include "evaluate.h"

static double network_cost(
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

static double network_regularization_cost(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset)
{
    double cost = 0.;

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        struct Layer *layer = &network->layers[i];
        struct Matrix *weight = layer->weight;

        double weight_sum = 0.;
        for (size_t r = 0; r < weight->nb_rows; r++)
            for (size_t c = 0; c < weight->nb_cols; c++)
            {
                double w = matrix_get(weight, r, c);
                weight_sum += w * w;
            }
        cost += weight_sum;
    }

    cost *= params.regularization_rate / (2. * dataset->nb_examples);
    return cost;
}

double network_evaluate_cost(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset)
{
    double sum_cost = network_cost(network, dataset);
    double sum_regularization =
        network_regularization_cost(network, params, dataset);

    return sum_cost + sum_regularization;
}
