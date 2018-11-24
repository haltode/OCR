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
