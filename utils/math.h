#ifndef MATH_H
#define MATH_H

#include <stddef.h>

float sigmoid(float x);
float sigmoid_prime(float x);
int argmax(float *array, size_t size);

#endif