#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

#include <SDL2/SDL.h>

Uint32 image_get_pixel(SDL_Surface *image, int w, int h);
void image_set_pixel(SDL_Surface *image, int w, int h, Uint32 pixel);
bool is_white_pixel(SDL_Surface *image, int w, int h);

#endif