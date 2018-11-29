#ifndef UTILS_SDL_H
#define UTILS_SDL_H

#include <SDL2/SDL.h>

SDL_Surface *image_load(const char *path);
SDL_Surface *image_new(const int height, const int width);

Uint32 image_get_pixel(SDL_Surface *image, int h, int w);
void image_set_pixel(SDL_Surface *image, int h, int w, Uint32 pixel);

#endif
