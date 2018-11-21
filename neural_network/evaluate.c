#include <stdio.h>

#include "../utils/math.h"
#include "evaluate.h"
#include "propagation.h"

int network_run(struct Network *network, struct Matrix *network_input)
{
    network_forward(network, network_input);

    struct Layer *output_layer = &network->layers[network->nb_layers - 1];
    float *output_vect = output_layer->out->mat;
    size_t output_size = output_layer->out->nb_rows;

    return argmax(output_vect, output_size);
}

void network_evaluate(struct Network *network, struct TrainingSet *train_set)
{
    int nb_correct = 0;
    for (size_t i = 0; i < train_set->params.nb_examples; i++)
    {
        struct TrainingData *example = &train_set->examples[i];
        int res = network_run(network, example->in);
        if (res == example->out->mat[0])
            nb_correct++;
    }

    printf("accuracy: %d / %zu\n", nb_correct, train_set->params.nb_examples);
}
