#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

#include <SDL2/SDL.h>

SDL_Surface *image_load(const char *path);
bool is_white_pixel(SDL_Surface *image, int h, int w);
Uint32 image_get_pixel(SDL_Surface *image, int h, int w);
void image_set_pixel(SDL_Surface *image, int h, int w, Uint32 pixel);

#endif
