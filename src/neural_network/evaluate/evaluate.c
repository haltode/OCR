#include "../propagation.h"
#include "evaluate.h"

struct Matrix *network_run(
    struct Network *network, struct Matrix *network_input)
{
    network_forward(network, network_input);

    struct Layer *output_layer = &network->layers[network->nb_layers - 1];
    return output_layer->out;
}

void network_evaluate(
    struct Network *network, struct TrainingParams params,
    struct Dataset *dataset, const char *dataset_name)
{
    printf("%s results:\n"
           "accuracy: %.2f%%\n"
           "cost: %.2f\n",
        dataset_name,
        network_evaluate_accuracy(network, dataset),
        network_evaluate_cost(network, params, dataset));
}
