#include <math.h>

#include "math.h"

float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}

float sigmoid_prime(float x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

int argmax(float *array, size_t size)
{
    int max_idx = 0;
    for (size_t i = 0; i < size; i++)
        if (array[i] > array[max_idx])
            max_idx = i;
    return max_idx;
}
