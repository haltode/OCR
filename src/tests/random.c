#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/random.h"

double mean(double* values, size_t n)
{
    double s = 0;
    for (size_t i = 0; i < n; i++)
        s += values[i];
    return s / n;
}

double stddev(double* values, size_t n)
{
    double average = mean(values, n);
    double s = 0;
    for (size_t i = 0; i < n; i++)
        s += (values[i] - average) * (values[i] - average);
    return sqrt(s / (n - 1));
}

double *generate_values(size_t n)
{
    double* values = malloc(n * sizeof(double));
    for (size_t i = 0; i < n; i++)
        values[i] = normal_distribution(0, 1);
    return values;
}

// https://rosettacode.org/wiki/Statistics/Normal_distribution#C
void print_histogram(double* values, size_t n)
{
    const double width = 50;
    const double low = -3.05;
    const double high = 3.05;
    const double delta = 0.1;

    int nbins = (high - low) / delta;
    int* bins = calloc(nbins, sizeof(int));
    for (size_t i = 0; i < n; i++)
    {
        int j = (values[i] - low) / delta;
        if (0 <= j && j < nbins)
            bins[j]++;
    }

    int max = 0;
    for (int j = 0; j < nbins; j++)
        if (max < bins[j])
            max = bins[j];

    for (int j = 0; j < nbins; j++)
    {
        printf("(%5.2f, %5.2f) |", low + j * delta, low + (j + 1) * delta);
        int k = width * bins[j] / max;
        while (k-- > 0)
            putchar('*');
        printf("  %-.1f%%\n", bins[j] * 100.0 / n);
    }

    free(bins);
}

void test_normal_distribution(void)
{
    size_t n = 1000000;
    double *values = generate_values(n);

    printf("mean = %f, stddev = %f\n\n", mean(values, n), stddev(values, n));
    print_histogram(values, n);

    free(values);
}
