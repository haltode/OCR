#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double random_float(double lower, double upper)
{
    int rnd = rand();
    double scale = upper - lower;
    return lower + (rnd * scale / RAND_MAX);
}

// Marsaglia polar method for standard normal random variables
double normal_distribution(double mean, double stddev)
{
    static bool has_spare = false;
    static double spare;

    if (has_spare)
    {
        has_spare = false;
        return mean + stddev * spare;
    }

    has_spare = true;

    static double u, v, s;

    do
    {
        u = (rand() * 2.0 / RAND_MAX) - 1.0;
        v = (rand() * 2.0 / RAND_MAX) - 1.0;
        s = u * u + v * v;
    } while(s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;

    return mean + stddev * u * s;
}
