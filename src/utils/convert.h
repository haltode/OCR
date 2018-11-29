#ifndef UTILS_CONVERT_H
#define UTILS_CONVERT_H

#include <SDL2/SDL.h>

#include "matrix.h"

struct Matrix *convert_image_to_matrix(SDL_Surface *image);
struct Matrix *convert_char_to_matrix(char c);
char convert_matrix_to_char(struct Matrix *char_matrix);

#endif
