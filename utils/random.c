#include <stdlib.h>

float random_float(float lower, float upper)
{
    int rnd = rand();
    float scale = upper - lower;
    return lower + (rnd * scale / RAND_MAX);
}
