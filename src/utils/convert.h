#ifndef CONVERT_H
#define CONVERT_H

#include <SDL2/SDL.h>

#include "matrix.h"

extern const size_t g_charset_size;
extern const char *g_charset;

struct Matrix *convert_image_to_matrix(SDL_Surface *image);
struct Matrix *convert_char_to_matrix(char c);

#endif
